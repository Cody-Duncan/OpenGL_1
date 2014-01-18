#include <string>       //string
#include <stdio.h>      //cout, endl
#include <windows.h>    //windows header
#include <fstream>      //file stream
#include <limits>       //numeric limits
#include <crtdbg.h>     //memory leak debugging

#include <gl/gl.h>

#include "WindowCreator.h"
#include "OpenGLInitialization.h"

int ScreenWidth = 800;
int ScreenHeight = 600;

int main()
{
    GenerateWindow(ScreenWidth, ScreenHeight);
    ActivateWindow();

    InitOpenGL(ghMainWnd);

    while(!QuitMsgRecieved)
    {
        CheckMessagePump();
            
        glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
        glClear( GL_COLOR_BUFFER_BIT );
            
        glPushMatrix();
        glRotatef( 0.2f, 0.0f, 0.0f, 1.0f );
        glBegin( GL_TRIANGLES );
        glColor3f( 1.0f, 0.0f, 0.0f ); glVertex2f( 0.0f, 1.0f );
        glColor3f( 0.0f, 1.0f, 0.0f ); glVertex2f( 0.87f, -0.5f );
        glColor3f( 0.0f, 0.0f, 1.0f ); glVertex2f( -0.87f, -0.5f );
        glEnd();
        glPopMatrix();
            
        OpenGL_SwapBuffers();
    }

    EndOpenGL();

    return 0;
}