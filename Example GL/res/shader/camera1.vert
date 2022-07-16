#version 330 core
layout (location = 0) in vec2 apos;
layout (location = 1) in vec4 acolor;
uniform mat3 proj;
out vec4 vertexColor; 

void main()
{
     gl_Position = vec4((proj * vec3(apos, 1)).xy, 0, 1);
    vertexColor = acolor; 
}