#version 430
layout (location = 4) uniform mat4 worldView;
layout (location = 0) in vec3 worldLoc;

out vec3 fragLoc;
out vec3 fragNormal;
void main()
{
	fraLoc = worldLoc;
	fragNormal = gl_Normal;
	gl_Position = worldView * vec4(worldLoc, 1);
}

//https://www.opengl.org/sdk/docs/tutorials/ClockworkCoders/lighting.php