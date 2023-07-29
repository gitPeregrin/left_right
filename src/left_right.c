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
  }else if(*str){
      char tmp = *(str+1);
      *(str+1) = 0;
      printf("%s",str);
      *(str+1) = tmp;
      *c = *c + 1;
      *lc = *lc + 1;
  }else{
      *lc = *lc + 1;
  }
}

int main(void) {

  char * left = "Левая часть консоли";
  char * right = "Right ""side"" of console.";

  char * M_left = mulS(left,10);
  char * M_right = mulS(right,10);

  enum {
    LEFT , RIGHT
  };

  uint lcounter, rcounter, counter;
  const uint l_size = lenS(M_left);
  const uint r_size = lenS(M_right);
  char f = 0;
  lcounter = rcounter = 0;
  counter = 1;

  #define lhasch	_nt_getbit(f,1)
  #define rhasch	_nt_getbit(f,2)
  #define side		_nt_getbit(f,0)
  #define isText	_nt_getbit(f,3)

  #define set_isText_false 	_nt_setbit(&f,3,0b0)
  #define set_isText_true 	_nt_setbit(&f,3,0b1)
  #define set_side_left 	_nt_setbit(&f,0,0b0)
  #define set_side_right 	_nt_setbit(&f,0,0b1)
  #define set_lhasch_false 	_nt_setbit(&f,1,0b0)
  #define set_lhasch_true 	_nt_setbit(&f,1,0b1)
  #define set_rhasch_false 	_nt_setbit(&f,2,0b0)
  #define set_rhasch_true 	_nt_setbit(&f,2,0b1)


  set_lhasch_true;
  set_rhasch_true;
  set_side_left;

  // === DRAWING ===

  puts("");

  while(lhasch || rhasch){

      switch(counter){
	case 1:
	  set_isText_false;
	  break;
	case 2:
	  set_isText_true;
	  set_side_left;
	  break;
	case 40:
	  set_isText_false;
	  set_side_right;
	  break;
	case 42:
	  set_isText_true;
	  break;
	case 78:
	  set_isText_false;
	  set_side_left;
	  break;
	case 80:
	  counter = 0;
	  break;
      }

      if(isText && lhasch && side == LEFT)
      	printS(&M_left[lcounter], &counter, &lcounter);

      if(isText && rhasch && side == RIGHT)
	printS(&M_right[rcounter], &counter, &rcounter);

      if(isText && !lhasch && side == LEFT) {
	  printf(" "); counter++;
      }

      if(isText && !rhasch && side == RIGHT) {
	  printf(" "); counter++;
      }

      if(!isText){
	  printf(" "); counter++;
      }

      if(lcounter >= l_size)
	set_lhasch_false;

      if(rcounter >= r_size)
	set_rhasch_false;

  }

  puts("end");

  // === END DRAWING ===

  free(M_left);
  free(M_right);

  getchar();

  return 0;
}


