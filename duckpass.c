/* duckpass.c -- password generator; public domain */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SRC_DEFAULT "/dev/urandom"  /* default random number source */
#define LEN_DEFAULT 12              /* default password length */

static void
usage(const char *progname)
{
  printf("Usage: %s [--src=RANDSRC] [--len=LEN]\n", progname);
  printf("Generate a LEN-character-long password (default %d).\n",
         LEN_DEFAULT);
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
    else if (strstr(argv[i], opt) == argv[i] && argv[i][strlen (opt)] == '=')
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

int
main(int argc, char *argv[])
{
  const char *rand_src = checkopt(argc, argv, "--src", SRC_DEFAULT);
  long pass_len = checkopt_long(argc, argv, "--len", LEN_DEFAULT);

  if (checkopt(argc, argv, "-h", 0) || checkopt(argc, argv, "-?", 0))
    usage(argv[0]);

  printf("rand_src = \"%s\"\n", rand_src);
  printf("pass_len = %ld\n", pass_len);
  return 0;
}
