#include <stdio.h>
#include <string.h>
#include <stdlib.h> // For exit(), rand(), srand()
#include <time.h> // For time()
char *encode_text(char *); 
char *decode_and_run(char *); 
 
char *decode_and_run(char *str) {
	//printf("decode starts\n");
	int CHUNK = 1024;
	char *result = NULL, *tmp = NULL;
  size_t size = 0, index = 0;
	int i;
	for(i=0;i<strlen(str);i++) {
		if((i+1)%31==0) {
			if (size <= index) {
			    size += CHUNK;
			    tmp = realloc(result, size);
					//printf("allocation memory now..\n");
			    if (!tmp) {
							printf("Failed to allocate memory\n");
			        exit(1);
			    }
			    result = tmp;
					//printf("allocation memory - done\n");
			}
			/* Actually store the thing. */
			result[index++] = str[i];
		}
	}
	//printf("decode ends\n");
	return result;
}
char *encode_text(char *filename) {
		//printf("encode starts\n");
    FILE *fptr;
    char  c;
		int CHUNK = 1024;
    char enc_chars[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G',
                       'H', 'I', 'J', 'K', 'L', 'M', 'N',
                       'O', 'P', 'Q', 'R', 'S', 'T', 'U',
                       'V', 'W', 'X', 'Y', 'Z','a', 'b', 
                       'c', 'd', 'e', 'f', 'g',
                       'h', 'i', 'j', 'k', 'l', 'm', 'n', 
                       'o', 'p', 'q', 'r', 's', 't', 'u',
                       'v', 'w', 'x', 'y', 'z',
			'!','@','#', '$','%','^','&','(',')', '{','}',
			'=','+','-','_','[',']','<','>','?',
			'0','1','2','3','4','5','6','7','8','9'};

		char *result = NULL, *tmp = NULL;
    size_t size = 0, index = 0;
    srand ( time(NULL) );
    //printf("Random : %d\n",random);
    //printf("alpha : %c\n",enc_chars[random]);
    //printf("Enter the filename to open \n");
    //scanf("%s", filename);
 
    // Open file
    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
		int i; 
    // Read contents from file
    c = fgetc(fptr);
    while (c != EOF) {	
				for(i=0;i<30;i++) {
					int random = rand() % strlen(enc_chars);
					//printf ("%c", enc_chars[random]);
					 /* Check if we need to expand. */
					if (size <= index) {
					    size += CHUNK;
					    tmp = realloc(result, size);
					    if (!tmp) {
									printf("Failed to allocate memory\n");
					        exit(1);
					    }
					    result = tmp;
					}
					/* Actually store the thing. */
					result[index++] = enc_chars[random];
        }
				result[index++] = c;
				//int random = rand() % 70;
				//printf ("%c%d", enc_chars[random],c);
        //printf ("%c", c);
        c = fgetc(fptr);
    }
		//printf("INDEX : %d\n",index);
		//printf("\n");
    fclose(fptr);
		//printf("encode ends\n");
		return result;
}
int main() {
		char *enc_result = encode_text("encodetext.c");
		char *dec_result = decode_and_run(enc_result);
		printf("%d\n",strlen(dec_result));
		printf("%s\n",dec_result);
		free(enc_result);
		free(dec_result);
    return 0;
}
