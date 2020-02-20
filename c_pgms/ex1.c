#include<stdio.h>

int main () {
   FILE *fp;
   char str[] = "This is tutorialspoint.com";

   fp = fopen( "file.txt" , "wb" );
   fwrite(&str , sizeof(str),1 , fp );

   fclose(fp);
  
   return(0);
}
