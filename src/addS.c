#include "../libs/types.h"

void* malloc(uint size);
int lenS(char*);

char* addS(char* str, char* substr){
   char* result;
   int len1 , len2;
   len1 = lenS(str)-1;
   len2 = lenS(substr)-1;
   result = malloc(len1+len2+1);
   int i;
   for(i=0; i<len1; i++) result[i] = str[i];
   for(i=0; i<len2; i++) result[i+len1] = substr[i];
   result[i+len1] = 0;
   return result;
}
