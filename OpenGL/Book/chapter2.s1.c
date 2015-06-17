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

void RenderScene(void)
{
	//������� ����
	glClear(GL_COLOR_BUFFER_BIT);
	//����� �������� �����
	glColor3f(1.0f,0.0f,0.0f);
	//������ ������������� ����������� ������� ������
	glRectf(-25.0f,25.0f,25.0f,-25.0f);
	//������� ������� ������� �������
	glFlush();
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
		glOrtho(-100.0, 100.0,-100.0/aspectRatio,100.0/aspectRatio,
				1.0, -1.0);
	else
		glOrtho(-100.0 * aspectRatio, 100.0 * aspectRatio,
				-100.0,100.0,1.0,-1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void SetupRC(void)
{
	glClearColor(0.0f,0.0f,1.0f,1.0f);
}

int main(void)
{
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutCreateWindow("GLRect");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	SetupRC();
	glutMainLoop();



	return 0;
}

