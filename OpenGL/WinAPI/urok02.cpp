//����� ���������� 
// g++ -Wall -o "%e" "%f" -mwindows -lopengl32 -lglu32
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>

#define GLvoid void
//#define CDS_FULLSCREEN 4

HGLRC hRC = NULL; //���������� �������� ����������
HDC hDC = NULL; //��������� �������� ���������� GDi
HWND hWnd = NULL; //����� ����� �������� ���������� ����
HINSTANCE hInstance; //���������� ����������

bool keys[256]; //��� �������� � �����������
bool active = TRUE; //���� ���������� ����
bool fullscreen = TRUE; //���� �������������� ������

LRESULT CALLBACK WndProc(HWND, UINT,WPARAM, LPARAM);//�������� ������� WndProc
//��������� ������� � ������������� ���� GL
GLvoid resizeGLScene(GLsizei width, GLsizei height)
{
	if(height ==0) //�������������� ������� �� ����
	{
		height = 1;
	}
	/*����� ������� ������� ������*/
	glViewport(0,0,width,height);
	//����� ������� ��������
	glMatrixMode(GL_PROJECTION);
	//����� ������� ��������
	glLoadIdentity();
	//���������� ����������� �������������� �������� ��� ����
	gluPerspective(45.0f, (GLfloat)width/(GLfloat)height,0.1f, 100.0f);
	//����� ������� ���� ������
	glMatrixMode(GL_MODELVIEW);
	//����� ������� ���� ������
	glLoadIdentity();
}

//��� ��������� OpenGL ���������� �����
int InitGL(GLvoid) 
{
	//��������� �������� �����������
	glShadeModel(GL_SMOOTH);
	//������� � ������������� ���� RGB alpha(������������)
	glClearColor(0.0f,0.0f,0.0f,0.5f);
	
	//��������� ������ �������
	//��������� ������� ������ �������
	glClearDepth(1.0f);
	//��������� ���� �������
	glEnable(GL_DEPTH_TEST);
	//��� ����� �������
	glDepthFunc(GL_LEQUAL); 
	//��������� � ���������� �����������
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	return TRUE; //������������� ������ �������
}
//������� ���������
int DrawGLScene(GLvoid)
{
	//�������� ����� � ����� �������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	//�������� ������� �������
	glLoadIdentity(); //�������� ������� �������
	
	//�������� ����� �� 1,5 ������
	glTranslatef(-1.5f,0.0f,-6.0f);
	//������ 
	//GL_TRIGLE
	//GL_QUADS
	//GL_POLYGONS
	
	glBegin(GL_TRIANGLES);                      // Drawing Using Triangles
    glVertex3f( 0.0f, 1.0f, 0.0f);              // Top
    glVertex3f(-1.0f,-1.0f, 0.0f);              // Bottom Left
    glVertex3f( 1.0f,-1.0f, 0.0f);              // Bottom Right
	glEnd();                            // Finished Drawing The Triangle
	
	glTranslatef(3.0f,0.0f,0.0f);
	glBegin(GL_QUADS);                      // Draw A Quad
        glVertex3f(-1.0f, 1.0f, 0.0f);              // Top Left
        glVertex3f( 1.0f, 1.0f, 0.0f);              // Top Right
        glVertex3f( 1.0f,-1.0f, 0.0f);              // Bottom Right
        glVertex3f(-1.0f,-1.0f, 0.0f);              // Bottom Left
    glEnd();                            // Done Drawing The Quad
    return TRUE;        
	
	
}
//���������� ���������� ����
GLvoid KillGLWindow(GLvoid)
{
	if(fullscreen)
	{
		//������� ���� � ��������� �����
		ChangeDisplaySettings(NULL,0);
		//�������� ������ ����
		ShowCursor(TRUE); //�������� ������ ����
	}
	//���������� �� �������� ����������
	if(hRC)
	{
		//����� �� ��������� RC DC
		if(!wglMakeCurrent(NULL,NULL))
		{
			MessageBox(NULL,"������ ������������ DC � RC","������", MB_OK|MB_ICONINFORMATION);
		}
		//����� �� ���������� �������� ����������
		if( !wglDeleteContext( hRC ) )
		{
			MessageBox(NULL,"������ ������������ ��������� ����������","������", MB_OK|MB_ICONINFORMATION);		
		}
		hRC = NULL; 
	}
	//�������� �� ���������� DC
	if(hDC && !ReleaseDC(hWnd, hDC))
	{
		MessageBox(NULL,"������ ������������ ��������� ����������","������", MB_OK|MB_ICONINFORMATION);
		hDC = NULL;
	}
	//�������� �� ���������� ����
	if(hWnd && !DestroyWindow(hWnd))
	{
		MessageBox(NULL,"�� ����������� hWnd","������", MB_OK|MB_ICONINFORMATION);
		hWnd = NULL;
	}
	//�������� �� ����������������� �����
	if(!UnregisterClass("OpenGL",hInstance))
	{
		MessageBox(NULL,"������ ����������������� �����","������", MB_OK|MB_ICONINFORMATION);
		hInstance = NULL;
	}
}

//������� ����
bool CreateGLWindow(/*LPCWSTR*/const char *title, int width, int height, int bits, bool fullscreenflag)
{
	//������ �������� ����� ������
	GLuint PixelFormat; 
	//��������� ������ ����
	WNDCLASS wc;
	DWORD dwExStyle; //������������ ����� ����
	DWORD dwStyle; //������� ����� ����
	// ������� ��� ��������� �������� � ������ �����
	RECT WindowRect; 
	WindowRect.left = (long)0; //���������� ����� ������������ � 0
	WindowRect.right = (long)width; //���������� ������ �������������
	WindowRect.top = (long)0; //���������� ������� ������������
	WindowRect.bottom = (long)height; //���������� ������ ������������
	//������������� �������� ���������� ���������� fullscreen
	fullscreen = fullscreenflag;
	
	//������������� �������� ����
	// ������� ���������� ������ ����������
	hInstance = GetModuleHandle(NULL);        
	// ���������� ��� ����������� � ������ ������� DC
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; 
	// ��������� ��������� ���������
	wc.lpfnWndProc = (WNDPROC) WndProc;          
	// ��� �������������� ���������� ��� ����
	wc.cbClsExtra = 0;              
	// ��� �������������� ���������� ��� ����
	wc.cbWndExtra = 0;              
	// ������������� ����������
	wc.hInstance = hInstance;            
	// ��������� ������ �� ���������
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);        
	// ��������� ��������� �����
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);        
	// ��� �� ��������� ��� GL
	wc.hbrBackground = NULL;              
	// ���� � ���� �� �����
	wc.lpszMenuName = NULL;              
	// ������������� ��� ������
	wc.lpszClassName = "OpenGL";            

	//������������ ����� ����
	if(!RegisterClass(&wc))
	{
		MessageBox(NULL, "������ ����������� ����� ����","������",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}
	
	//�������� �������������� ������
	if(fullscreen)
	{
		//����� ����������
		DEVMODE dmScreenSettings;
		//������� ��� �������� ���������
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));
		//������ ��������� Devmode
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);
		//������ ������
		dmScreenSettings.dmPelsWidth = width;
		//������ ������ 
		dmScreenSettings.dmPelsHeight = height; 
		//������� �����
		dmScreenSettings.dmBitsPerPel = bits;
		//����� �������
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		//�������� ���������� ��������� ����� � �������� ���������.
		if(ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			//���� ������������ � ������������� ����� ����������
			//����� ���������� ������� ����� ��� �����
			if(MessageBox(NULL,"������� � ������������� ����� ����������\n ������������ ������� �����","��������� ���������",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				//��������� �������� ������
				fullscreen=FALSE;
			}
			else
			{
				//����� ��������� � ��������� ���� 
				MessageBox(NULL,"��������� ����� �������", "������", MB_OK|MB_ICONSTOP);
				return FALSE;
			}
		}
	}
	//�� � ������������� ������
	if(fullscreen)
	{
		//������ ������� ����� ���� ������ � ����������
		dwExStyle = WS_EX_APPWINDOW;
		//������� ����� ����
		dwStyle = WS_POPUP;
		//������ ��������� ����
		ShowCursor(FALSE);
	}
	else
	{
		//������� ���� ����� �������� ���
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		//������� � ������ ��������� �������
		dwStyle = WS_OVERLAPPEDWINDOW;
	}
	// ��������� ���� ���������� �������
	AdjustWindowRectEx( &WindowRect, dwStyle, FALSE, dwExStyle );  
	
	/*
	       ����������� ����� ����������� �����; 
	       ��� ������ (������� ������ ���� ��� �����, ��� �� ������������, ����� �������������� ����� ����); 
	       ��������� ����; 
	       ������� ����� ����; 
	       X ������ ���� ����; 
	       Y ������ ���� ����; 
	       ������ ����; 
	       ������ ����; 
	       ������������ ���� (� ��� ��� ���); 
	       ���������� ���� (� ���� � ��� ���� ���); 
	       ���������� ����������; 
	       �������������� ������. 
	  */
	
	if( !( hWnd = CreateWindowEx(
								dwExStyle,// ����������� ����� ��� ����
								"OpenGL", // ��� ������
								title,    // ��������� ����
								dwStyle |
								WS_CLIPSIBLINGS |	 // ���������� ����� ��� ����
								WS_CLIPCHILDREN ,       // ��������� ������ ����� �������� ������ ������ ����
								0, 0,     // ������� ����
								WindowRect.right-WindowRect.left,    // ���������� ���������� ������
								WindowRect.bottom-WindowRect.top,    // ���������� ���������� ������
								NULL,     // ��� �������������
								NULL,     // ��� ����
								hInstance, // ���������� ����������
								NULL ) ) ) // �� ������� ������ �� WM_CREATE


			{//� ������ ������
		     KillGLWindow(); // ������������ �����
		     MessageBox( NULL, "������ �������� ����", "������", MB_OK | MB_ICONEXCLAMATION );
			 return FALSE;                // ������� FALSE
			}
			
			//������������� ������ ����������� ��������
			static PIXELFORMATDESCRIPTOR pfd =
			{
				sizeof(PIXELFORMATDESCRIPTOR), //������ ����������� ������� ������� ��������
				1, 				//����� ������
				PFD_DRAW_TO_WINDOW | //������ ��� ����
				PFD_SUPPORT_OPENGL | //������ ��� OpenGL
				PFD_DOUBLEBUFFER, //������ ��� �������� ������
				PFD_TYPE_RGBA, //��������� rgba ������
				bits, //���������� ��� ������� �����
				0, 0, 0, 0, 0, 0, //������������� �������� �����
				0, //��� ������ ������������
				0, //��������� ���
				0, //��� ������ ����������
				0, 0, 0, 0, //����  ��������� ������������
				32, //32 ������ z-����� �������
				0, //��� ������ ���������
				0, //��� ��������������� �������
				PFD_MAIN_PLANE, //������� ���� ���������
				0, //���������������
				0,0,0 //����� ���� ������������
			};
			
			//����� �� �� �������� �������� ����������
			if(!(hDC = GetDC(hWnd))) 	
			{
				KillGLWindow(); //����������� �����
				MessageBox(NULL, "�� ������� �������� ����������","������",MB_OK|MB_ICONINFORMATION);
				return FALSE;
			}
				
			//������ �� ����������� ������ �������
			if(!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))
			{
				KillGLWindow(); //����������� �����
				MessageBox(NULL, "�� ������ ������ �������", "������", MB_OK|MB_ICONEXCLAMATION);
				return FALSE;
			}
			
			//�������� �� ���������� ������ �������
			if(!SetPixelFormat(hDC, PixelFormat, &pfd))
			{
				KillGLWindow();
				MessageBox(NULL,"�� ���������� ������ �������","������",MB_OK|MB_ICONEXCLAMATION);
				return FALSE;
			}
				//�������� �� ���������� �������� ����������
			if(!(hRC = wglCreateContext(hDC)))
			{
				KillGLWindow();
				MessageBox(NULL, "�� ���������� �������� ����������","������", MB_OK|MB_ICONEXCLAMATION);
				return FALSE;
			}
				
			//����������� ������������ ������� ���������� 
			if(!wglMakeCurrent(hDC, hRC))
			{
				KillGLWindow();
				MessageBox(NULL, "�� ����������� �������� ����������","������", MB_OK|MB_ICONEXCLAMATION);
				return FALSE;
			}
			
			ShowWindow(hWnd, SW_SHOW); //�������� ����
			SetForegroundWindow(hWnd); //������ ������� ���������
			SetFocus(hWnd); //���������� ������ ���������� �� ���� ����
			resizeGLScene(width, height); //�������� ���������� ��� ������ ����
			
			//������������� ���������� ����
			if(!InitGL())
			{
				KillGLWindow();
				MessageBox(NULL, "������ �������������","������", MB_OK|MB_ICONEXCLAMATION);
				return FALSE;
			}
			
			return TRUE;	
			}

	//������������ ����� ���� � ��������� ��������� ���������
	LRESULT CALLBACK WndProc(HWND hWnd, //���������� ������� ����
							UINT uMsg, //��������� ��� ����� ����
							WPARAM wParam, //�������������� ����������
							LPARAM lParam) //�������������� ����������
	{
		switch(uMsg) //�������� ��������� ��� ����
		{
			case WM_ACTIVATE: //�������� ��������� ���������� ����
			{
				if(!HIWORD(wParam)) //��������� ��������� �����������
				{
					active = TRUE; //��������� ��������
				}
				else
				{
					active = FALSE; //��������� �� �������
				}
				return 0; //�������� � ���� ��������� ���������
			}
			//������������� ��������� �������
			case WM_SYSCOMMAND:
			{
				switch(wParam) //������������� ��������� �����
				{
					case SC_SCREENSAVE: // �������� �� ���������� �����������
					case SC_MONITORPOWER:  //�������� ������� ������� � ������ ����� 
					return 0; //������������
				}
				break;
			}
			
			case WM_CLOSE: //�������� ��������� �� �������� 
			{
				PostQuitMessage(0); //��������� ��������� � ������
				return 0;
			}
			//���� ������ ������
			case WM_KEYDOWN: 
			{
				keys[wParam]=TRUE; //���� ��� ����������� ��������������� ������ TRUE
				return 0;
			}
			case WM_KEYUP: // ���� �� �������� �������?
			{
				keys[wParam] = FALSE;          //  ���� ���, �� ����������� ���� ������ FALSE
				return 0;            // ������������
			}
			//��������� �������� OpenGL ����
			case WM_SIZE:
			{
				//������� ����� ������ / ������� ����� ������
				resizeGLScene(LOWORD(lParam),HIWORD(lParam));
				return 0;
			}
		}
			// ���������� ��� �������������� ��������� DefWindowProc
			return DefWindowProc( hWnd, uMsg, wParam, lParam );
		}
		//����� ����� � ���������
	int WINAPI WinMain( HINSTANCE hInstance,        // ���������� ����������
						HINSTANCE hPrevInstance,        // ���������� ������������� ����������
						LPSTR lpCmdLine,        // ��������� ��������� ������
						int nCmdShow )        // ��������� ����������� ����
		{
			MSG msg;  // ��������� ��� �������� ��������� Windows
		    bool done = FALSE;            // ���������� ���������� ��� ������ �� �����

			// ���������� ������������, ����� ����� ������ �� ������������
			if( MessageBox( NULL, "������ �� �� ��������� ���������� � ������������� ������?",  "��������� � ������������� ������?", MB_YESNO | MB_ICONQUESTION) == IDNO )
			{
				fullscreen = FALSE;          // ������� �����
			}
			
			// ������� ���� OpenGL ����
			if( !CreateGLWindow( "GL programm", 1024, 768, 32, fullscreen ) )
			{
				return 0; // �����, ���� ���� �� ����� ���� �������
			}

			while(!done)
			{
				if(PeekMessage(&msg,NULL,0,0, PM_REMOVE)) //���� �� � ������� ���������
				{
					if( msg.message == WM_QUIT )        // �� ������� ��������� � ������?
					{
						done = TRUE;          // ���� ���, done=TRUE
					}
					else              // ���� ���, ������������ ���������
					{
						TranslateMessage( &msg );        // ��������� ���������
						DispatchMessage( &msg );        // �������� ���������
					}
				}
				else
				{
					// ������������� �����.
					if( active )          // ������� �� ���������?
					{
						if(keys[VK_ESCAPE])        // ���� �� ������ ������� ESC?
						{
							done = TRUE;      // ESC ������� �� �������� ���������� ���������
						}
						else            // �� ����� ��� ������, ������� �����.
						{
							DrawGLScene();        // ������ �����
							SwapBuffers( hDC );    // ������ ����� (������� �����������)
						}
					}
					
					if( keys[VK_F1] )          // ���� �� ������ F1?
					{
						keys[VK_F1] = FALSE;        // ���� ���, ������ �������� ������ ������� �� FALSE
						KillGLWindow();          // ��������� ������� ����
						fullscreen = !fullscreen;      // ����������� �����
						// ���������� ���� OpenGL ����
						if( !CreateGLWindow("���� ����", 1024, 768, 32, fullscreen ))
						{
							return 0;        // �������, ���� ��� ����������
						}
					}
				}
			}
		
		// Shutdown
		KillGLWindow();                // ��������� ����
		return ( msg.wParam );              // ������� �� ���������
}






	
	















