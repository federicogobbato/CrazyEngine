
#include "GLSLProgram.h"

#include <fstream>
#include <iostream>
#include <vector>

namespace Engine {

    bool shaderCompilationChecking(GLuint shader)
    {
        GLint isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

            // Provide the infolog in whatever manor you deem best.
            // Exit with failure.
            glDeleteShader(shader); // Don't leak the shaderID.

            std::cout << &(errorLog[0]) << std::endl;
            return false;
        }
        return true;
    }



    GLSLProgram::GLSLProgram() : m_NumAttribute(0), m_ProgramID(0), m_VertexShaderID(0), m_FragmentShaderID(0)
    {
    }


    GLSLProgram::~GLSLProgram()
    {
    }



    void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilepath)
    {
        m_ProgramID = glCreateProgram();
        if (m_ProgramID == 0) {
            std::cout << "Program shader failed to be created!" << std::endl;
        }

        m_VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        if (m_VertexShaderID == 0) {
            std::cout << "Vertex shader failed to be created!" << std::endl;
        }

        m_FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        if (m_FragmentShaderID == 0) {
            std::cout << "Fragment shader failed to be created!" << std::endl;
        }

        // VERTEX SHADER COMPILATION
        compileShader(vertexShaderFilePath, m_VertexShaderID);

        // FRAGMENT SHADER COMPILATION
        compileShader(fragmentShaderFilepath, m_FragmentShaderID);

    }


    void GLSLProgram::compileShader(const std::string& shaderFilePath, GLuint shaderID)
    {
        std::ifstream shaderFile(shaderFilePath);
        if (shaderFile.fail()) {
            std::cout << "Failed to open " + shaderFilePath << std::endl;
        }

        // We copy all the text in the shader file on a string
        std::string fileContents = "";
        std::string line;
        while (std::getline(shaderFile, line))
        {
            fileContents += line + "\n";
        }

        shaderFile.close();

        std::cout << fileContents << std::endl;

        const char* contentsPtr = fileContents.c_str();
        glShaderSource(shaderID, 1, &contentsPtr, nullptr);

        glCompileShader(shaderID);

        // Shader compilation error checking   
        if (!shaderCompilationChecking(shaderID)) {
            std::cout << "Shader " + shaderFilePath + " failed to compile" << std::endl;
        }

    }



    void GLSLProgram::linkShader() {
        // Vertex and fragment shaders are successfully compiled.
        // Now time to link them together into a program.

        // Attach our shaders to our program
        glAttachShader(m_ProgramID, m_VertexShaderID);
        glAttachShader(m_ProgramID, m_FragmentShaderID);

        // Link our program
        glLinkProgram(m_ProgramID);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(m_ProgramID, GL_LINK_STATUS, (int *)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength);
            glGetProgramInfoLog(m_ProgramID, maxLength, &maxLength, &errorLog[0]);

            // We don't need the program anymore.
            glDeleteProgram(m_ProgramID);
            // Don't leak shaders either.
            glDeleteShader(m_VertexShaderID);
            glDeleteShader(m_FragmentShaderID);

            std::cout << &(errorLog[0]) << std::endl;
            std::cout << "Linking is failed!" << std::endl;
        }

        // Always detach shaders after a successful link.
        glDetachShader(m_ProgramID, m_VertexShaderID);
        glDetachShader(m_ProgramID, m_FragmentShaderID);

        glDeleteShader(m_VertexShaderID);
        glDeleteShader(m_FragmentShaderID);
    }



    void GLSLProgram::addAttribute(const std::string& attributeName)
    {
        // Associates a generic vertex attribute index with a named attribute variable
        glBindAttribLocation(m_ProgramID, m_NumAttribute++, attributeName.c_str());
    }



    GLint GLSLProgram::getAttrLocation(const std::string &attrName) {
        GLint location = glGetAttribLocation(m_ProgramID, attrName.c_str());

        if (location == GL_INVALID_INDEX)
        {
            std::cout << "Attribute " + attrName + " not found in shader!" << std::endl;
        }
        return location;
    }

    GLint GLSLProgram::getUniformLocation(const std::string &uniformName) {
        GLint location = glGetUniformLocation(m_ProgramID, uniformName.c_str());

        if (location == GL_INVALID_INDEX)
        {
            std::cout << "Uniform " + uniformName + " not found in shader!" << std::endl;
        }
        return location;
    }


    // Enable the shader, and all its attributes
    void GLSLProgram::use() {
        glUseProgram(m_ProgramID);
        //for (int i = 0; i < m_NumAttribute; i++)
        //{
        //    // Enable the generic vertex attribute array specified by index
        //    glEnableVertexAttribArray(i);
        //}
    }

    // Disable the shader
    void GLSLProgram::unuse() {
        glUseProgram(0);
        //for (int i = 0; i < m_NumAttribute; i++)
        //{
        //    glDisableVertexAttribArray(i);
        //}
    }

}



