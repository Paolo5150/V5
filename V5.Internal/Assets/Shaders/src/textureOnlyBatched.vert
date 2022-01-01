#version 460

layout( location = 0) in vec3 aPosition;
layout( location = 1) in vec2 aUV;
layout( location = 2) in vec4 aColor;
layout( location = 3) in float aTextureIndex;

layout( location = 0) out vec4 color;
layout( location = 1) out vec2 textCoords;
layout( location = 2) out flat float iTextureIndex;

layout (std140, binding = 0) uniform ViewProj
{
    mat4 viewProjection;
};

void main()
{

	gl_Position = viewProjection  * vec4(aPosition, 1.0);
	color = aColor;
	textCoords = aUV;
	iTextureIndex = aTextureIndex;
}