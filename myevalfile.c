/*
 *   * hello.c -- A minimal Tcl C extension.
 *     */
 #include <tcl.h>

 static int 
 Myevalfile_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
 {
     //Tcl_SetObjResult(interp, Tcl_NewStringObj("Myevalfile, World!", -1));
     int code = Tcl_EvalFile(interp,"./input.tcl");
     char *result = Tcl_GetStringResult(interp);
     return code;
 }

 /*
 *   * Myevalfile_Init -- Called when Tcl loads your extension.
 *     */
 int DLLEXPORT
 Myevalfile_Init(Tcl_Interp *interp)
 {
     if (Tcl_InitStubs(interp, TCL_VERSION, 0) == NULL) {
         return TCL_ERROR;
     }
     /* changed this to check for an error - GPS */
     if (Tcl_PkgProvide(interp, "Myevalfile", "1.0") == TCL_ERROR) {
         return TCL_ERROR;
     }
     Tcl_CreateObjCommand(interp, "hello", Myevalfile_Cmd, NULL, NULL);
     return TCL_OK;
 }
