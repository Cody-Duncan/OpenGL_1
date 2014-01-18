#include <string>       //string
#include <stdio.h>      //cout, endl
#include <windows.h>    //windows header
#include <fstream>      //file stream
#include <limits>       //numeric limits
#include <crtdbg.h>     //memory leak debugging

#include "WindowCreator.h"
#include "OpenGLInitialization.h"

//use glload to bind the openGL functions to thier C interface.
//the C++ interface doesn't use the same functions/enums as standard openGL
#include <glload/gl_all.h>
#include <glload/gl_load.h>


int ScreenWidth = 800;
int ScreenHeight = 600;

int main()
{
    GenerateWindow(ScreenWidth, ScreenHeight);
    ActivateWindow();

    //initialize the context
    InitOpenGL(ghMainWnd);

    //load openGL functions
    int loadTest = ogl_LoadFunctions();

    if(loadTest != ogl_LOAD_FAILED)
    {

        printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
        printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
        printf("Rendered by: %s\n", glGetString(GL_RENDERER));
        fflush(stdout);

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
    }

    EndOpenGL();

    return 0;
}