#version 460

layout(location = 0) in vec3 color;
layout( location = 1) in vec2 textCoords;
layout(location = 0) out vec4 fragColor;

uniform sampler2D albedo;

void main()
{
	vec3 textureColor = texture(albedo, textCoords).xyz; 
	fragColor = vec4(textureColor,1.0);
}