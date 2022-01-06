#version 460

layout(location = 0) in vec3 color;
layout( location = 1) in vec2 textCoords;

layout(location = 0) out vec4 fragColor;

layout (binding = 0) uniform sampler2D textures[32];


layout (std140, binding = 0) uniform TestColor
{
    vec4 testColor;
};

void main()
{
	vec3 textureColor =  texture(textures[0], textCoords).xyz * texture(textures[1], textCoords).xyz *testColor.xyz ; 
	fragColor = vec4(textureColor,1.0);
}