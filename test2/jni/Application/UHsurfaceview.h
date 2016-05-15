/*
 * surfaceview.h
 *
 *  Created on: 2014. 6. 9.
 *      Author: Admin
 */

#include <GLES/gl.h>
#include <GLES/glext.h>

#ifndef SURFACEVIEW_H_
#define SURFACEVIEW_H_

#define WIDTH  960
#define HEIGHT 540
#define WIDTHX	1024
#define HEIGHTX	1024

void DrawFrameRGB24();
int OnSurfaceChanged(int width, int height);
int OnSurfaceCreated();

#endif /* SURFACEVIEW_H_ */
