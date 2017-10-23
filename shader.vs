#version 130
uniform mat4 u_modelViewProjection;
uniform mat4 u_normal;

out vec3 v_position;
out vec3 v_normal;

void main()
{

	v_normal = normalize((u_normal * vec4(gl_Normal, 0.0f)).xyz);

	vec4 position  = u_modelViewProjection * gl_Vertex;

	v_position = position.xyz;
	
	gl_Position = position;
}
