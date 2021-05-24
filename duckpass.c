/* duckpass.c -- password generator; public domain */
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SRC_DEFAULT "/dev/urandom"  /* default random number source */
#define LEN_DEFAULT 12              /* default password length */
#define LEN_MAX     512             /* maximum password length */

/* Crash with error message M if EXPR is false. */
static void verify(int expr, const char *m) { if (!expr) perror(m), exit(1); }

static void
usage(const char *progname)
{
  printf("Usage: %s [--src=RANDSRC] [--len=LEN]\n", progname);
  printf("Generate a LEN-byte-long password (default %d).\n", LEN_DEFAULT);
  printf("LEN must be at least 4 and at most %d.\n", LEN_MAX);
  printf("RANDSRC specifies random number source (default %s).\n",
         SRC_DEFAULT);
  exit(1);
}

/* Parse command line for option OPT and return its value.  (e.g., if OPT is
   "--foo" and ARGV contains "--foo=bar", then return "bar").  Return
   DEFAULT_VAL if ARGV doesn't contain OPT. */
static const char *
checkopt(int argc, char *argv[], const char *opt, const char *default_val)
{
  int i;
  for (i = 1; i < argc; i++)
    if (!strcmp(argv[i], opt) && i+1 < argc && argv[i+1][0] != '-')
      return argv[i+1];
    else if (strstr(argv[i], opt) == argv[i] && argv[i][strlen(opt)] == '=')
      return argv[i] + strlen (opt) + 1;
    else if (strstr(argv[i], opt) == argv[i] && strstr(opt, "--") != opt)
      return argv[i] + strlen(opt);
  return default_val;
}

/* Like checkopt(), but crashes if OPT's value is not an integer. */
static long
checkopt_long(int argc, char *argv[], const char *opt, long default_val)
{
  const char *strval = checkopt(argc, argv, opt, NULL);
  char *endptr = NULL;
  long retval = strval ? strtol(strval, &endptr, 10) : default_val;

  if (strval && (*strval == '\0' || *endptr != '\0'))
    usage(argv[0]);
  return retval;
}

/* Randomly shuffle LEN bytes in STR.  (e.g., "abcd" -> "dacb"). */
static void
shuffle(char *str, size_t len, FILE *rand_src)
{
  size_t i, j, rnd;
  char swap;
  for (i = 0; i < len; i++) {
    verify(fread(&rnd, sizeof rnd, 1, rand_src) == 1, "Read error");
    j = i + rnd % (len - i);
    swap = str[j];
    str[j] = str[i];
    str[i] = swap;
  }
}

/* Return the first byte from SRC for which FILTER() returns true. */
static char
rand_char(FILE *src, int (*filter)(char))
{
  int c;
  do {
    verify((c = fgetc(src)) != EOF, "Unexpected end of random stream");
  } while (c == '\0' || !filter(c));
  return c;
}

static int is_lower(char c) { return islower(c); }
static int is_upper(char c) { return isupper(c); }
static int is_digit(char c) { return isdigit(c); }
static int is_punct(char c) { return !!strchr("!@#$%^&*?:;_", c); }
static int is_valid(char c) { return (islower(c) ||
                                      isupper(c) ||
                                      isdigit(c) ||
                                      is_punct(c)); }

/* Generate NBYTE-char long password and write the result to PASS. */
static void
gen_pass(char *pass, size_t nbyte, FILE *rand_src)
{
  size_t i;

  /* Generate random chars, but leave space for 4 required chars. */
  verify(nbyte >= 4, "!!! found a bug !!!");
  for (i = 0; i < nbyte-4; i++)
    pass[i] = rand_char(rand_src, is_valid);

  /* Generate required chars (punctuation, numbers, etc). */
  pass[i++] = rand_char(rand_src, is_lower);
  pass[i++] = rand_char(rand_src, is_upper);
  pass[i++] = rand_char(rand_src, is_digit);
  pass[i++] = rand_char(rand_src, is_punct);

  /* Shuffle the chars and nul-terminate. */
  shuffle(pass, i, rand_src);
  pass[i] = '\0';
}

int
main(int argc, char *argv[])
{
  const char *rand_file = checkopt(argc, argv, "--src", SRC_DEFAULT);
  long pass_len = checkopt_long(argc, argv, "--len", LEN_DEFAULT);
  FILE *rand_src;
  char pass[LEN_MAX + 1];

  if (checkopt(argc, argv, "-?", 0))
    usage(argv[0]);
  if (!(4 <= pass_len && pass_len <= LEN_MAX))
    usage(argv[0]);

  verify((rand_src = fopen(rand_file, "rb")) != NULL, rand_file);
  gen_pass(pass, pass_len, rand_src);
  puts(pass);
  return 0;
}
