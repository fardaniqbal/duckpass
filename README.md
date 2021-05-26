Password generator implemented in native code.  Run `make` to build,
then run `./duckpass` to generate a password.  Pass argument `--len=N`
to generate a password of length `N`.  Pass argument `--src=RANDSRC`
to specify file to source random numbers from.  Run with argument `-?`
for more usage info.

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
extent, though not religiously.  In particular I want to keep the code
short and easily auditable.

# Similar Projects

As mentioned above, I found many other open source password
generators.  Although they didn't meet my needs of minimalism,
auditability, and command line interface they might meet your needs
better than `duckpass`.  Here are some other password generators I
found:

* [Advanced Password
  Generator](https://sourceforge.net/projects/apwg/) - lightweight
  password generator with both GUI and command line interfaces written
  in FreePascal/Lazarus.
* [Hawkpass](https://github.com/kalpetros/hawkpass) - generates easy
  to remember passphrases; I think it's browser-based.
* [PassGen](https://github.com/chirra/PasGen) - pronounceable password
  generator.
* [Password Tech](https://sourceforge.net/projects/pwgen-win/) -
  password generator with many bells and whistles like pronounceable
  passwords and Lua scripting.
* [PW Generator](https://sourceforge.net/projects/pw-generator/) -
  password generator using c# and .NET framework.
* [RND](https://sourceforge.net/p/rnd2/code/ci/master/tree/) - secure
  character streams and large files.
* [SimpleKey](https://sourceforge.net/projects/simplekey/) - password
  generator that lets you choose from a list of several algorithms.

Drop me a line if you know about any other open source password
generators that should be on this list.
