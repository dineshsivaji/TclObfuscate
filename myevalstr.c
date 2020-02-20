/*
 *   * hello.c -- A minimal Tcl C extension.
 *     */
 #include <tcl.h>
#include <stdio.h>
#include <stdlib.h> // For exit()

 static int 
 Myevalstr_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
 {
     //Tcl_SetObjResult(interp, Tcl_NewStringObj("Myevalstr, World!", -1));
		FILE *fp;
		long lSize;
		char *buffer;
		
		fp = fopen ( "input.tcl" , "r" );
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
     //int code = Tcl_EvalFile(interp,"./input.tcl");
     int code = Tcl_Eval(interp,buffer);
     const char *result = Tcl_GetStringResult(interp);
		free(buffer);
     return code;
 }

 /*
 *   * Myevalstr_Init -- Called when Tcl loads your extension.
 *     */
 int DLLEXPORT
 Myevalstr_Init(Tcl_Interp *interp)
 {
     if (Tcl_InitStubs(interp, TCL_VERSION, 0) == NULL) {
         return TCL_ERROR;
     }
     /* changed this to check for an error - GPS */
     if (Tcl_PkgProvide(interp, "Myevalstr", "1.0") == TCL_ERROR) {
         return TCL_ERROR;
     }
     Tcl_CreateObjCommand(interp, "hello", Myevalstr_Cmd, NULL, NULL);
     return TCL_OK;
 }
