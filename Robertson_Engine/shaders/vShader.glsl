#version 430
layout (location = 0) in vec3 worldLoc;
layout (location = 1) in vec3 normal;
layout (location = 4) uniform mat4 worldView;

out vec3 fragLoc;
out vec3 fragNormal;

void main()
{
	gl_Position = worldView * vec4(worldLoc, 1);
	fragLoc = worldLoc;
	fragNormal = normal;
}