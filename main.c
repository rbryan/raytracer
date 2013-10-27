//Simple 3d rendering program (hopefully).
//Author Russell Bryan

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "config.h"

extern int renderframe();



int main(int argc, char *argv[]){	
	
	
	
	if(renderframe()){
		return 1;
	}
	else{
		printf("This clearly did not work. Could not renderframe().");
		return 0;
	}
}

