#include <stdio.h>
#include <stdlib.h> // For exit()
 
int main()
{
    FILE *fptr;
 
    char filename[100], c;
		int ascii = -1;

    char alphabets[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G',
                       'H', 'I', 'J', 'K', 'L', 'M', 'N',
                       'O', 'P', 'Q', 'R', 'S', 'T', 'U',
                       'V', 'W', 'X', 'Y', 'Z','a', 'b', 
                       'c', 'd', 'e', 'f', 'g',
                       'h', 'i', 'j', 'k', 'l', 'm', 'n', 
                       'o', 'p', 'q', 'r', 's', 't', 'u',
                       'v', 'w', 'x', 'y', 'z',
			'!','@','#', '$','%','^','&','(',')',
			'=','+','-','_','[',']','<','>','?'};
     
    srand ( time(NULL) );
    //printf("Random : %d\n",random);
    //printf("alpha : %c\n",alphabets[random]);
    printf("Enter the filename to open \n");
    scanf("%s", filename);
 
    // Open file
    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
 
    // Read contents from file
    c = fgetc(fptr);
    while (c != EOF)
    {	
        int random = rand() % 70;
        //printf ("%c%d", alphabets[random],c);
				ascii = c+1;
        printf ("%c", ascii);
        c = fgetc(fptr);
    }
 
    fclose(fptr);
    return 0;
}
