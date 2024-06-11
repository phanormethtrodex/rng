# rng
its an rng, what more could you ask for? 
can generate a stream of chars (ASCII) in a wide variety of formats/charsets - binary, hex, alphanuma, ASCII symbols (non-alphanuma, printable), or even any possible ASCII (including newlines, backspaces, bells, /etc/..

FUTURE: add feature/option to generate raw bit streams (not just ASCII chars)


coded in C; coded by me

FUTURE: (re)learn how to make make files and drop that biz in the mix
FORNOW: just the source code and resultant compiled exec of the same

NOW: offering compiled executables compatible with three or more (or less..) architecture options! Such as: ARM, WIN/DOS, & UNIX!
..just compile it from source!


## RELEASE NOTES
###VERSIONS
####HISTORY
#####FIXES
LATEST VERSION: 1.0.4
  CHANGES FROM: 1.0.3
  -none

reqs: 
a C compiler (in order to recompile from source)
realtime clock libraries
a CPU with a realtime clock
available entropy pool

```
Usage: rng [bondxluazcys] [#]

# - number of characters

[bondxluazcys] - character class:
b - binary
o - octal
n - "nonal" (1-9)
d - decimal
x - hexadecimal
l - lower
u - upper
a - alpha
z - alphanumeric
c - "printable" ascii
y - non-alphanumeric "printable" ascii
s - any ascii
no args - random number of chars from random class
```
