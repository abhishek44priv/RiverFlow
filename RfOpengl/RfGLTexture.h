#pragma once
class GLTexture
{
    // holds the ID of the texture object, used for all texture operations to reference to this particlar texture
    unsigned int ID;
    // texture image dimensions
    unsigned int width, height; // width and height of loaded image in pixels
    // texture Format
    unsigned int format; // format of loaded image
    // texture configuration
    unsigned int wrap_S; // wrapping mode on S axis
    unsigned int wrap_T; // wrapping mode on T axis
    unsigned int filter_Min; // filtering mode if texture pixels < screen pixels
    unsigned int filter_Max; // filtering mode if texture pixels > screen pixels
public:
	GLTexture();
    ~GLTexture();
	void GenerateFromFile(const char* name);
    void Bind(unsigned int index=0) const;
};

