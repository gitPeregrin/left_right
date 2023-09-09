int cmpS(char* str1, char* str2){
   int i = 0;
   while(1){
      if(str1[i] != str2[i]) return -1;// NOT compare
      if(str1[i] == 0) return 0; // compare               
      i++;                                                   
   }                                                         
}      

