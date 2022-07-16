#include"pch.h"
#include"RfOpenGL.h"
#include "RfGLTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
GLTexture::GLTexture()
    : width(0), height(0), format(GL_RGBA), wrap_S(GL_REPEAT), wrap_T(GL_REPEAT), filter_Min(GL_LINEAR),
    filter_Max(GL_LINEAR),ID(0)
{
    
}
GLTexture::~GLTexture()
{
    glDeleteTextures(1, &this->ID);
}
void GLTexture::GenerateFromFile(const char* name)
{
    glGenTextures(1, &this->ID);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(name, &width, &height, &nrChannels, 4);
    this->width = width;
    this->height = height;
    // create Texture
    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->format, width, height, 0, this->format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    // set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filter_Max);
    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);
}

void GLTexture::Bind(unsigned int index) const
{
    glActiveTexture(GL_TEXTURE0+index); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, this->ID);
}
