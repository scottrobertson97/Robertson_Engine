#pragma once
#include <glm\gtx\transform.hpp>
#include "Transform.h"
#include "CollisionBound.h"

using glm::mat4;
using glm::mat3;
using glm::vec3;

class RigidBody
{
private:
	
public:
	vec3 velocity;
	vec3 acceleration;

	float maxspeed;
	float mass;
	float scale;

	Transform * transform;

	CollisionBound collisionbound;

	RigidBody(Transform * transform, BoundType type);
	RigidBody();
	~RigidBody();

	void update();
	void push(vec3 force);
	void drag(float frictionCoefficient);
	void turn(float x, float y, float z);

	float magnitude(vec3 vector);
};

