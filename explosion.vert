#version 130
in vec3 position;
in vec3 colour;

uniform mat4 matrix;
uniform float phase;

smooth out vec4 vColor;

void main(void)
{
	gl_Position = vec4(position*sin(phase), 1.0f)*matrix;
	
	vColor = vec4(1.0-colour, 1.0); 
}

