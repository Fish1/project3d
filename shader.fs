#version 130
uniform float u_red;
uniform float u_green;
uniform float u_blue;

uniform vec4 u_light_pos;

in vec4 v_position;
in vec4 v_normal;

void main()
{
	vec4 ivec = u_light_pos - v_position;
	float i = (ivec.x * ivec.x) + (ivec.y * ivec.y) + (ivec.z * ivec.z) + (ivec.w * ivec.w);
	i = 1/i;
	i = i * 50.0f;

	d = dot(ivec, v_normal);

	gl_FragColor = vec4(i / 10.0f, i / 10.0f, i / 10.0f, 1.0f);
}
