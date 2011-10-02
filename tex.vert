#version 130
in vec3 position;
in vec2 vtexCoord;
uniform mat4 matrix;
smooth out vec2 texCoord;

void main(void)
{

	gl_Position = vec4(position, 1.0f)*matrix;
	texCoord=vtexCoord;
}

