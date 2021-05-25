Password generator implemented in native code.  Run `make` to build,
then run `./duckpass` to generate a password.  Pass argument `--len=N`
to generate a password of length `N`.  Pass argument `--src=RANDSRC`
to specify source file containing random bytes.  Run with argument
`-?` for more usage info.

# Examples

Run `duckpass` with no arguments to print (to `stdout`) a random
password with at least one lowercase char, one uppercase char, one
number, and one punctuation char:

```sh
$ ./duckpass
PF%5VLT2toD*
```

Use the `--len` option to specify the password length:

```sh
$ ./duckpass --len=8
wHu1u*Uo
```

By default, `duckpass` gets randomness from `/dev/urandom`.  You can
use the `--src` option to specify a different source of randomness:

```sh
$ ./duckpass --src=myfile.txt
xc@Vt9AT5b!P
```

# Why?

This is mostly an experiment to benchmark against
[`duckpass.sh`](https://github.com/fardaniqbal/duckpass), which is
interpreted code, but is probably more convenient than this since you
don't have to compile it.  I might be re-inventing the wheel here but
other open-source password generators I found didn't meet my
expectations of transparency and minimalism.  I'm trying to follow the
[suckless philosophy](https://suckless.org/philosophy/) to some
extent, though not religiously.
