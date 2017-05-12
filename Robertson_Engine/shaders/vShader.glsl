#version 430
layout (location = 0) in vec3 worldLoc;
layout (location = 1) in vec2 modelUV;
layout (location = 2) in vec3 normal;

layout (location = 4) uniform mat4 worldView;

out vec3 fragLoc;
out vec2 fragUV;
out vec3 fragNormal;

void main()
{
	fragLoc = worldLoc;
	fragUV = modelUV;
	fragNormal = normal;
	
	gl_Position = worldView * vec4(worldLoc, 1);
	//gl_Position =  vec4(worldLoc, 1);
}