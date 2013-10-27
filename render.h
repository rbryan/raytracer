#include <stdio.h>
#include <stdlib.h>

extern int raytrace(camera *pcam, camvector *pray);

extern int trace(camera *pcam, camvector *pray,vector* ppoint_1, vector* ppoint_2, vector* ppoint_3);

extern void test_point(int test_number);


//-----------------------------------------------------------------------------------------------------------------------------
//THESE ARE IN TRACE.C
//-----------------------------------------------------------------------------------------------------------------------------

extern traceout traceray(vector* ppoint_1, vector* ppoint_2, vector* ppoint_3, camvector* pray);