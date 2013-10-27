//This might be improved by reworking with more pointers or by comparing to more than one polygon corner.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "config.h"
#include "typedefs.h"

extern double dotproduct(vector a, vector b);
int in_angle(vector vec1, vector vec2, vector point1, vector point2, vector point3, vector intersect);

static vector point1,point2,point3;

static vector intersect;
static vector components;
static vector vec1_2,vec1_3,vec2_1,vec2_3, vec3_2, vec3_1,vec1_inter,vec2_inter;

static double n1,n2,n3;
static double dot_product,dot1,dot2;

static vector checks;

static double theta, theta_intersect, theta_intersect2;

static double dist1_2,dist2_1, dist1_3,dist2_3, dist1_inter,dist2_inter;

static double collision_distance;

static traceout output;

traceout traceray(vector* ppoint_1, vector* ppoint_2, vector* ppoint_3,camvector* pray){
	
	//translates the location of the entire ray polygon system so that the origin of the ray is the origin (0,0,0).
	point1.x = ppoint_1->x - pray->x;
	point1.y = ppoint_1->y - pray->y;
	point1.z = ppoint_1->z - pray->z;
	
	point2.x = ppoint_2->x - pray->x;
	point2.y = ppoint_2->y - pray->y;
	point2.z = ppoint_2->z - pray->z;
	
	point3.x = ppoint_3->x - pray->x;
	point3.y = ppoint_3->y - pray->y;
	point3.z = ppoint_3->z - pray->z;
	
	//finds proportional x and y components of the ray vector for a parametric vector. 
	//parametric: <xt,yt,zt> = <components.x, components.y, components.z>
	components.x = 1;
	components.y = tan(pray->yaw);
	components.z = tan(pray->pitch);
	
	/*
	components.x = cos(pray->yaw);
	components.y = sin(pray->yaw);
	components.z = sin(pray->pitch);
	*/
	//components of vector going from point 1 to point 2 (vec1_2)
	vec1_2.x = point2.x - point1.x;
	vec1_2.y = point2.y - point1.y;
	vec1_2.z = point2.z - point1.z;
	
	//components of vector going from point 1 to point 3 (vec1_3)
	vec1_3.x = point3.x - point1.x;
	vec1_3.y = point3.y - point1.y;
	vec1_3.z = point3.z - point1.z;
	
	//components of a vector going from point 2 to point 1 (vec2_1)
	vec2_1.x = point1.x - point2.x;
	vec2_1.y = point1.y - point2.y;
	vec2_1.z = point1.z - point2.z;
	
	//components of a vector going from point 2 to point 3 (vec2_3)
	vec2_3.x = point3.x - point2.x;
	vec2_3.y = point3.y - point2.y;
	vec2_3.z = point3.z - point2.z;
	
	vec3_2.x = -1*vec2_3.x;
	vec3_2.y = -1*vec2_3.y;
	vec3_2.z = -1*vec2_3.z;
	
	vec3_1.x = -1*vec1_3.x;
	vec3_1.y = -1*vec1_3.y;
	vec3_1.z = -1*vec1_3.z;

	
	//this finds the cross product of vec1_2 and vec1_3 (<n1,n2,n3>)
	n1 = vec1_2.y*vec1_3.z - vec1_2.z*vec1_3.y;	
	n2 = vec1_2.z*vec1_3.x - vec1_2.x*vec1_3.z;
	n3 = vec1_2.x*vec1_3.y - vec1_2.y*vec1_3.x;
	
	// equation of the plane of the three points is:
	//n1(components.x * t - point1.x) + n2(components.y * t - point1.y) + n3(components.z * t - point1.z) = 0
	//when solved for t (the collision distance (essentially)):
	collision_distance = (n1*point1.x + n2*point1.y + n3*point1.z)/(n1*components.x + n2*components.y + n3*components.z);
	
	//calculates the intersection point
	intersect.x = components.x*collision_distance;
	intersect.y = components.y*collision_distance;
	intersect.z = components.z*collision_distance;
	
	if(DEBUG){
		
		printf("point1: %lf %lf %lf\n", point1.x,point1.y,point1.z);
		printf("point2: %lf %lf %lf\n", point2.x,point2.y,point2.z);
		printf("point3: %lf %lf %lf\n", point3.x,point3.y,point3.z);
		printf("ray components: %lf %lf %lf\n", components.x,components.y,components.z);
		printf("vec1_2: %lf %lf %lf\n",vec1_2.x,vec1_2.y,vec1_2.z);
		printf("vec1_3: %lf %lf %lf\n",vec1_3.x,vec1_3.y,vec1_3.z);
		printf("vec2_1: %lf %lf %lf\n",vec2_1.x,vec2_1.y,vec2_1.z);
		printf("vec2_3: %lf %lf %lf\n",vec2_3.x,vec2_3.y,vec2_3.z);
		printf("cross_product: %lf %lf %lf\n",n1,n2,n3);
		printf("collision_dist: %lf\n",collision_distance);
		printf("intersect: %lf %lf %lf\n",intersect.x, intersect.y, intersect.z);

	}
	
	//HERE BEGINS THE CHECK FOR IN POLYGON===========================================================<
	/*
			//this finds the dot product of vec1_2 and vec2
			dot1 = dotproduct(vec1_2,vec1_3);
			
			//this calculates the distance from point1 to the ray intersection
			dist1_inter = sqrt( pow(intersect.x-point1.x,2) + pow(intersect.y-point1.y,2) + pow(intersect.z-point1.z,2));
			dist1_2 = sqrt( pow(point2.x-point1.x,2) + pow(point2.y-point1.y,2) + pow(point2.z-point1.z,2));
			dist1_3 = sqrt( pow(point3.x-point1.x,2) + pow(point3.y-point1.y,2) + pow(point3.z-point1.z,2));
			
			//components of a vector going from point1 to intersection (vec1_inter)
			vec1_inter.x = intersect.x - point1.x;
			vec1_inter.y = intersect.y - point1.y;
			vec1_inter.z = intersect.z - point1.z;
			
			dot2 = dotproduct(vec1_inter,vec1_2);
			
			//a(dot)b = |a||b|Cos(theta)
			//angle between the two vectors
			theta = acos(dot1/(dist1_2*dist1_3));
			theta_intersect = acos(dotproduct(vec1_inter,vec1_2)/(dist1_inter*dist1_2)); 
	
	if(theta >= theta_intersect){
		checks.x = 1;
	}
	
			//this finds the dot product of vec1_2 and vec2
			dot1 = dotproduct(vec2_1,vec2_3);
			
			//this calculates the distance from point1 to the ray intersection
			dist1_inter = sqrt( pow(intersect.x-point2.x,2) + pow(intersect.y-point2.y,2) + pow(intersect.z-point2.z,2));
			dist2_1= sqrt( pow(point1.x-point2.x,2) + pow(point1.y-point2.y,2) + pow(point1.z-point2.z,2));
			dist2_3 = sqrt( pow(point3.x-point2.x,2) + pow(point3.y-point2.y,2) + pow(point3.z-point2.z,2));
			
			//components of a vector going from point1 to intersection (vec1_inter)
			vec2_inter.x = intersect.x - point2.x;
			vec2_inter.y = intersect.y - point2.y;
			vec2_inter.z = intersect.z - point2.z;
			
			dot2 = dotproduct(vec2_inter,vec2_1);
			
			//a(dot)b = |a||b|Cos(theta)
			//angle between the two vectors
			theta = acos(dot1/(dist2_1*dist2_3));
			theta_intersect = acos(dotproduct(vec2_inter,vec2_1)/(dist2_inter*dist2_1)); 
	
	if(theta >= theta_intersect){
		checks.y = 1;
	}

	
	if(checks.x == 1 && checks.y==1){
		output.status = 1;
	}
	*/
	output.status = 0;
	
	if(in_angle(vec1_2,vec1_3,point1,point2,point3,intersect) ){
		if (in_angle(vec2_1,vec2_3,point2,point1,point3,intersect)) {
			if(in_angle(vec3_2,vec3_1,point3,point2,point1,intersect)){
				if(DEBUG) {
					printf("\n\n\npassed in_angle() check\n\n\n");
				}
				output.status = 1;
			}
		}
	}
	
	
		
	
	
	//HERE ENDS THE CHECK FOR IN POLYGON============================================================<
	if(collision_distance < pray->collision_distance){
		output.intersect = intersect;
	}
	
	
	return output;
}
//THE PROBLEM(S) LIES HERE!!!!!!!!!!!!!!!!!!!!!

int in_angle(vector vec1/*p1->p2*/, vector vec2/*p1->p3*/, vector point1/*vertex of angle*/, vector point2, vector point3, vector intersect){ 
	
	//this finds the dot product of vec1_2 and vec2
	dot_product = dotproduct(vec1,vec2);
	
	//this calculates the distance from point1 to point2
	dist1_2 = sqrt( pow(point2.x-point1.x,2) + pow(point2.y-point1.y,2) + pow(point2.z-point1.z,2));		//Redundant use vec1.x for point2.x-point1.x
	
	//this calculates the distance from point1 to point3
	dist1_3 = sqrt( pow(point3.x-point1.x,2) + pow(point3.y-point1.y,2) + pow(point3.z-point1.z,2));
	
	//this calculates the distance from point1 to the ray intersection
	dist1_inter = sqrt( pow(intersect.x-point1.x,2) + pow(intersect.y-point1.y,2) + pow(intersect.z-point1.z,2));
	
	
	//components of a vector going from point1 to intersection (vec1_inter)
	vec1_inter.x = intersect.x - point1.x;
	vec1_inter.y = intersect.y - point1.y;
	vec1_inter.z = intersect.z - point1.z;
	
	
	//a(dot)b = |a||b|Cos(theta)
	//angle between the two vectors
	theta = acos(dot_product/(dist1_2*dist1_3));
/*Simon removed code	
	//angle between vec1 and vec1_inter
	theta_intersect = acos(dotproduct(vec1_inter,vec1)/(dist1_inter*dist1_2)); 
	
	//printf("theta: %lf inter_angle: %lf\n",theta, theta_intersect);
	if(theta >= theta_intersect){
		return 1;
	}
*/
//Start Simon added code
	//angle between vec1 and vec1_inter
	theta_intersect = acos(dotproduct(vec1_inter,vec1)/(dist1_inter*dist1_2)); 
	//angle between vec2 and vec1_inter
	theta_intersect2 = acos(dotproduct(vec1_inter,vec2)/(dist1_inter*dist1_3)); 
	//I bleive this secondary check to be necessary since the angles you are getting are absolute values. For instance,
	//a point which is outside of a 20 degree angle by 10 degrees on the proper side will register as inside.
	//The if statement below ensures that this won't happen.
	
	
	//printf("theta: %lf inter_angle: %lf\n",theta, theta_intersect);
	if(theta >= theta_intersect && theta >= theta_intersect2){
		return 1;
	}

//End Simon added code
	return 0;
}

double dotproduct(vector a, vector b){
	return (a.x*b.x+a.y*b.y+a.z*b.z);
}


