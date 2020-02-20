#include <stdio.h>
#include <stdlib.h> // For exit()
void decode_and_run(char *); 
 
void decode_and_run(char *str) {
	//int idx = 0;
	//while(str[idx]!='\0') {
	//	printf("%c\n",str[idx++]);
	//}
	FILE *fp;
	char buffer[31];
	fp = fopen(str,"r");
  if (fp == NULL) {
		printf("NOOO");
		return;
  } 
  while(fread(buffer,sizeof(char),31,fp)==31) {
    printf("%c",buffer[30]);
  }
  fclose(fp);
  //printf("decode ends\n");

}
int main()
{
		decode_and_run("test.c.obf");
    return 0;
}
