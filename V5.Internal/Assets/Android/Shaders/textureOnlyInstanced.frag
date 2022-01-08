#version 320 es

layout(location = 0) in highp vec4 color;
layout( location = 1) in highp vec2 textCoords;
layout( location = 2) in flat highp float iTextureIndex;

layout(location = 0) out highp vec4 fragColor;

layout (binding = 0) uniform sampler2D textures[16];

void main()
{
	highp vec4 textureColor =   color; 
	switch(int(iTextureIndex))
	{
		case 0:	textureColor *= texture(textures[0], textCoords) ; break;
		case 1:	textureColor *= texture(textures[1], textCoords); break;
		case 2:	textureColor *= texture(textures[2], textCoords); break;
		case 3:	textureColor *= texture(textures[3], textCoords); break;
		case 4:	textureColor *= texture(textures[4], textCoords); break;
		case 5:	textureColor *= texture(textures[5], textCoords); break;
		case 6:	textureColor *= texture(textures[6], textCoords); break;
		case 7:	textureColor *= texture(textures[7], textCoords); break;
		case 8:	textureColor *= texture(textures[8], textCoords); break;
		case 9:	textureColor *= texture(textures[9], textCoords); break;
		case 10:textureColor *= texture(textures[10], textCoords); break;
		case 11:textureColor *= texture(textures[11], textCoords); break;
		case 12:textureColor *= texture(textures[12], textCoords); break;
		case 13:textureColor *= texture(textures[13], textCoords); break;
		case 14:textureColor *= texture(textures[14], textCoords); break;
		case 15:textureColor *= texture(textures[15], textCoords); break;

	}
	fragColor = textureColor;
}
