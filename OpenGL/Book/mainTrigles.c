/*
 * mainTrigles.c
 *
 *  Created on: 02.01.2013
 *      Author: Igor
 */


//gcc -Wall -o "%e" "%f" -opengl32 -glut32 -glu32
#define GL_PI 3.1415f

#include <GL\gl.h>
#include <GL\glu.h>
#include <GL\glut.h>
#include <math.h>
#include <stdio.h>
#include <windows.h>

//�������� ���� � ������������ x � y
//����� �������� �� ������� �� ������ ���� ������������ �������������
GLfloat xstep = 3.0f;
GLfloat ystep = 3.0f;
//������������ ��������� ������ � ������ ����
GLfloat windowWidth;
GLfloat windowHeight;

GLfloat xRot;
GLfloat yRot;
BOOL bCull= FALSE;
BOOL bDepth = FALSE;
BOOL bOutLine = FALSE;

void RenderScene(void)
{
	GLfloat x, y , angle; //�������� ���������� � ����
	int iPivot = 1; 	  //������������, ����� ��������
						  //������������ �����
	//������� ���� � ����� �������
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// �������� �����, ���� ����������� �����
	if(bCull)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);

	//���� ����������� �����, ���������� �������� �������
	if(bDepth)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	//���� ����������� ����� ������ ������ �������
	//� ����� �������
	if(bOutLine)
		glPolygonMode(GL_BACK,GL_LINE);
	else
		glPolygonMode(GL_BACK,GL_FILL);

	//���������� ��������� ������� � ��������� �������
	glPushMatrix();
	glRotatef(xRot, 1.0, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	// �������� ���� �������������
	glBegin(GL_TRIANGLE_FAN);
	//������� ������ �������� ����� �������� �����. �����������
	// ����� �� ��� z, � ������ ���������� �������� �����
	glVertex3f(0.0f, 0.0f, 75.0f);
	//�� ����� �������� ���������� � ������ ������ ����� �����
	// ���������� �� ������� ����� �������������
	for(angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI/8.0f))
	{
		// ����������� ��������� x � y ��������� �������
		x = 50.0f * sin(angle);
		y = 50.0f * cos(angle);
		//�������� ������� � ������� ����
		if((iPivot%2)==0)
		{
			glColor3f(0.0f,1.0f,0.0f);
		}
		else
		{
			glColor3f(1.0f, 0.0f, 0.0f);
		}

		// ����������� pivot �� 1, ����� � ��������� ���
		// �������� ����
		iPivot++;
		// ������ ��������� ������� ����� �������������
		glVertex2f(x,y);
	}
	//������ ����, ����������� �����
	glEnd();

	//�������� ����� ���� �������������, ����������� ���������
	//������
	glBegin(GL_TRIANGLE_FAN);
	// ������� ����� �������� ������ ���������
	glVertex2f(0.0f, 0.0f);
	for(angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI/8.0f))
	{
		//������������ ���������� x � y ��������� �������
		x = 50.0f * sin(angle);
		y = 50.0f * cos(angle);
		//�������� ������� � ������� �����
		if((iPivot%2)==0)
			glColor3f(0.0f, 0.0f, 1.0f);
		else
			glColor3f(1.0f,1.0f,0.0f);

		//����������� pivot �� ������� ����� � ��������� ����
		// �������� �����
		iPivot++;
		// ������ ��������� ������� ����� �������������
		glVertex2f(x,y);
	}
	//������ ����, ����������� ��������� ������
	glEnd();
	// �������������� �������������
	glPopMatrix();
	//O������ ���� ������ ���������
	glFlush();

	glutSwapBuffers();
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
	//������������� ������ ���
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	//���� ���������
	glColor3f(0.0f,1.0f,0.0f);
	//���� ������ ��������� ���������� �������������������
	glShadeModel(GL_FLAT);
	//�������������� � ������� �� ������� ������� ���������
	//������������� ������; ��������� �������� �� ��������,
	//��������� �� ���������� ����� �������������
	glFrontFace(GL_CW);
}

void SpecialKeys(int key, int x, int y)
    {
	GLfloat stepSize = 0.9f;


	switch(key)
	{
		case GLUT_KEY_UP:
			yRot += stepSize;
			break;
		case GLUT_KEY_DOWN:
			yRot -= stepSize;
			break;
		case GLUT_KEY_LEFT:
			xRot -= stepSize;
			break;
		case  GLUT_KEY_RIGHT:
			xRot += stepSize;
			break;
		case GLUT_KEY_F1:
			bCull= !bCull;
			break;
		case GLUT_KEY_F2:
			bDepth=!bDepth;
			break;
		case GLUT_KEY_F3:
			bOutLine = !bOutLine;
			break;
	}

	glutPostRedisplay();
	}

int main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutCreateWindow("GL TRIGLES");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	SetupRC();
	//glutTimerFunc(33,TimerFunction,1);
	glutSpecialFunc(SpecialKeys);
	glutMainLoop();

	return 0;
}

