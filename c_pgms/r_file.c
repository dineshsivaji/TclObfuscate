#include <stdio.h>
#include <stdlib.h> // For exit()
 
int main() {
FILE *fp;
long lSize;
char *buffer;

fp = fopen ( "r_file.c" , "r" );
if( !fp ) perror("blah.txt"),exit(1);

fseek( fp , 0L , SEEK_END);
lSize = ftell( fp );
rewind( fp );

/* allocate memory for entire content */
buffer = calloc( 1, lSize+1 );
if( !buffer ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);

/* copy the file into the buffer */
if( 1!=fread( buffer , lSize, 1 , fp) )
  fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);

/* do your work here, buffer is a string contains the whole text */

printf("%s",buffer);

fclose(fp);
free(buffer);
}
