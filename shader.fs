#version 130

uniform vec3 u_light_pos;

in vec3 v_position;
in vec3 v_normal;

void main()
{
	vec3 toLight = normalize(u_light_pos - v_position);
	float i =  1.0f / sqrt((toLight.x * toLight.x) + (toLight.y * toLight.y) + (toLight.z * toLight.z));

	float angle = dot(toLight, v_normal);
	angle = max(angle, 0.0f);
	i = i * angle;

	float c = i + 0.1f;
	gl_FragColor = vec4(c, c, c, 1.0f);
}
