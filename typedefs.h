//type used for storing pixel data.
typedef struct {
	int x;
	int y;
	int r;
	int g;
	int b;
	int a;
} pixel;

//type usually used to represend a point.
typedef struct {
	double x; 
	double y; 
	double z;
} vector;

//type usually used for rays
typedef struct {
	double x,y,z; 
	double x2,y2,z2;
	double pitch, yaw;
	int r,g,b;
	double collision_distance;
} camvector;

//type for camera
typedef struct {
	double pitch,yaw,roll;
	double x,y,z;
	double fov;
	unsigned int scrn_w,scrn_h;
} camera;

//format for output of traceray function
typedef struct {
	int status;
	int both;
	vector intersect;
} traceout;
