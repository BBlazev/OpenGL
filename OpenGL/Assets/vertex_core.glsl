#version 330 core
layout (location = 0) in vec3 aPos; // Specifies that input data at location 0 is a 3D vector (vec3)


void main()
{
	gl_Position = vec4(aPos, 1.0); // Set the position of the vertex
}
