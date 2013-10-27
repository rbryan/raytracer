/*This is where all of the pretty pictures are made (hopefully).
	Author: Russell Bryan


	TO DO:
	* Add double buffered output to framebuffer.
	* Real time movement.
	* Add light and shading.
	* Port to run on graphics card?



	LIST OF USED TEST POINTS:
	
	
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "typedefs.h"
#include "render.h"
#include "config.h"

camvector trace_list[WIDTH][HEIGHT];
pixel pixels[WIDTH][HEIGHT];
pixel* ppixel;

vector *ppoint_1;
vector *ppoint_2;
vector *ppoint_3;

vector polys[POLYS][3]; //You'll probably want to change the size of this array later.

int renderframe(){
	
	ppoint_1 = &polys[0][0];
	ppoint_2 = &polys[0][1];
	ppoint_3 = &polys[0][2];

	ppoint_1->x = 200;
	ppoint_1->y = 0;
	ppoint_1->z = 100;
	
	ppoint_2->x = 200;
	ppoint_2->y = 50;
	ppoint_2->z = 0;

	ppoint_3->x = 200;
	ppoint_3->y = -50;
	ppoint_3->z = 0;
	
	camera *pcam;													//MAKING CAMERA
	camera cam;
	pcam = &cam;
	cam.pitch = -1.4;
	cam.yaw = -3.141592653/2;
	cam.roll = 0;
	cam.x = 150;
	cam.y = -300;
	cam.z = 500;
	cam.fov = FOV;
	cam.scrn_w = WIDTH;
	cam.scrn_h = HEIGHT;

	camvector *pray; 

	FILE *ofp;									
	ofp = fopen("render_output","w");
	
	int x,y;								
	
	

	//int count = 0;
	
	//printf("HUGE: %lf\n", HUGE);
	for( y= 0; y != cam.scrn_h; y++){
		for( x=0 ; x != cam.scrn_w; x++){
		
			pray = &(trace_list[x][y]); 
			
			pray->collision_distance = HUGE;
			
			pray->x = cam.x;
			pray->y = cam.y;
			pray->z = cam.z;
			
			pray->pitch = (atan2((cam.scrn_h/2.0 - y),cam.fov)+cam.pitch); 
			pray->yaw = (atan2((x - cam.scrn_w/2.0),cam.fov)+cam.yaw);
			if(DEBUG){
				printf("pitch yaw:%lf %lf\n", pray->pitch, pray->yaw);
			}
			
			//raytrace(pcam,ppitch,pyaw,pray);
			if(raytrace(pcam,pray)){
				pray->r = 255;
				pray->g = 0;
				pray->b = 0;
				fprintf(ofp,"%d %d %d %d %d\n",x,y,pray->r,pray->g,pray->b);
			}
			
			//count++;
		}
		
	}
	fclose(ofp);
	return 1;
	
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int raytrace(camera *pcam, camvector *pray){
	static int poly;													//Maybe no need for static?
	for( poly=0 ; poly != POLYS; poly++){
		
		ppoint_1 = &polys[poly][0];
		ppoint_2 = &polys[poly][1];
		ppoint_3 = &polys[poly][2];
		traceout out;
		out = traceray(ppoint_1,ppoint_2,ppoint_3,pray);
		
		if(out.status){
			if(DEBUG){
				printf("HHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\nHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\nHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n");
				
				printf("intersection from out: %lf %lf %lf\n", out.intersect.x, out.intersect.y, out.intersect.z);
				printf("point1 from out: %lf %lf %lf\n\n", ppoint_1->x,ppoint_1->y,ppoint_1->z);
			}
			return 1;												//ADD FUNCTION FOR CHECKING SHADING
		}
	}

	return 0;
	
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



int trace(camera* pcam, camvector* pray,vector* ppoint_1, vector* ppoint_2, vector* ppoint_3){
	
	
	return 1;	//add extern to header
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_point(int test_number){
	if(DEBUG){
		printf("test_point# %d\n",test_number);
		fflush(stdout);
	}
}
