#version 330 core
layout (location = 0) in vec3 aPos; // Specifies that input data at location 0 is a 3D vector (vec3)
layout (location = 1) in vec3 aColor; // Specifies that input data at location 1 is a 3D vector (vec3)

out vec3 ourColor; // Output data to fragment shader

uniform mat4 transform; // Uniform variable for transformation matrix
						// set in code


void main()
{
	gl_Position = transform * vec4(aPos, 1.0); // Set the position of the vertex

	ourColor = aColor; // Set the color of the vertex
}
