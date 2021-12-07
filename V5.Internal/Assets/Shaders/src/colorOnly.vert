#version 460

layout( location = 0) in vec3 aPosition;
layout( location = 1) in vec3 aColor;

layout( location = 2) in vec3 offset;
layout( location = 3) in vec3 iColor;

layout( location = 0) out vec3 color;

layout (std140, binding = 0) uniform ViewProj
{
    mat4 viewProjection;
};

void main()
{

	gl_Position = viewProjection * vec4(aPosition + offset, 1.0);
	color = aColor * iColor;
}