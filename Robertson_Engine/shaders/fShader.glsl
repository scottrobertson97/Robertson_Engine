#version 430
uniform vec2 WindowSize;

uniform vec3 lightLoc;
uniform vec3 cameraLoc;
in vec3 fragLoc;
in vec3 fragNormal;

const vec4 material = vec4(0.2, 0.6, 1.0, 1.0);
const float
void main()
{
	float diffuse = max(dot(normalize(fragLoc), normalize(fragNormal)), 0.0);

	vec3 L = normalize(lightLoc - fragLoc);
	vec3 E = normalize(cameraLoc - fragLoc);
	vec3 H = normalize(L + E);
		
	
	float x = gl_FragCoord.x / WindowSize.x * 0.9 + 0.05;
	float y = gl_FragCoord.y / WindowSize.y * 0.9 + 0.05;
	float avg = ((0.9-x)+(0.9-y))/2;
	gl_FragColor = vec4(material.x + diffuse * material.y);
}