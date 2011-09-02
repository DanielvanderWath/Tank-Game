#version 130
in vec3 position;
in vec3 colour;
uniform mat4 matrix;
smooth out vec4 vColor;

void main(void)
{

	gl_Position = vec4(position, 1.0f)*matrix;
	
	//vColor = vec4(1.0, 1.0f, 1.0, 1.0); 
	vColor = vec4(colour, 1.0); 
}

