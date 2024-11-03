#include "xxOpenGL.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

#include "XXGL/xxGL.hpp"


int main (){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    int windowWidth = 1280;
    int windowHeight = 720;

    GLFWwindow* window = glfwCreateWindow(windowWidth,windowHeight,"xxOpenGL",NULL,NULL);

    // OpenGL 运行模式--单线程
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);


    char * vertexShader = (char *)R"(
        #version 330
        uniform float a;
        layout (location = 0) in vec3 pos;
        layout (location = 1) in vec3 uvPos;
        out vec3 outPos;
        out vec3 outUVPos;
        void main()
        {
            outPos = pos;
            outUVPos = uvPos;
            float _a = sin(a);
            _a = 1;
            gl_Position = vec4(pos.x * _a,pos.y * _a,pos.z * _a,1.0);
        }   
    
    )";
    

    char * fragmentShader = (char *)R"(
            #version 330

            out vec4 rgbaColor;
            in vec3 outPos;
            in vec3 outUVPos;
            uniform sampler2D t;
            void main()
            {   
                //纹理坐标
                vec2 uv = vec2(outUVPos.x,outUVPos.y);
                vec4 color = texture(t,uv);
                rgbaColor = vec4(outPos,1.0);
                rgbaColor = color;
            }
        
    )";

    // float vertex[] = 
    // {
    //     0.0f, 1.0f, 0.0f,
    //     -1.0f, -1.0f, 0.0f,
    //     1.0f, -1.0f, 0.0f
    // };

    float vertex[] = 
    {
        /* A */ -1.0,1.0,0.0,
        /* B */ 1.0,1.0,0.0,
        /* C */ 1.0,-1.0,0.0,
        /* D */ -1.0,-1.0,0.0,
    };

    float vertexUV[] = 
    {
        /* A */ 0.0,1.0,0.0,
        /* B */ 1.0,1.0,0.0,
        /* C */ 1.0,0.0,0.0,
        /* D */ 0.0,0.0,0.0,
    };

    unsigned int index[] {
        /* A->D->B */ 0,3,1,
        /* B->D->C */ 1,3,2,
    };

    xxGLVAO* vao = new xxGLVAO();
    vao->addVertex3D(vertex,4,0);
    vao->addVertex3D(vertexUV,4,1);
    vao->setIndex(index,6);



    xxGLProgram* program = new xxGLProgram(vertexShader,fragmentShader);

    //RGB

    int imgWidth = 2;
    int imgHeight = 2;
    unsigned char imgData[] = {
        255,0,0,         0,255,0,
        0,0,255,         127,127,127
    };

    GLuint textureId = 0;
    glGenTextures(1,&textureId);

    glBindTexture(GL_TEXTURE_2D,textureId);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,imgWidth,imgHeight,0,GL_RGB,GL_UNSIGNED_BYTE,imgData);






    float aa = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        // TODO 绘制操作
        glClear(GL_COLOR_BUFFER_BIT);

        program->UseProgram();

        GLint loc = glGetUniformLocation(program->program,"a");
        glUniform1f(loc,aa);

        GLint textureLoc = glGetUniformLocation(program->program,"t");
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,textureId);
        glUniform1i(textureLoc,0);
        

        vao->draw();
        aa +=0.002;

        // TODO
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // delete shader;
    delete vao;
    delete program;

    glfwTerminate();

    return 0;
}

