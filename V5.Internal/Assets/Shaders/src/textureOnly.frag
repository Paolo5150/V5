#version 460

layout(location = 0) in vec3 color;
layout( location = 1) in vec2 textCoords;
layout(location = 0) out vec4 fragColor;

uniform sampler2D albedo;

layout (std140, binding = 0) uniform TestColor
{
    vec4 testColor;
};

void main()
{
	vec3 textureColor = texture(albedo, textCoords).xyz * testColor.xyz; 
	fragColor = vec4(textureColor,1.0);
}