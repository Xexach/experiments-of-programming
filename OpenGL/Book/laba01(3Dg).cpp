/*
 * laba01(3Dg).cpp
 *
 *  Created on: 14.02.2013
 *      Author: Igor
 */
#define GL_PI 3.1415f

#include <GL\gl.h>
#include <GL\glu.h>
#include <GL\glut.h>
#include <math.h>
#include <stdio.h>

//�������� ��������� � ������ ��������������
GLfloat x1 = 0.0f;
GLfloat y11 = 0.0f;
GLfloat rsize = 25;
//�������� ���� � ������������ x � y
//����� �������� �� ������� �� ������ ���� ������������ �������������
GLfloat xstep = 3.0f;
GLfloat ystep = 3.0f;
//������������ ��������� ������ � ������ ����
GLfloat windowWidth;
GLfloat windowHeight;


GLfloat xRot;
GLfloat yRot;

void RenderScene(void)
{
	GLfloat x,y,z, angle;
	//�������� �������� �������� �������������� �����
	GLfloat sizes[2];
	//���������� �������������� �������� �������� �����
	GLfloat step;
	//���������� ������ ������� �����
	GLfloat curSize;

	glClear(GL_COLOR_BUFFER_BIT);
	//���������� ��������� ������� � ��������� �������
	glPushMatrix();
	glRotatef(xRot,1.0f,0.0f,0.0f);
	glRotatef(yRot, 0.0f,1.0f,0.0f);

	//�������� �������� �������� �������������� ����� � ������ ����
	glGetFloatv(GL_POINT_SIZE_RANGE,sizes);
	glGetFloatv(GL_POINT_SIZE_GRANULARITY,&step);
	//������ �������� ������ �����
	curSize = sizes[0];
	z = -50.0f;

	glBegin(GL_LINE_LOOP);
		for (angle = 0.0f; angle <= (2.0f * GL_PI)*3.0f ; angle +=0.1f) {
			x = 50.0f*sin(angle);
			y = 50.0f*cos(angle);
			//������ ������ ����� ����� ��������� ���������
			glPointSize(curSize);
			//������ �����
			//glBegin(GL_POINTS);
			   glVertex3f(x,y,z);
			//glEnd();
			z +=0.5f;
			//curSize +=step;
		}

    glEnd();
	//�������������� ��������������
    glPopMatrix();

	//xRot +=0.2f;
	//yRot +=0.2f;
	glutSwapBuffers();
	//glFlush();

}

void TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}
//��������� GLUT ��� ��������� �������� ����
void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat nRange = 100.0f;
	//������������� ������� �� ����
	if(h == 0)
		h=1;

	//������������� ���� ��������� � ��������� ����
	glViewport(0,0,w,h);
	//��������� ������� ���������
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//� ������ ���������� ��������� (�����, ������, ������, �������, �������, ��������)
	//������������� ����� �������

	if(w<=h)
	{
		glOrtho(-nRange, nRange,
				-nRange*h/w,nRange*h/w,
				-nRange, nRange);
	}
	else
	{
		glOrtho(-nRange*w/h, nRange*w/h,
				-nRange,nRange,
				-nRange,nRange);
	}
    //����������� ���� ������ �������� ������
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void SetupRC(void)
{
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glColor3f(0.0f,1.0f,0.0f);
}

void SpecialKeys(int key, int x, int y)
    {
	GLfloat stepSize = 0.5f;



	if(key == GLUT_KEY_UP)
		yRot += stepSize;

	if(key == GLUT_KEY_DOWN)
		yRot -= stepSize;

	if(key == GLUT_KEY_LEFT)
		xRot -= stepSize;

	if(key == GLUT_KEY_RIGHT)
		xRot += stepSize;


	glutPostRedisplay();
	}

int main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutCreateWindow("GL 3.1");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	SetupRC();
	//glutTimerFunc(33,TimerFunction,1);
	glutSpecialFunc(SpecialKeys);
	glutMainLoop();

	return 0;
}
