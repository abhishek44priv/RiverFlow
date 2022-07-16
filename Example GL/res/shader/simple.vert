#version 330 core
layout (location = 0) in vec2 apos;
layout (location = 1) in vec4 acolor;
uniform vec2 screen;
out vec4 vertexColor; 

void main()
{
    vec2 sv=vec2(apos.x/screen.x,apos.y/screen.y);
    gl_Position = vec4(sv,0.0, 1.0); 
    vertexColor = acolor; 
}
