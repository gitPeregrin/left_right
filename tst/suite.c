#include "../libs/colors.h"
#include "../libs/types.h"

int puts(const char*);
void* malloc(uint size);
void free(void*);

char* addS(char*, char*);
int cmpS(char*, char*);
int lenS(char*);
char * mulS(char*, int);
int printS(char*, uint*, uint*, char*);

int main(void){
   int result = 0;

   {// test for lenS
      char test[] = "Hello";
      int len = sizeof(test);
      if( len != lenS(test) ){
         puts(strRED "FAILED:" strDEF " lenS");
         return -1;
      }else{
         puts(strGREEN "OK:" strDEF " lenS");
      }
   }

   {// test for cmpS
      if( cmpS("Hello","Hello") != 0  ){
         puts(strRED "FAILED:" strDEF " cmpS");
         return -1;
      }else{
         puts(strGREEN "OK:" strDEF " cmpS");
      }
   }

   {// test for mulS
      char* test = mulS("HE",2);
      if( cmpS(test,"HE HE")!=0 ){
         free(test);
         puts(strRED "FAILED:" strDEF " mulS");
         return -1;
      }else{
         free(test);
         puts(strGREEN "OK:" strDEF " mulS");
      }
   }

   {// test for addS
      char* test = addS("Hello,"," world!");
      if( cmpS(test,"Hello, world!")!=0 ){
         free(test);
         puts(strRED "FAILED:" strDEF " addS");
         return -1;
      }else{
         free(test);
         puts(strGREEN "OK:" strDEF " addS");
      }
   }

   {// test for printS
      uint c = 0, lc = 0;
      char str[] = strRED;
      char* cc = malloc(lenS(str));
      int result = printS(str,&c,&lc,cc);
      if( result !=0 ){
         free(cc);
         puts(strRED "FAILED:" strDEF " printS");
         return -1;
      }else{
         free(cc);
         puts(strGREEN "OK:" strDEF " printS");
      }
   }

  return result;
}
