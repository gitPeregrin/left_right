#include <sys/ioctl.h>
#include <stdio.h>  
#include <stdlib.h>
#include <unistd.h>

#include "../libs/bits.h"
#include "../libs/colors.h"
#include "../libs/types.h"

#define min(a,b)        		(a < b ? a : b)
#define max(a,b)	         	(a < b ? b : a)
#define res(left,some,right)	(min(max(left,some),right))
#define isOdd(num)            (num%2)

#define false  0
#define true   1

#define lhasch	       _nt_getbit(f,1)
#define rhasch	       _nt_getbit(f,2)
#define side	       _nt_getbit(f,0)
#define isText	       _nt_getbit(f,3)

#define set_isText(b) _nt_setbit(&f,3,b)
#define set_side(b)   _nt_setbit(&f,0,b)
#define set_lhasch(b) _nt_setbit(&f,1,b)
#define set_rhasch(b) _nt_setbit(&f,2,b)

int cmpS(char*, char*);
uint lenS(char*);
char * mulS(char*, int);
void printS(char*, uint*, uint*, char*);

int main(void) {

   struct winsize w;
   ioctl(STDOUT_FILENO , TIOCGWINSZ , &w);

   char* left = "Левая " strRED "часть" strDEF " консоли";
   char* right = "Right " strBLUE "side of" strDEF " console.";

   char lColor[20] = {0};
   char rColor[20] = {0};

   char* M_left = mulS(left,100);
   char* M_right = mulS(right,100);

   unsigned char border , console_width , area;
   
   border = 1;
   console_width = w.ws_col;
   area = (console_width - border * 3) / 2;
   
   const uint left_border = border;
   const uint left_column = left_border + border;
   const uint center_border = left_column + area - border;
   const uint right_column = center_border + \
       border * (isOdd(console_width) ? 1 : 2);
   const uint right_border = right_column + area - border;

   enum { LEFT , RIGHT };

   uint lcounter, rcounter, counter;
   const uint l_size = lenS(M_left);
   const uint r_size = lenS(M_right);
   char f = 0;
   lcounter = rcounter = 0;
   counter = 1;
   
   set_lhasch(true);
   set_rhasch(true);
   set_side(LEFT);

   // === DRAWING ===

   for(int i = 0; i < border; i++) putchar('\n'); 

   while(lhasch || rhasch){

      if(counter == left_border){
         set_isText(false);
      }

      if(counter == left_column){
         set_isText(true); set_side(LEFT);
      }

      if(counter == center_border){
         set_isText(false); set_side(RIGHT);
      }

      if(counter == right_column){
         set_isText(true);
      }

      if(counter == right_border){
         set_isText(false); set_side(LEFT);
      }

      if(counter == console_width){
         counter = 0;
      } 

      if(isText && lhasch && side == LEFT)
         printS(&M_left[lcounter], &counter, &lcounter, lColor);

      if(isText && rhasch && side == RIGHT)
         printS(&M_right[rcounter], &counter, &rcounter, rColor);

      if(isText && !lhasch && side == LEFT) {
         putchar(' '); counter++;
      }

      if(isText && !rhasch && side == RIGHT) {
         putchar(' '); counter++;
      }

      if(!isText){
         putchar(' '); counter++;
      }

      if(lcounter >= l_size)
	      set_lhasch(false);

      if(rcounter >= r_size)
	      set_rhasch(false);

   }

   for(int i = 0; i < border; i++) putchar('\n'); 

   // === END DRAWING ===

   free(M_left);
   free(M_right);
   return 0;
}
