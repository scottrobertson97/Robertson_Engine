#pragma once
#include <glm\gtx\transform.hpp>

using glm::mat4;
using glm::mat3;
using glm::vec3;

class Transform
{
private:
	void initialize(vec3 position, vec3 eulerRoation, float maxSpeed, float mass);
public:
	vec3 eulerRoation;
	mat3 rotation;

	vec3 position;
	vec3 velocity;
	vec3 acceleration;
	
	float maxSpeed;
	float mass;
	float scale;

	Transform();
	Transform(vec3 position);
	Transform(vec3 position, float maxSpeed, float mass);
	Transform(vec3 position, vec3 eulerRoation, float maxSpeed, float mass);
	~Transform();

	void update();
	void push(vec3 force);
	void drag(float frictionCoefficient);
	void turn(float x, float y, float z);

	float magnitude(vec3 vector);
};

