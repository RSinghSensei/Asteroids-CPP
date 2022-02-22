#version 330 core

out vec4 FragColor;
in vec3 ourColor;
in vec2 ourTexCoords;

uniform sampler2D ourTexture;
void main(){
	vec4 tempTexColor = texture(ourTexture, ourTexCoords);
	if (tempTexColor.a < 0.1)
	{
		discard;
	}
	FragColor = tempTexColor;
}