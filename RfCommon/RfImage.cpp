#include "pch.h"
#include "RfImage.h"
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"
RfImage::RfImage()
{
}

RfImage::~RfImage()
{
    if (pixels)
    {
        stbi_image_free(pixels);
    }
}

void RfImage::Load(std::string path)
{
    if (pixels)
    {
        stbi_image_free(pixels);
    }
    //stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channel, 4);
    pixels = data;
}
void RfImage::Print(std::string msg)
{
    print(" {} w {} h {} channel {} pixels{} \n", msg,width, height, channel,(int)pixels);
}