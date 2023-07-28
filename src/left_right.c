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

uint printS(char * str, uint c){
  if(*str == -48){
      char tmp = *(str+2);
      *(str+2) = 0;
      printf("%s",str);
      *(str+2) = tmp;
      c++;
      return c;
  }else if(*str == 27){
      uchar i = 0;
      while( *(str+i) != 109) i++;
      char tmp = *(str+i+1);
      *(str+i+1) = 0;
      printf("%s", str);
      *(str+i+1) = tmp;
      return c;
  }else{
      char tmp = *(str+1);
      *(str+1) = 0;
      printf("%s",str);
      *(str+1) = tmp;
      c++;
      return c;
  }
}

int main(void) {

  char * left = "Левая часть консоли";
  char * right = "Right ""side"" of console.";
  char * spec = strRED "special" strDEF;



  // === DRAWING ===

  char * M_left = mulS(left,10);
  char * M_right = mulS(right,10);

  char * pS;

  enum {
    LEFT , RIGHT
  };

  uint lcounter, rcounter, counter;
  uint l_size, r_size;
  _Bool side, lHasChars, rHasChars;
  lcounter = rcounter = counter = 0;
  side = LEFT;
  lHasChars = rHasChars = 1;
  l_size = lenS(M_left);
  r_size = lenS(M_right);




  while(lHasChars || rHasChars){



      printf("%d [%d+%d] L(%d/%d) R(%d/%d) side->%s\n",
	     counter,
	     lHasChars, rHasChars,
	     lcounter,l_size,
	     rcounter,r_size,
	     (side == LEFT ? "LEFT" : "RIGHT"));

      if(counter > 80) counter = 0;

  }


  //TODO путчар не годится, надо попробовать принтф(%s) через поинтеры
  //	 и временную замену одного символа на \0 и обратно

  puts("");

  // === END DRAWING ===

  free(M_left);
  free(M_right);

  getchar();

  return 0;
}


