#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 Projection;
uniform mat4 Transform;

out vec3 ourColor;
out vec2 ourTexCoords;

void main(){
	gl_Position = Projection * Transform * vec4(position,1.0f);
	ourColor = aColor;
	ourTexCoords = aTexCoords;
}