#include <string>       //string
#include <stdio.h>      //cout, endl
#include <windows.h>    //windows header
#include <fstream>      //file stream
#include <limits>       //numeric limits
#include <crtdbg.h>     //memory leak debugging

#include "WindowCreator.h"
#include "OpenGLInitialization.h"
#include "Shaders.h"

//use glload to bind the openGL functions to thier C interface.
//the C++ interface doesn't use the same functions/enums as standard openGL
#include <glload/gl_all.h>
#include <glload/gl_load.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>

#include <vector>


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

        //set clear color and enable features
        glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);


        //Create Shader
        GLuint vertexShader = CreateShader("vert.hlsl", GL_VERTEX_SHADER);
        GLuint pixelShader = CreateShader("pixe.hlsl", GL_FRAGMENT_SHADER);
        
        GLuint baseShader = glCreateProgram();
        glBindAttribLocation(baseShader, 0, "position");
        glBindAttribLocation(baseShader, 1, "color");
        LinkProgram(baseShader, vertexShader, pixelShader);
        glUseProgram(baseShader);

        //checking for correct indexing
        //GLint index = glGetAttribLocation(baseShader, "position");
        //GLint index2 = glGetAttribLocation(baseShader, "outColor");
        GLint MatrixID = glGetUniformLocation(baseShader, "MVP");


        //create cube vertices
        static const GLfloat g_vertex_buffer_data[] = {
            -1.0f,-1.0f,-1.0f, // triangle 1 : begin
            -1.0f,-1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, // triangle 1 : end
            1.0f, 1.0f,-1.0f, // triangle 2 : begin
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f, // triangle 2 : end
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f
        };

        GLuint vertexBuffer;
        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

        // 2nd attribute buffer : colors
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(
            0,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );

        //cube colors per vertex
        static const GLfloat g_color_buffer_data[] = {
            1.0f,  0,  0,
            0,  1.0f,  0,
            0,  0,  1.0f,
            1.0f,  1.0f,  0,
            0,  1.0f,  1.0f,
            1.0f,  0,  1.0f,
            0.597f,  0.770f,  0.761f,
            0.559f,  0.436f,  0.730f,
            0.359f,  0.583f,  0.152f,
            1.0f,  1.0f,  0,
            1.0f,  1.0f,  1.0f,
            0,  1.0f,  1.0f,
            1.0f,  0,  0,
            0,  0,  1.0f,
            0,  1.0f,  0,
            0.676f,  0.977f,  0.133f,
            0.971f,  0.572f,  0.833f,
            0.140f,  0.616f,  0.489f,
            0.997f,  0.513f,  0.064f,
            0.945f,  0.719f,  0.592f,
            0.543f,  0.021f,  0.978f,
            0.279f,  0.317f,  0.505f,
            0.167f,  0.620f,  0.077f,
            0.347f,  0.857f,  0.137f,
            0.055f,  0.953f,  0.042f,
            0.714f,  0.505f,  0.345f,
            0.783f,  0.290f,  0.734f,
            0.722f,  0.645f,  0.174f,
            0.302f,  0.455f,  0.848f,
            0.225f,  0.587f,  0.040f,
            0.517f,  0.713f,  0.338f,
            0.053f,  0.959f,  0.120f,
            0.393f,  0.621f,  0.362f,
            0.673f,  0.211f,  0.457f,
            0.820f,  0.883f,  0.371f,
            0.982f,  0.099f,  0.879f
        };

        GLuint colorbuffer;
        glGenBuffers(1, &colorbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );

        //World, View, Projection matrices
        glm::mat4 view = glm::lookAt(
            glm::vec3(0, 2, -3),
            glm::vec3(0,0,0),
            glm::vec3(0,1,0)
        );
        glm::mat4 projection = glm::perspective(
            75.0f,        //FOV
            4.0f / 3.0f,  //aspect ratio
            0.1f,         //near plane
            100.0f        //far plane
        );
        glm::mat4 viewProj =  projection * view;

        glm::mat4 world;

        float angle = 0.0f;

        while(!QuitMsgRecieved)
        {
            CheckMessagePump();

            angle += 0.5f; //increase angle to make rotation
            world = glm::mat4(); //reset matrix
            world = glm::rotate(world, angle, glm::vec3(0,1,0));
            
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glPushMatrix();
                
                //update matrix in shader
                glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(viewProj * world)[0][0]);

                //draw cube
                glDrawArrays(GL_TRIANGLES, 0, 12*3);

            glPopMatrix();
            
            glFlush();
            OpenGL_SwapBuffers();
        }
    }

    EndOpenGL();

    return 0;
}