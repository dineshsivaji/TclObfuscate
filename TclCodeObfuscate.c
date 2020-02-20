/*
 *   * TclCodeObfuscate.c -- A minimal Tcl C extension.
 *     
*/
#include <tcl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // For exit(), rand(), srand()
#include <time.h> // For time()

#define CHUNK 1024
#define ENCODE_KEY 50


char *encode_text(char *); 
char *decode_text(char *); 
 
char *decode_text(char *filename) {
	FILE *fp;
	char buffer[ENCODE_KEY+1];
	char *result = NULL, *tmp = NULL;
  size_t size = 0, index = 0;
  fp = fopen(filename, "r");
  if (fp == NULL) {
		return "TCL_OBFUSCATE_INPUT_FILE_OPEN_ERROR";
  }
	int chars_to_read = ENCODE_KEY+1;
	while(fread(buffer,sizeof(char),chars_to_read,fp)==chars_to_read) {
		if (size <= index) {
		    size += CHUNK;
		    tmp = realloc(result, size);
		    if (!tmp) {
					// To avoid partial 'result' value, returning 'NULL' itself
					return "TCL_OBFUSCATE_MEMORY_FAILURE_FOR_INPUT_FILE_CONTENT";
		    }
		    result = tmp;
		}
		/* Actually store the thing. */
		result[index++] = buffer[ENCODE_KEY];
  }
	//To mark the end of the string, adding the 
	//string delimiter '\0'
	result[index++] = '\0';
	fclose(fp);
	return result;
}
char *encode_text(char *filename) {
    FILE *fptr;
    char  c;
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
    //printf("->%s<-\n", filename);
 
    // Open file
    fptr = fopen(filename, "r");
    if (fptr == NULL) {
			return "TCL_OBFUSCATE_INPUT_FILE_OPEN_ERROR";
    }
		int i; 
    // Read contents from file
    c = fgetc(fptr);
    while (c != EOF) {	
				for(i=0;i<ENCODE_KEY;i++) {
					int random = rand() % strlen(enc_chars);
					//printf ("%c", enc_chars[random]);
					 /* Check if we need to expand. */
					if (size <= index) {
					    size += CHUNK;
					    tmp = realloc(result, size);
					    if (!tmp) {
								// To avoid partial 'result' value, returning 'NULL' itself
								return "TCL_OBFUSCATE_MEMORY_FAILURE_FOR_INPUT_FILE_CONTENT";
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
    fclose(fptr);
		return result;
}
/*
int main() {
		char *enc_result = encode_text("encodetext.c");
		char *dec_result = decode_and_run(enc_result);
		printf("%d\n",strlen(dec_result));
		printf("%s\n",dec_result);
		free(enc_result);
		free(dec_result);
    return 0;
}
*/

 static int 
 Enc_File_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
 {
		FILE *fp;
		char *input_file;
		char *output_file;

		//printf("count : %d\n",objc);
		//printf("args : \n");
		//int i;
		////index '0' will have the command name itself
		//for(i=1;i<objc;i++) {
		//	printf("%d = %s\n",i,Tcl_GetString(objv[i]));
		//}
		//printf("");

		if (objc<2 || objc>3) {
			Tcl_WrongNumArgs(interp,1,objv,"inputfile ?outputfile?");
			return TCL_ERROR;
		} 
		input_file = Tcl_GetString(objv[1]);
		if(objc==3) {
			output_file = Tcl_GetString(objv[2]);
		} else {
			output_file = (char *)malloc((strlen(input_file)+10)*sizeof(char));
			if (output_file == NULL) {
				Tcl_SetObjResult(interp, Tcl_NewStringObj("Unable to allocate memory", -1));
				return TCL_ERROR;
			}
			memset(output_file, '\0', sizeof(output_file));
			strcpy(output_file,input_file);
			strcat(output_file,".obf");
		}
    //Tcl_SetObjResult(interp, Tcl_NewStringObj("Tclobfuscate, World!", -1));
    //Tcl_SetObjResult(interp, Tcl_NewStringObj(enc_result, -1));
		//printf("%s",input_file);
		char *enc_result = encode_text(input_file);
		if (enc_result == NULL) {
			Tcl_SetObjResult(interp, Tcl_NewStringObj("Empty inputfile ", -1));
			return TCL_ERROR;
		} else if(strcmp(enc_result,"TCL_OBFUSCATE_INPUT_FILE_OPEN_ERROR")==0) {
			Tcl_SetObjResult(interp, Tcl_NewStringObj("Unable to open the inputfile ", -1));
			return TCL_ERROR;
		} else if(strcmp(enc_result,"TCL_OBFUSCATE_MEMORY_FAILURE_FOR_INPUT_FILE_CONTENT")==0) {
			Tcl_SetObjResult(interp, Tcl_NewStringObj("Unable to allocate memory for inputfile content ", -1));
			return TCL_ERROR;
		} 
		fp = fopen(output_file,"w");
		if (fp==NULL) {
			Tcl_SetObjResult(interp, Tcl_NewStringObj("Unable to create the outputfile ", -1));
			return TCL_ERROR;
		}
		fprintf(fp,"%s",enc_result);
		fclose(fp);
		free(enc_result);
     //int code = Tcl_EvalFile(interp,"./input.tcl");
     //int code = Tcl_Eval(interp,buffer);
		Tcl_SetObjResult(interp,Tcl_NewBooleanObj(1));
		 //free(enc_result);
		 //free(input_file);
     return TCL_OK;
 }
 static int 
 Dec_File_And_Run_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
 {
		FILE *fp;
		char *input_file;

		if (objc!=2) {
			Tcl_WrongNumArgs(interp,1,objv,"inputfile");
			return TCL_ERROR;
		} 
		input_file = Tcl_GetString(objv[1]);
		char *dec_result = decode_text(input_file);
		if (dec_result == NULL) {
			Tcl_SetObjResult(interp, Tcl_NewStringObj("Empty inputfile ", -1));
			return TCL_ERROR;
		} else if(strcmp(dec_result,"TCL_OBFUSCATE_INPUT_FILE_OPEN_ERROR")==0) {
			Tcl_SetObjResult(interp, Tcl_NewStringObj("Unable to open the inputfile ", -1));
			return TCL_ERROR;
		} else if(strcmp(dec_result,"TCL_OBFUSCATE_MEMORY_FAILURE_FOR_INPUT_FILE_CONTENT")==0) {
			Tcl_SetObjResult(interp, Tcl_NewStringObj("Unable to allocate memory for inputfile content ", -1));
			return TCL_ERROR;
		} 
		int code = Tcl_Eval(interp,dec_result);
		//int code = TCL_OK;
		//const char *result = Tcl_GetStringResult(interp);
		free(dec_result);
		return TCL_OK;
 }

 /*
 *   * Tclobfuscate_Init -- Called when Tcl loads your extension.
 *     */
 int DLLEXPORT
 Tclobfuscate_Init(Tcl_Interp *interp)
 {
     if (Tcl_InitStubs(interp, TCL_VERSION, 0) == NULL) {
         return TCL_ERROR;
     }
     /* changed this to check for an error - GPS */
     if (Tcl_PkgProvide(interp, "Tclobfuscate", "1.0") == TCL_ERROR) {
         return TCL_ERROR;
     }
     Tcl_CreateObjCommand(interp, "enc_file", Enc_File_Cmd, NULL, NULL);
     Tcl_CreateObjCommand(interp, "dec_file_and_run", Dec_File_And_Run_Cmd, NULL, NULL);
     return TCL_OK;
 }
