#include"pch.h"
#include"RfOpenGL.h"
#include "RfGLShaderCompiler.h"

RfGLShaderCompiler::RfGLShaderCompiler()
{

}
RfGLShaderCompiler::~RfGLShaderCompiler()
{

}

void RfGLShaderCompiler::CreateFromFile(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ "<<e.what() << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // shader programID
    programID = glCreateProgram();
    glAttachShader(programID, vertex);
    glAttachShader(programID, fragment);
    glLinkProgram(programID);
    checkCompileErrors(programID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void RfGLShaderCompiler::CreateFromFile(const char* commonPath)
{
    std::string name = commonPath;
    CreateFromFile(std::string(name + ".vert").c_str(), std::string(name + ".frag").c_str());
}

void RfGLShaderCompiler::CreateFromString(const char* vertexString, const char* fragmentString, const char* geometryString)
{
    const char* vShaderCode = vertexString;
    const char* fShaderCode = fragmentString;
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // shader programID
    programID = glCreateProgram();
    glAttachShader(programID, vertex);
    glAttachShader(programID, fragment);
    glLinkProgram(programID);
    checkCompileErrors(programID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void RfGLShaderCompiler::use()
{
    glUseProgram(programID);
}

void RfGLShaderCompiler::setBool(const char* name, bool value) const
{
    glUniform1i(glGetUniformLocation(programID, name), (int)value);
}

void RfGLShaderCompiler::setInt(const char* name, int value) const
{
    glUniform1i(glGetUniformLocation(programID, name), value);
}

void RfGLShaderCompiler::setFloat(const char* name, float value) const
{
    glUniform1f(glGetUniformLocation(programID, name), value);
}

void RfGLShaderCompiler::setVec2(const char* name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(programID, name), x, y);
}

void RfGLShaderCompiler::setVec3(const char* name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(programID, name), x, y, z);
}

void RfGLShaderCompiler::setVec4(const char* name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(programID, name), x, y, z, w);
}

void RfGLShaderCompiler::setMat2(const char* name, const float* arr22) const
{
    glUniformMatrix2fv(glGetUniformLocation(programID, name), 1, GL_FALSE, arr22);
}

void RfGLShaderCompiler::setMat3(const char* name, const float* arr33) const
{
    glUniformMatrix3fv(glGetUniformLocation(programID, name), 1, GL_FALSE, arr33);
}

void RfGLShaderCompiler::setMat4(const char* name, const float* arr44) const
{
    glUniformMatrix4fv(glGetUniformLocation(programID, name), 1, GL_FALSE, arr44);
}

void RfGLShaderCompiler::SetIntArray(const char* name, int array[], int size) const
{
    glUniform1iv(glGetUniformLocation(programID, name), size, array);
}

void RfGLShaderCompiler::Begin()
{
    if (m_isBegin)
    {
        //error
        std::cout << "already Begin() must call End()\n";
    }
    else
    {
        m_isBegin = true;
        glUseProgram(programID);
    }
}

void RfGLShaderCompiler::End()
{
    if (m_isBegin)
    {
        
        m_isBegin = false;
    }
    else
    {
        //error
       
        std::cout << "already End() must call Begin()\n";
    }
}

void RfGLShaderCompiler::checkCompileErrors(unsigned int shader, const char* type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
