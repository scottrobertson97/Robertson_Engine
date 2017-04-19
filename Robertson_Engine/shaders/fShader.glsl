#version 430

uniform sampler2D myTexture;

uniform vec3 lightLoc;
uniform vec3 cameraLoc;

in vec3 fragLoc;
in vec2 fragUV;
in vec3 fragNormal;

const vec3 ambientVal = 		vec3(.1);
const vec3 diffuseVal = 		vec3(.6);
const vec3 specularVal = 		vec3(.6);
const vec3 specularAlphaVal = 	vec3(1);

void main()
{
	vec3 L = normalize(lightLoc - fragLoc);
	vec3 V = normalize(cameraLoc - fragLoc);
	vec3 H = normalize(L + V);
	vec3 N = fragNormal;
	
	float diffuse = max(dot(L, N), 0);
	float specular = pow(max(dot(N, H), 0), 16);
	
	vec4 shade = vec4(ambientVal + diffuseVal * diffuse + specularVal * specular * specularAlphaVal, 1);
	gl_FragColor = texture(myTexture, fragUV) * shade;
}