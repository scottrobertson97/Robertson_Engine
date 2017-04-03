#version 430
layout (location = 4) uniform mat4 worldView;
layout (location = 0) in vec3 worldLoc;
void main()
{
	gl_Position = worldView * vec4(worldLoc, 1);
}