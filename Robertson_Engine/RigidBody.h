#pragma once
#include <glm\gtx\transform.hpp>
#include "Transform.h"
#include "AABB.h"
#include "Sphere.h"

using glm::mat4;
using glm::mat3;
using glm::vec3;

class RigidBody
{
private:
	//void initialize(vec3 position, vec3 eulerRoation, float maxSpeed, float mass);
	Transform transform;
public:
	vec3 eulerRoation;
	mat3 rotation;

	vec3 position;
	vec3 velocity;
	vec3 acceleration;

	float maxSpeed;
	float mass;
	float scale;

	RigidBody(Transform transform);
	~RigidBody();

	//Transform();
	//Transform(vec3 position);
	//Transform(vec3 position, float maxSpeed, float mass);
	//Transform(vec3 position, vec3 eulerRoation, float maxSpeed, float mass);
	//~Transform();

	void update();
	void push(vec3 force);
	void drag(float frictionCoefficient);
	void turn(float x, float y, float z);

	float magnitude(vec3 vector);

	bool isColliding(Sphere s1, Sphere s2);
	bool isColliding(AABB b, Sphere s);
	bool isColliding(Sphere s, AABB b);
	bool isColliding(AABB b1, AABB b2);
};

