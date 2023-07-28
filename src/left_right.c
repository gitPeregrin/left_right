/*
 ============================================================================
 Name        : left_right.c
 Author      : gitPeregrin
 Version     :
 Copyright   : My copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "bits.h"

#define strDEF	"\033[0m"
#define strRED	"\033[31m"
#define strBLUE	"\033[34m"
#define strER	"\033[K"

#define min(a,b)		(a < b ? a : b)
#define max(a,b)		(a < b ? b : a)
#define res(left,some,right)	(min(max(left,some),right))

typedef unsigned int uint;
typedef unsigned char uchar;
typedef wchar_t wchar;



uint lenS(char * str){ // string lenght
  uint result = 0;
  while(str[result] != 0) result++;
  return result+1;
}

// IMPORTANT !!! do not forget free memory after using mulS()
char * mulS(char * str, int count){ // string multiply
  char * result = malloc(lenS(str)*count);
  for(uint i = 0; i < count; i++){
      sprintf(result+lenS(str)*i,"%s",str);
      if(i+1 != count) * (result+lenS(str)*(i+1)-1) = ' ';
  }
  return result;
}

void printS(char * str, uint * c, uint * lc){
  if(*str < 0){
      char tmp = *(str+2);
      *(str+2) = 0;
      printf("%s",str);
      *(str+2) = tmp;
      *c = *c + 1;
      *lc = *lc + 2;
  }else if(*str == 27){
      uchar i = 0;
      while( *(str+i) != 109) i++;
      char tmp = *(str+i+1);
      *(str+i+1) = 0;
      printf("%s", str);
      *(str+i+1) = tmp;
      *lc = *lc + i;
  }else{
      char tmp = *(str+1);
      *(str+1) = 0;
      printf("%s",str);
      *(str+1) = tmp;
      *c = *c + 1;
      *lc = *lc + 1;
  }
}

int main(void) {

  char * left = "Левая часть консоли";
  char * right = "Right ""side"" of console.";



  // === DRAWING ===

  char * M_left = mulS(left,10);
  char * M_right = mulS(right,10);


  enum {
    LEFT , RIGHT
  };

  uint lcounter, rcounter, counter;
  const uint l_size = lenS(M_left);
  const uint r_size = lenS(M_right);
  lint f = 0;
  lcounter = rcounter = counter = 0;


  setbit((lint*)&f,0,0b0); //side left
  setbit((lint*)&f,1,0b1);
  setbit((lint*)&f,2,0b1);

#define lhasch	getbit((lint)f,1)
#define rhasch	getbit((lint)f,2)
#define side	getbit((lint)f,0)

  while(lhasch || rhasch){

      if(side){		// side = right

	  if(rhasch){	// right side has chars for print

	      printS(&M_right[rcounter], &counter, &rcounter);
	      if(rcounter >= r_size) setbit((lint*)&f,2,0b0); // right side hasnt chars for print

	  }else{
	      printf(" ");
	      counter++;
	  }

      }else{		//side = left

	  if(lhasch){	// left side has chars for print

	      printS(&M_left[lcounter], &counter, &lcounter);
	      if(lcounter >= l_size) setbit((lint*)&f,1,0b0); // left side hasnt chars for print

	  }else{
	      printf(" ");
	      counter++;
	  }

      }

      if(counter > 80) counter = 0;

      if(0 <= counter && counter <= 40) {
	  _nt_setbit(&f,0,0b0);
      }else{
	  _nt_setbit(&f,0,0b1);
      }

      /* debug
      printf("%2d [%u+%u] L(%u/%u) R(%u/%u) side->%s\n",
	     counter,
	     getbit((lint)f,1), getbit((lint)f,2),
	     lcounter,l_size,
	     rcounter,r_size,
	     (getbit((lint)f,0) ? "right" : "left"));

      */
  }

  puts("");

  // === END DRAWING ===

  free(M_left);
  free(M_right);

  getchar();

  return 0;
}


