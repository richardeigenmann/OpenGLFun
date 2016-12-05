// OpenGLFun.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <GL/glut.h>
#include <iostream>

using std::cout;

auto initGl() -> void {
	cout << "initGl\n";
	glClearColor(0.3f, 1.0f, 0.0f, 1.0f);
}

auto drawPoints() -> void {
	glBegin(GL_POINTS);
	glColor3f(0.0f, 1.0f, 0.1f);
	glVertex2f(0.1f, -0.6f);
	glVertex2f(0.7f, -0.6f);
	glVertex2f(0.4f, -0.1f);
	glEnd();
}

auto drawLines() -> void {
	glBegin(GL_LINES);
	glColor3f(0.5, 0.8, 0.3);
	glVertex2f(0.1f, -0.6f);
	glVertex2f(0.7f, -0.6f);

	glVertex2f(0.7f, -0.6f);
	glVertex2f(0.4f, -0.1f);
	glEnd();
}

auto drawSolidTriangle() -> void {
	glBegin(GL_TRIANGLES);
	glColor3f(0.5, 0.8, 0.3);
	glVertex2f(0.1f, -0.6f);
	glVertex2f(0.7f, -0.6f);
	glVertex2f(0.4f, -0.1f);
	glEnd();
}


auto update() -> void {
	glClear(GL_COLOR_BUFFER_BIT);
	//drawPoints();
	//drawLines();
	drawSolidTriangle();
	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutCreateWindow("Richi GL Fun 2");
	glutInitWindowSize(220, 220);
	glutInitWindowPosition(20, 20);
	glutDisplayFunc(update);
	//initGl();
	glutMainLoop();
    return 0;
}

