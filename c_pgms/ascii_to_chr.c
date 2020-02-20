#include <stdio.h>
#include <stdlib.h> // For exit()
 
int main()
{
    FILE *fptr;
 
    char filename[100], c;
    int i,j;
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
		for(j=0;j<11;j++) {
			fscanf(fptr,"%c",&c);
		}
    while (!feof(fptr)) {	
      printf ("%c", c);
			for(j=0;j<11;j++) {
				fscanf(fptr,"%c",&c);
			}
    }
 
    fclose(fptr);
    return 0;
}
