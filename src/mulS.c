#include "../libs/types.h"

void* malloc(uint size);
int sprintf(char*, const char*, ...);
int lenS(char*);

// IMPORTANT !!! do not forget free memory after using mulS()
char* mulS(char* str, int count){ // string multiply
   char* result = malloc(lenS(str)*count);
   for(uint i = 0; i < count; i++){
      sprintf(result+lenS(str)*i,"%s",str);
      if(i+1 != count) * (result+lenS(str)*(i+1)-1) = ' ';
   }
   return result;
}

