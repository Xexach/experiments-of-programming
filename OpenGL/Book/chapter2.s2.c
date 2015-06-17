/*
 * main.c
 *
 *  Created on: 01.01.2013
 *      Author: Igor
 */

/*
 * main.c
 *
 *  Created on: 31.12.2012
 *      Author: Igor
 */
//gcc -Wall -o "%e" "%f" -opengl32 -glut32 -glu32
#include <GL\gl.h>
#include <GL\glu.h>
#include <GL\glut.h>
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

void RenderScene(void)
{
	//������� ����
	glClear(GL_COLOR_BUFFER_BIT);
	//����� �������� �����
	glColor3f(1.0f,0.0f,0.0f);
	//������ ������������� ����������� ������� ������
	glRectf(x1,y11,x1 + rsize,y11 - rsize);
	//������� ������� ������� �������
	glutSwapBuffers();
	//glFlush();
}

void TimerFunction(int value)
{
	//������ ���������� �� ��������������� ��� ������� � ������ ��� ������� ����
	if(x1> windowWidth - rsize || x1< -windowWidth)
		xstep = -xstep;
	//������ ����������� �� ��������������� ��� ������� � ��������� ��� ������� ����
	if(y11>windowHeight||y11<-windowHeight + rsize)
		ystep = -ystep;
	//���������� �������
	x1+=xstep;
	y11+=ystep;
	//�������� ������. ���� ���� ������ ��������������
	//������� ������� ������ � ������������� ������������ ���� ��� ������ ������ ���������
	if(x1>(windowWidth - rsize + xstep))
		x1 = windowWidth-rsize - 1;
	else if(x1 < -(windowWidth + xstep))
		x1 = -windowWidth-1;

	if(y11 > (windowHeight + ystep))
		y11= windowHeight-1;
	else if(y11 < -(windowHeight - rsize + ystep))
		y11 = -windowHeight + rsize - 1;

	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}
//��������� GLUT ��� ��������� �������� ����
void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat aspectRatio;
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
	aspectRatio = (GLfloat)w/(GLfloat)h;
	if(w<=h)
	{
		windowWidth = 100;
		windowHeight = 100/aspectRatio;
		glOrtho(-windowWidth, windowWidth,
				-windowHeight,windowHeight,
				1.0, -1.0);
	}
	else
	{
		windowWidth = 100*aspectRatio;
		windowHeight = 100;
		glOrtho(-windowWidth, windowWidth,
				-windowHeight,windowHeight,
				1.0,-1.0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void SetupRC(void)
{
	glClearColor(0.0f,0.0f,1.0f,1.0f);
}

int main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutCreateWindow("GLRect 2");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	SetupRC();
	glutTimerFunc(33,TimerFunction,1);

	glutMainLoop();

   /* const GLubyte *vendor = glGetString(GL_VENDOR);
    const GLubyte *render = glGetString(GL_RENDERER);
    const GLubyte *version = glGetString(GL_VERSION);
    const GLubyte *extens = glGetString(GL_EXTENSIONS);

    printf("VENDOR:%s;EOF\nRENDERER:%sEOF;\nVERSION:%s;EOF\nEXTENSIONS:%s;EOF", vendor, render, version, extens);
*/
    getchar();
	return 0;
}


