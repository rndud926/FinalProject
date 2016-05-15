#include <GLES/gl.h>
#include <android/log.h>
#include "UHsurfaceview.h"

extern unsigned char outputRGB[WIDTH*HEIGHT*3];

GLfloat arrVertex[12];
GLfloat arrTexture[8];
GLshort arrIndex[4];
GLuint mTextureID;

int OnSurfaceCreated()
{
	__android_log_print(ANDROID_LOG_DEBUG, "OpenGL", "OnSurfaceCreated\n");

	//glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

	int i, j, fd;
	int textures[1] = {0};

	glDisable(GL_DITHER);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	glClearColor(0, 0, 0, 1);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, textures);
	mTextureID = textures[0];
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTHX, HEIGHTX, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	return 0;
}

int OnSurfaceChanged(int width, int height)
{
	__android_log_print(ANDROID_LOG_DEBUG, "OpenGL", "OnSurfaceChanged\n");

	float ratio = (float) width / height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustumf(-ratio, ratio, -1, 1, 1, 2);

	arrVertex[0] = -ratio;  arrVertex[1] =   1;  arrVertex[2]  = 0;
	arrVertex[3] =  ratio;  arrVertex[4] =   1;  arrVertex[5]  = 0;
	arrVertex[6] = -ratio;  arrVertex[7] =  -1;  arrVertex[8]  = 0;
	arrVertex[9] =  ratio;  arrVertex[10] = -1;  arrVertex[11] = 0;

	arrTexture[0] = (float)WIDTH/WIDTHX;  arrTexture[1] = (float)HEIGHT/HEIGHTX; arrTexture[2] = 0;  arrTexture[3] = (float)HEIGHT/HEIGHTX;
	arrTexture[4] = (float)WIDTH/WIDTHX;  arrTexture[5] = 0; arrTexture[6] = 0;  arrTexture[7] = 0;

	arrIndex[0] = 0;  arrIndex[1] = 1;  arrIndex[2] = 2;  arrIndex[3] = 3;

	return 0;
}

void DrawFrameRGB24()
{
	//__android_log_print(ANDROID_LOG_DEBUG, "OpenGL", "DrawFrameRGB\n");
	glDisable(GL_DITHER);
	glTexEnvx(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -1);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glActiveTexture(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glEnable(GL_TEXTURE_2D);
	glVertexPointer(3, GL_FLOAT, 0, arrVertex);
	glTexCoordPointer(2, GL_FLOAT, 0, arrTexture);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, arrIndex);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, outputRGB);


}
