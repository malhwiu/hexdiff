# hexdiff

 _WTF is hexdiff?_
hexdiff is a small tool for comparing two binary files

## Features
- Compare two binary files

> Warning! After several mounths of coding in python my brain turned into old sponge. And also I started to learn C very recentely, so this software can have unexpected behavior, bad code and poor memory management. I wrote this just to learn to code in C.

## Example

```sh
$ hexdiff binary1.bin binary2.bin
00000169: 4A 00
0000016A: 70 00
0000016B: BC 00
0000016C: 4A 00
0000016D: 0D 00
000001D9: 6B FF
000001DA: F5 FF
000001DB: 59 FF
000001DC: B6 FF
```

## Installation

### Linux 

Install `gcc`

run `build.sh` or `gcc main.c -o build/hexdiff`

If build succeded, then I'm really glad for you. Now you can put the binary into `/bin` folder if you want.

## Plans

- Make it to accept more arguments then just `file1` and `file2`