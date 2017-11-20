#pragma once

#include <string>
#include <glew.h>

namespace Engine {

    //Reference: http://www.opengl.org/wiki/Shader_Compilation

    class GLSLProgram
    {
    public:
        GLSLProgram();
        ~GLSLProgram();

        void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilepath);
        void linkShader();
        void addAttribute(const std::string& attributeName);
        void use();
        void unuse();

        GLint getAttrLocation(const std::string &uniformName);
        GLint getUniformLocation(const std::string &uniformName);

    private:

        void compileShader(const std::string& shaderFilePath, GLuint shaderID);

        int m_NumAttribute;
        GLuint m_ProgramID;
        GLuint m_VertexShaderID;
        GLuint m_FragmentShaderID;

    };

}