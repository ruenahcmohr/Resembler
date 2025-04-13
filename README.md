# Resembler

It resembles assembly, but...

This is a 6502 like processing environment where you write
the op-codes as decimal into a text file. 

goals:
a language specificly taylored to self- modifying software
a matter a fact, you have to self modify to do much of anything.

you have 64k memory words,
the program is loaded into the front of it
the X  pointer is left on the first byte of non-program space

HAVE FUN!

This is linux-only software. ;) 

opcodes:
0    NOP
1    IN     IN->*X
2    OUT  V V->OUT
15   HALT     

3    SETX V  X = V
4    SUBX V  X = X - V     
5    TRAX    A = X  
6    TRXA    X = A        
7    LDAX    A = *X
8    STAX   *X = A     
9    LDA  V  A = V
10   SUBA V  A = A - V     

11   JNZA V  jump + V if A != 0
12   JZA  V  jump + V if A == 0     
13   JNZX V  jump + V if *X != 0
14   JZX  V  jump + V if *X == 0    



compile:

   gcc main.c -o rzexec2



running:

  The program will always run "main.rz" I link the file to the program I'm working on. Maybe we can change that for a later version.


examples:

  There are a few example files (see the .rz files) 
