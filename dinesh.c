/*
 *   * hello.c -- A minimal Tcl C extension.
 *     */
 #include <tcl.h>
#include <stdio.h>
#include <stdlib.h> // For exit()

 static int 
 dinesh_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
 {
     //Tcl_SetObjResult(interp, Tcl_NewStringObj("dinesh, World!", -1));
		FILE *fp;
		long lSize;
		char *buffer = "set a 10";
		
		//fp = fopen ( "input.tcl" , "r" );
		//if( !fp ) perror("blah.txt"),exit(1);
		//
		//fseek( fp , 0L , SEEK_END);
		//lSize = ftell( fp );
		//rewind( fp );
		//
		///* allocate memory for entire content */
		//buffer = calloc( 1, lSize+1 );
		//if( !buffer ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);
		//
		///* copy the file into the buffer */
		//if( 1!=fread( buffer , lSize, 1 , fp) )
		//  fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);
		//
		///* do your work here, buffer is a string contains the whole text */
		//
		//printf("%s",buffer);
		//
		//fclose(fp);
     //int code = Tcl_EvalFile(interp,"./input.tcl");
		printf("count : %d\n",objc);
		printf("args : \n");
		int i;
		//index '0' will have the command name itself
		for(i=1;i<objc;i++) {
			printf("%d = %s\n",i,Tcl_GetString(objv[i]));
		}
		printf("");
     int code = Tcl_Eval(interp,buffer);
     const char *result = Tcl_GetStringResult(interp);
		 //printf("-->%s<--\n",result);
		 //free(buffer);
     return code;
 }

 /*
 *   * dinesh_Init -- Called when Tcl loads your extension.
 *     */
 int DLLEXPORT
 Dinesh_Init(Tcl_Interp *interp)
 {
     if (Tcl_InitStubs(interp, TCL_VERSION, 0) == NULL) {
         return TCL_ERROR;
     }
     /* changed this to check for an error - GPS */
     if (Tcl_PkgProvide(interp, "dinesh", "1.0") == TCL_ERROR) {
         return TCL_ERROR;
     }
     Tcl_CreateObjCommand(interp, "dinesh", dinesh_Cmd, NULL, NULL);
     return TCL_OK;
 }
