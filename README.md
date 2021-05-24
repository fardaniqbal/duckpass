Password generator implemented in native code.  Run `make` to build,
then run `./duckpass` to generate a password.  Pass argument `--len=N`
to generate a password of length `N`.  Pass argument `--src=RANDSRC`
to specify source file containing random bytes.  Run with argument
`-?` for more usage info.

This is mostly an experiment to benchmark against
[`duckpass.sh`](https://github.com/fardaniqbal/duckpass), which is
interpreted code, but is probably more convenient than this since you
don't have to compile it.  I might be re-inventing the wheel here but
other open-source password generators I found didn't meet my
expectations of transparency and minimalism.  I'm trying to follow the
[suckless philosophy](https://suckless.org/philosophy/) to some
extent, though not religiously.
