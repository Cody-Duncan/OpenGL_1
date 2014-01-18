#include "OpenGLInitialization.h"

#include <Windows.h>

HGLRC hRC;
HDC hDC;
HWND windowHandle;

void InitOpenGL(HWND windowHandle)
{
    //get drawing context
    hDC = GetDC( windowHandle );

    PIXELFORMATDESCRIPTOR pfd;
    ZeroMemory( &pfd, sizeof( pfd ) );
    pfd.nSize = sizeof( pfd );
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    int iFormat = ChoosePixelFormat( hDC, &pfd );
    SetPixelFormat( hDC, iFormat, &pfd );

    hRC = wglCreateContext( hDC );
    wglMakeCurrent( hDC, hRC );
}

void OpenGL_SwapBuffers()
{
    SwapBuffers( hDC );
}

void EndOpenGL()
{
    if(hRC)
    {
        wglMakeCurrent( NULL, NULL );
        wglDeleteContext( hRC );
    }
    if ( windowHandle && hDC )
    {
        ReleaseDC( windowHandle, hDC );
    }
}