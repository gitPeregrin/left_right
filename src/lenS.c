#include "../libs/types.h"

uint lenS(char* str){
   uint result = 0;
   while(str[result] != 0) result++;
   return result+1;
}
