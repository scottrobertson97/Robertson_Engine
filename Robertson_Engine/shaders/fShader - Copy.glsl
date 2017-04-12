#version 430
uniform vec3 lightLoc;
uniform vec3 cameraLoc;
in vec3 fragLoc;
in vec3 fragNormal;

const vec4 material = vec4(0.2, 0.6, 1.0, 1.0);
const float ambientVal = 0.2;
const float diffuseVal = 0.6;
const float specularVal = 1.0;
const specularAlphaVal = 1.0;

void main()
{
	vec3 L = normalize(lightLoc - fragLoc);
	vec3 V = normalize(cameraLoc - fragLoc);
	vec3 H = normalize(L + E);
	vec3 N = fragNormal;
		
	float diffuse = max(dot(L, N), 0.0);
	float specular = pow(dot(H, N), 16);
	
	gl_FragColor = vec4(ambientVal,
						diffuseVal * diffuse,
						specularVal * specular,
					specularAlphaVal);
}