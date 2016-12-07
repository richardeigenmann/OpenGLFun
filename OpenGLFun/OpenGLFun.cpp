// OpenGLFun.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <GL/glut.h>
#include <iostream>

using std::cout;

auto initGl() -> void {
	cout << "initGl\n";
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}


GLuint texture;
#pragma warning(disable: 4996)
bool loadTexture(const char* filename) {
	unsigned char header[54];
	unsigned char* data;
	int dataPos;
	int width;
	int height;
	int imageSize;

	FILE * file = fopen(filename, "rb");
	if (!file) return false;
	if (fread(header, 1, 54, file) != 54) return false;
	if (header[0] != 'B' || header[1] != 'M') return false;
	dataPos = *(int*) & (header[0x0A]);
	imageSize = *(int*) & (header[0x22]);
	width = *(int*) & (header[0x12]);
	height = *(int*) & (header[0x16]);
	if (imageSize == 0) imageSize = width * height * 3;
	if (dataPos == 0) dataPos = 54;
	data = new unsigned char[imageSize];
	fread(data, 1, imageSize, file);
	fclose(file);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
	GLenum err = glGetError();
	if (err)
		cout << "glTexImage2D err: " << err << "\n";
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	return true;
}



auto drawPoints() -> void {
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 0.1f);
	glVertex2f(0.1f, -0.6f);
	glVertex2f(0.7f, -0.6f);
	glVertex2f(0.4f, -0.1f);
	glEnd();
}

auto drawLines() -> void {
	glBegin(GL_LINES);
	glColor3f(0.5f, 0.8f, 0.3f);
	glVertex2f(0.1f, -0.6f);
	glVertex2f(0.7f, -0.3f);

	glVertex2f(0.7f, -0.6f);
	glVertex2f(0.4f, -0.1f);
	glEnd();
}

auto drawSolidTriangle() -> void {
	glBegin(GL_TRIANGLES);
	glColor3f(0.5f, 0.8f, 0.3f);
	glVertex2f(0.1f, -0.6f);
	glVertex2f(0.7f, -0.6f);
	glVertex2f(0.4f, -0.1f);
	glEnd();
}

auto drawGradientTriangle() -> void {
	glBegin(GL_TRIANGLES);
	glColor3f(0.5, 0.0f, 0.0f);
	glVertex2f(0.3f, -0.4f);
	glColor3f(0.2f, 0.87f, 0.1f);
	glVertex2f(0.9f, -0.4f);
	glColor3f(0.4f, 0.95f, 0.3f);
	glVertex2f(0.6f, -0.9f);
	glEnd();
}

auto drawQuad() -> void {
	glBegin(GL_QUADS);
	glColor3f(0.1f, 1.0f, 0.1f);
	glVertex2f(0.1f, -0.1f);
	glVertex2f(0.1f, -0.6f);
	glVertex2f(0.6f, -0.6f);
	glVertex2f(0.6f, -0.1f);
	glEnd();
}

auto drawTexture() -> void {
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(0.5f, 0.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(0.5f, 0.5f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(0.0f, 0.5f);
	glEnd();
}

auto update() -> void {
	//glClear(GL_COLOR_BUFFER_BIT);
	//drawPoints();
	//drawLines();
	//drawSolidTriangle();
	//drawGradientTriangle();
	//drawQuad();
	drawTexture();
	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);


	glutInitWindowSize(220, 320);
	glutInitWindowPosition(100, 20);
	glutCreateWindow("Richi GL Fun");

	glutDisplayFunc(update);
	initGl();

	if (loadTexture("flower.bmp"))
		cout << "Loading of texture returned true\n";
	else
		cout << "Loading of texture returned false\n";
	glutMainLoop();
    return 0;
}

