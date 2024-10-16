#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D textures[16];
uniform int texture_count;
void main()
{
	vec4 result = texture(textures[0], TexCoord);
	for(int i = 1; i < texture_count; ++i)
	{
		result = mix(result,
					texture(textures[i], TexCoord), 0.5);;
	}
	FragColor = result;
}