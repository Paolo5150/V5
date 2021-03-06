#version 460

layout( location = 0) in vec3 aPosition;
layout( location = 1) in vec2 aUV;

layout( location = 2) in float textureIndex;
layout( location = 3) in vec4 iColor;
layout( location = 4) in mat4 modelMat;

layout( location = 0) out vec4 color;
layout( location = 1) out vec2 textCoords;
layout( location = 2) out flat float iTextureIndex;

layout (std140, binding = 0) uniform ViewProj
{
    mat4 viewProjection;
};

void main()
{

	gl_Position = viewProjection * modelMat * vec4(aPosition, 1.0);
	color = iColor;
	textCoords = aUV;
	iTextureIndex = textureIndex;
}