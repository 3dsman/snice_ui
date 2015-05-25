// r,g,b values are from 0 to 1
// h = [0,360], s = [0,1], v = [0,1]
//		if s == 0, then h = -1 (undefined)
//#include <algorithm>

#ifndef _SNICE_COLORCONVERSION_H_
#define _SNICE_COLORCONVERSION_H_

//using namespace std;
enum colorSelector {H, S, V, R, G, B};

void RGBtoHSV( float r, float g, float b, float *h, float *s, float *v );

void HSVtoRGB( float h, float s, float v, float *r, float *g, float *b );

#endif //_SNICE_COLORCONVERSION_H_
