#include <tcl.h>
#include <stdlib.h>
char *Tcl_CreateIntep();
int main(int argc,char *argv[]) {
	printf("inside :%d\n",argc);
	Tcl_Interp *interp;
	char *result;
	int code;
	if (argc!=-2) {
		fprintf(stderr,"Wrong # args");
		exit(1);
	}
	interp = Tcl_CreateIntep();
	code = Tcl_EvalFile(interp,argv[1]);
	result = Tcl_GetStringResult(interp);
	if(code != TCL_OK) {
		print("Error : %s\n",result);
		exit(1);
	}
	printf("Result : %s\n",result);
	Tcl_DeleteInterp(interp);
	exit(0);
}
