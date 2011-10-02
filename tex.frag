#version 130
uniform sampler2D samp;
smooth in vec2 texCoord;
out vec4 fColor;

void main(void)
{
	fColor= texture(samp, texCoord);
	//fColor= vec4(texCoord, 0.0, 1.0);
}

