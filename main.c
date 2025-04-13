/*


Rue_mohr s resembler interperter.
Nov 29 2012
V2.0000000000000000000000000000000 

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

*/

char * opcodes[] = {"NOP ","IN  ", "OUT ", "SETX", "SUBX", "TRAX", "TRXA", "LDAX", "STAX", "LDA ", "SUBA", "JNZA", "JZA ", "JNZX", "JZX ", "HALT" };
int parcount[] =   { 0,    0,    1,     1,      1,      0,      0,      0,      0,      1,     1,      1,      1,     1,      1,     0     };

int data[65535];
int IP, X, A;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define debug() printf("IP:%d I:%s ",parcount[data[IP]]==1?"%d":"%s"," A:%d  X:%d \n",IP, opcodes[data[IP]], parcount[data[IP]]==1?data[IP]:"", A, X)

void debug() {
  if (parcount[data[IP]]==1) {
    printf("\nIP:%05d I:%s %05d A:%05d  X:%05d *X:%05d   ",IP, opcodes[data[IP]], data[IP+1], A, X, data[X]);
  } else {
     printf("\nIP:%05d I:%s       A:%05d  X:%05d *X:%05d   ",IP, opcodes[data[IP]], A, X, data[X]);
  }

}

int main(void) {
  
  FILE * progfile;
  
  memset(data, 0, 65535);
  IP = 0;
  
  // load program into memory
  
  if ((progfile = fopen("main.rz", "rt")) == NULL) {  //open text file 'param 1' w/ err chk 
    printf("Unable to open main.rz for input.\n");
    return -1;
  }
 
  for ( IP = 0; (fscanf( progfile, "%d", &data[IP]) != EOF)&&(IP<65534);  IP++); 
  fclose(progfile);
  
  X = IP; // set pointers to it
  A = 0;
  
  IP = 0; // reset instruction pointer
  
 ///----
  
  while(data[IP] != 15) {
    debug();
    switch(data[IP]) {
      case 1: // IN     IN->*X
        data[X] = getchar();   IP++;        
      break;    
      
      case 2: // OUT  V V->OUT
        IP++; printf("%c", data[IP]); IP++;
      break;   
      
      case 3: // SETX V  X = V
        IP++;  X = data[IP]; IP++;
      break; 
      
      case 4: // SUBX V  X = X - V    
        IP++;  X = X - data[IP]; IP++;
      break; 
      
      case 5: // TRAX    A = X 
        A = X; IP++;
      break; 
      
      case 6: // TRXA    X = A
        X = A; IP++;
      break; 
      
      case 7: // LDAX    A = *X
        A = data[X]; IP++;
      break; 
      
      case 8: // STAX   *X = A  
        data[X] = A; IP++;
      break; 
      
      case 9: // LDA  V  A = V
        IP++;  A = data[IP]; IP++;
      break; 
      
      case 10: // SUBA V  A = A - V
        IP++;  A = A - data[IP]; IP++;
      break; 
      
      case 11: // JNZA V  jump + V if A != 0
        IP++; 
        if (A != 0) IP += data[IP];
        else IP++; 
      break; 
      
      case 12: // JZA  V  jump + V if A == 0
        IP++; 
        if (A == 0) IP += data[IP];
        else IP++; 
      break; 
      
      case 13: // JNZX V  jump + V if *X != 0
        IP++; 
        if ((data[X]) != 0) IP += data[IP];
        else IP++; 
      break; 
      
      case 14: // JZX  V  jump + V if *X == 0
        IP++; 
        if ((data[X]) == 0) IP += data[IP];
        else IP++; 
      break; 
      
      case 15: // not executed
        printf("\n\n");
        return;
      break; 
      
    
    }
      
  }
  printf("\n");

  
  
  
  


  return 0;
}
