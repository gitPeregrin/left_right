#include "../libs/colors.h"
#include "../libs/types.h"

int printf(const char*,...);
void free(void*);

int lenS(char*);
char* addS(char*, char*);

int printS(char* str, uint* c, uint* lc , char* color){
   if(*str < 0){ // ru unicode
      char tmp = *(str+2);
      *(str+2) = 0;
      char* coloredStr = addS(color,str);
      printf("%s",coloredStr);
      free(coloredStr);
      *(str+2) = tmp;
      *c = *c + 1;
      *lc = *lc + 2;
      return 0;
   }else if(*str == 27){ // escape sequence
      uchar i = 0;
      while( *(str+i) != 109) i++;
      char tmp = *(str+i+1);
      *(str+i+1) = 0;
      *color = *str;
      *(str+i+1) = tmp;
      *lc = *lc + i;
      return 0;
   }else if(*str){ // eng unicode
      char tmp = *(str+1);
      *(str+1) = 0;
      char* coloredStr = addS(color,str);
      printf("%s",coloredStr);
      free(coloredStr);
      *(str+1) = tmp;
      *c = *c + 1;
      *lc = *lc + 1;
      return 0;
   }else{ // have no idea about char in str
      *lc = *lc + 1;
      return -1;
   }
}
