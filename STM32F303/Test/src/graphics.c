//-----------------------------------------------------------------------------
//
//    THE SOFTWARE INCLUDED IN THIS FILE IS FOR GUIDANCE ONLY.
//    BTC KORPORACJA SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
//    OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
//    FROM USE OF THIS SOFTWARE.
//
//                     http://www kamami.com
//-----------------------------------------------------------------------------

#include "lcdlib.h"
#include "math.h"

#define CUBE_WIDTH_HALF	70	// Half of cube width
#define PERSPECTIVE_ORIGIN_DISTANCE		300.0
#define PERSPECTIVE_SURFACE_DICTANCE	100.0
#define PERSPECTIVE_RATIO PERSPECTIVE_SURFACE_DICTANCE/PERSPECTIVE_ORIGIN_DISTANCE

typedef struct
{
	unsigned short x, y;
} point;

typedef struct
{
	float x0, y0, z0, x1, y1, z1;
} line3D;

point points[400], oldPoints[400];
int pointCount, oldPointCount;



// cube stores cube coordinates
// rotatedCube will be used to store cube coordinates after transformations
line3D rotatedCube[12], cube[12]=
{
	{-CUBE_WIDTH_HALF, CUBE_WIDTH_HALF, -CUBE_WIDTH_HALF, -CUBE_WIDTH_HALF, CUBE_WIDTH_HALF, CUBE_WIDTH_HALF},
	{CUBE_WIDTH_HALF, CUBE_WIDTH_HALF, -CUBE_WIDTH_HALF, CUBE_WIDTH_HALF, CUBE_WIDTH_HALF, CUBE_WIDTH_HALF},
	{-CUBE_WIDTH_HALF, -CUBE_WIDTH_HALF, -CUBE_WIDTH_HALF, -CUBE_WIDTH_HALF, -CUBE_WIDTH_HALF, CUBE_WIDTH_HALF},
	{CUBE_WIDTH_HALF, -CUBE_WIDTH_HALF, -CUBE_WIDTH_HALF, CUBE_WIDTH_HALF, -CUBE_WIDTH_HALF, CUBE_WIDTH_HALF},

	{-CUBE_WIDTH_HALF, -CUBE_WIDTH_HALF, -CUBE_WIDTH_HALF, -CUBE_WIDTH_HALF, CUBE_WIDTH_HALF, -CUBE_WIDTH_HALF},
	{CUBE_WIDTH_HALF, -CUBE_WIDTH_HALF, -CUBE_WIDTH_HALF, CUBE_WIDTH_HALF, CUBE_WIDTH_HALF, -CUBE_WIDTH_HALF},
	{CUBE_WIDTH_HALF, -CUBE_WIDTH_HALF, CUBE_WIDTH_HALF, CUBE_WIDTH_HALF, CUBE_WIDTH_HALF, CUBE_WIDTH_HALF},
	{-CUBE_WIDTH_HALF, -CUBE_WIDTH_HALF, CUBE_WIDTH_HALF, -CUBE_WIDTH_HALF, CUBE_WIDTH_HALF, CUBE_WIDTH_HALF},

	{-CUBE_WIDTH_HALF, -CUBE_WIDTH_HALF, -CUBE_WIDTH_HALF, CUBE_WIDTH_HALF, -CUBE_WIDTH_HALF, -CUBE_WIDTH_HALF},
	{-CUBE_WIDTH_HALF, -CUBE_WIDTH_HALF, CUBE_WIDTH_HALF, CUBE_WIDTH_HALF, -CUBE_WIDTH_HALF, CUBE_WIDTH_HALF},
	{-CUBE_WIDTH_HALF, CUBE_WIDTH_HALF, -CUBE_WIDTH_HALF, CUBE_WIDTH_HALF, CUBE_WIDTH_HALF, -CUBE_WIDTH_HALF},
	{-CUBE_WIDTH_HALF, CUBE_WIDTH_HALF, CUBE_WIDTH_HALF, CUBE_WIDTH_HALF, CUBE_WIDTH_HALF, CUBE_WIDTH_HALF}
};



float sinus[128]={
0,					// sin (0 * 360 deg. / 128)
0.049067674	,		// sin (1 * 360 deg. / 128)
0.09801714	,		// sin (2 * 360 deg. / 128)
0.146730474	,		// ...
0.195090322	,
0.24298018	,
0.290284677	,
0.336889853	,
0.382683432	,
0.427555093	,
0.471396737	,
0.514102744	,
0.555570233	,
0.595699305	,
0.634393284	,
0.671558955	,
0.707106781	,
0.740951125	,
0.773010453	,
0.803207532	,
0.831469612	,
0.85772861	,
0.881921264	,
0.903989293	,
0.923879533	,
0.941544065	,
0.956940336	,
0.970031253	,
0.98078528	,
0.98917651	,
0.995184727	,
0.998795456	,
1	,
0.998795456	,
0.995184727	,
0.98917651	,
0.98078528	,
0.970031253	,
0.956940336	,
0.941544065	,
0.923879532	,
0.903989293	,
0.881921264	,
0.85772861	,
0.831469612	,
0.803207531	,
0.773010453	,
0.740951125	,
0.707106781	,
0.671558955	,
0.634393284	,
0.595699304	,
0.555570233	,
0.514102744	,
0.471396737	,
0.427555093	,
0.382683432	,
0.336889853	,
0.290284677	,
0.24298018	,
0.195090322	,
0.146730474	,
0.09801714	,
0.049067674	,
0	,
-0.049067675	,
-0.098017141	,
-0.146730475	,
-0.195090322	,
-0.24298018	,
-0.290284678	,
-0.336889854	,
-0.382683433	,
-0.427555094	,
-0.471396737	,
-0.514102745	,
-0.555570233	,
-0.595699305	,
-0.634393285	,
-0.671558955	,
-0.707106782	,
-0.740951126	,
-0.773010454	,
-0.803207532	,
-0.831469613	,
-0.85772861	,
-0.881921265	,
-0.903989293	,
-0.923879533	,
-0.941544065	,
-0.956940336	,
-0.970031253	,
-0.980785281	,
-0.98917651	,
-0.995184727	,
-0.998795456	,
-1	,
-0.998795456	,
-0.995184727	,
-0.98917651	,
-0.98078528	,
-0.970031253	,
-0.956940336	,
-0.941544065	,
-0.923879532	,
-0.903989293	,
-0.881921264	,
-0.85772861	,
-0.831469612	,
-0.803207531	,
-0.773010453	,
-0.740951125	,
-0.707106781	,
-0.671558954	,
-0.634393284	,
-0.595699304	,
-0.555570232	,
-0.514102744	,
-0.471396736	,
-0.427555093	,
-0.382683432	,
-0.336889853	,
-0.290284677	,
-0.242980179	,
-0.195090321	,
-0.146730474	,
-0.09801714	,
-0.049067674
};

float cosinus[128] = {
1	,		 		// cos (0 * 360 deg. / 128)
0.998795456	,		// cos (1 * 360 deg. / 128)
0.995184727	,		// cos (2 * 360 deg. / 128)
0.98917651	,		// ...
0.98078528	,
0.970031253	,
0.956940336	,
0.941544065	,
0.923879532	,
0.903989293	,
0.881921264	,
0.85772861	,
0.831469612	,
0.803207531	,
0.773010453	,
0.740951125	,
0.707106781	,
0.671558955	,
0.634393284	,
0.595699304	,
0.555570233	,
0.514102744	,
0.471396737	,
0.427555093	,
0.382683432	,
0.336889853	,
0.290284677	,
0.24298018	,
0.195090322	,
0.146730474	,
0.09801714	,
0.049067674	,
0	,
-0.049067675	,
-0.098017141	,
-0.146730475	,
-0.195090322	,
-0.24298018	,
-0.290284677	,
-0.336889854	,
-0.382683433	,
-0.427555094	,
-0.471396737	,
-0.514102744	,
-0.555570233	,
-0.595699305	,
-0.634393284	,
-0.671558955	,
-0.707106781	,
-0.740951126	,
-0.773010454	,
-0.803207532	,
-0.831469612	,
-0.85772861	,
-0.881921265	,
-0.903989293	,
-0.923879533	,
-0.941544065	,
-0.956940336	,
-0.970031253	,
-0.98078528	,
-0.98917651	,
-0.995184727	,
-0.998795456	,
-1	,
-0.998795456	,
-0.995184727	,
-0.98917651	,
-0.98078528	,
-0.970031253	,
-0.956940336	,
-0.941544065	,
-0.923879532	,
-0.903989293	,
-0.881921264	,
-0.85772861	,
-0.831469612	,
-0.803207531	,
-0.773010453	,
-0.740951125	,
-0.707106781	,
-0.671558954	,
-0.634393284	,
-0.595699304	,
-0.555570233	,
-0.514102744	,
-0.471396736	,
-0.427555093	,
-0.382683432	,
-0.336889853	,
-0.290284677	,
-0.242980179	,
-0.195090321	,
-0.146730474	,
-0.09801714	,
-0.049067674	,
0	,
0.049067675	,
0.098017141	,
0.146730475	,
0.195090323	,
0.242980181	,
0.290284678	,
0.336889854	,
0.382683433	,
0.427555094	,
0.471396737	,
0.514102745	,
0.555570234	,
0.595699305	,
0.634393285	,
0.671558955	,
0.707106782	,
0.740951126	,
0.773010454	,
0.803207532	,
0.831469613	,
0.85772861	,
0.881921265	,
0.903989293	,
0.923879533	,
0.941544065	,
0.956940336	,
0.970031253	,
0.980785281	,
0.98917651	,
0.995184727	,
0.998795456
};


// 2D rotation of (x, y) point with angle around (0, 0), result in
// resx and resy
void Rotate(float x, float y, signed char angle, float * resx, float * resy)
{
	if (angle >= -64 && angle <= 63)
	{
		*resx = x * cosinus[angle + 64] - y * sinus[angle + 64];
		*resy = x * sinus[angle + 64] + y * cosinus[angle + 64];
	}
	else
	{
		*resx = 0;
		*resy = 0;
	}
}

// Rotate 2-point vector around 3 axises
void RotateLine(line3D ToRotate, line3D * Rotated, unsigned char x_angle, unsigned char y_angle, unsigned char z_angle)
{
	Rotate(ToRotate.x0, ToRotate.y0, z_angle, &(*Rotated).x0, &(*Rotated).y0);
	Rotate(ToRotate.x1, ToRotate.y1, z_angle, &(*Rotated).x1, &(*Rotated).y1);

	Rotate(ToRotate.z0, (*Rotated).y0, x_angle, &(*Rotated).z0, &(*Rotated).y0);
	Rotate(ToRotate.z1, (*Rotated).y1, x_angle, &(*Rotated).z1, &(*Rotated).y1);

	Rotate((*Rotated).x0, (*Rotated).z0, y_angle, &(*Rotated).x0, &(*Rotated).z0);
	Rotate((*Rotated).x1, (*Rotated).z1, y_angle, &(*Rotated).x1, &(*Rotated).z1);
}

// Add perspective
void ComputePerspective(line3D * ToCompute)
{
	(*ToCompute).x0 = (*ToCompute).x0 * PERSPECTIVE_SURFACE_DICTANCE / (PERSPECTIVE_ORIGIN_DISTANCE - (*ToCompute).z0);
	(*ToCompute).y0 = (*ToCompute).y0 * PERSPECTIVE_SURFACE_DICTANCE / (PERSPECTIVE_ORIGIN_DISTANCE - (*ToCompute).z0);

	(*ToCompute).x1 = (*ToCompute).x1 * PERSPECTIVE_SURFACE_DICTANCE / (PERSPECTIVE_ORIGIN_DISTANCE - (*ToCompute).z1);
	(*ToCompute).y1 = (*ToCompute).y1 * PERSPECTIVE_SURFACE_DICTANCE / (PERSPECTIVE_ORIGIN_DISTANCE - (*ToCompute).z1);
}

// Draw line
void Line(int x0, int y0, int x1, int y1, unsigned int color)
{
	int dx = x1 - x0;
	int dy = y1 - y0;

	LCDSetPixel(x0, y0, color);

	if (abs(dx) > abs(dy))
	{
		float m = (float) dy / (float) dx;
		float b = y0 - m*x0;
		dx = (dx < 0) ? -1 : 1;
		while (x0 != x1)
		{
			x0 += dx;
			LCDSetPixel(x0, lround(m*x0 + b), color);
        }
	} else
	if (dy != 0)
	{
		float m = (float) dx / (float) dy;
		float b = x0 - m*y0;
		dy = (dy < 0) ? -1 : 1;
		while (y0 != y1)
		{
			y0 += dy;
			LCDSetPixel(lround(m*y0 + b), y0, color);
		}
	}
}


// Draw cube
void DrawCube(unsigned char x_angle, unsigned char y_angle, unsigned char z_angle, unsigned int color)
{
	char i;

	// Rotate cube
	for (i=0; i<12; i++)
		RotateLine(cube[i], &(rotatedCube[i]), x_angle, y_angle, z_angle);

	// Add perspective
	for (i=0; i<12; i++)
		ComputePerspective(&(rotatedCube[i]));

	pointCount = 0;
   	// Move cube to screen center and draw it
	for (i=0; i<12; i++)
		Line(rotatedCube[i].x0 + 66, rotatedCube[i].y0 + 66, rotatedCube[i].x1 + 66, rotatedCube[i].y1 + 66, color);

}
