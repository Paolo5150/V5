#version 320 es

layout( location = 0) in vec3 aPosition;
layout( location = 1) in vec2 aUV;

layout( location = 2) in float textureIndex;
layout( location = 3) in vec3 position;
layout( location = 4) in vec2 scale;
layout( location = 5) in vec4 iColor;

layout( location = 0) out vec4 color;
layout( location = 1) out vec2 textCoords;
layout( location = 2) out flat float iTextureIndex;

layout (std140, binding = 0) uniform ViewProj
{
    mat4 viewProjection;
};

void main()
{
	mat4 modelMat = mat4(1.0);
	modelMat[0][0] = scale[0];
	modelMat[1][1] = scale[1];
	
	modelMat[3][0] = position[0];
	modelMat[3][1] = position[1];
	modelMat[3][2] = position[2];
	
	
	gl_Position =  viewProjection * modelMat * vec4(aPosition, 1.0);
	color = iColor;
	textCoords = aUV;
	iTextureIndex = textureIndex;
}