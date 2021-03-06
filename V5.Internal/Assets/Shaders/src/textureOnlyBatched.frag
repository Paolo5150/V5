#version 460

layout(location = 0) in vec4 color;
layout( location = 1) in vec2 textCoords;
layout( location = 2) in flat float iTextureIndex;

layout(location = 0) out vec4 fragColor;

layout (binding = 0) uniform sampler2D textures[32];

void main()
{
	vec4 textureColor =   color; 
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
		case 16:textureColor *= texture(textures[16], textCoords); break;
		case 17:textureColor *= texture(textures[17], textCoords); break;
		case 18:textureColor *= texture(textures[18], textCoords); break;
		case 19:textureColor *= texture(textures[19], textCoords); break;
		case 20:textureColor *= texture(textures[20], textCoords); break;
		case 21:textureColor *= texture(textures[21], textCoords); break;
		case 22:textureColor *= texture(textures[22], textCoords); break;
		case 23:textureColor *= texture(textures[23], textCoords); break;
		case 24:textureColor *= texture(textures[24], textCoords); break;
		case 25:textureColor *= texture(textures[25], textCoords); break;
		case 26:textureColor *= texture(textures[26], textCoords); break;
		case 27:textureColor *= texture(textures[27], textCoords); break;
		case 28:textureColor *= texture(textures[28], textCoords); break;
		case 29:textureColor *= texture(textures[29], textCoords); break;
		case 30:textureColor *= texture(textures[30], textCoords); break;
		case 31:textureColor *= texture(textures[31], textCoords); break;
	}
	fragColor = textureColor;
}