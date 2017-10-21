#version 130
uniform mat4 u_model;

out vec4 v_position;
out vec4 v_normal;

void main()
{
	v_normal = gl_Normal;
	v_position = u_model * gl_Vertex;
	
	gl_Position = v_position;
}
