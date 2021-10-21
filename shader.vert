#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 Projection;
uniform mat4 Transform;

void main(){
	gl_Position = Projection * Transform * vec4(position,1.0f);
}