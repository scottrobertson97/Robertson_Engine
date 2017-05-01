#include "Engine.h"
#include "RigidBody.h"

//void RigidBody::initialize(vec3 position, vec3 eulerRoation, float maxSpeed, float mass)
//{
//	this->position = position;
//	velocity = vec3();
//	acceleration = vec3();
//
//	this->eulerRoation = eulerRoation;
//	rotation = mat3(glm::yawPitchRoll(eulerRoation.y, eulerRoation.x, eulerRoation.z));
//
//	this->maxSpeed = maxSpeed;
//	this->mass = mass;
//}
//
//RigidBody::RigidBody()
//{
//	initialize
//	(
//		vec3(),
//		vec3(),
//		1,
//		1
//	);
//}
//
//RigidBody::RigidBody(vec3 position)
//{
//	initialize
//	(
//		position,
//		vec3(),
//		1,
//		1
//	);
//}
//
//RigidBody::RigidBody(vec3 position, float maxSpeed, float mass)
//{
//	initialize
//	(
//		position,
//		vec3(),
//		maxSpeed,
//		mass
//	);
//}
//
//RigidBody::RigidBody(vec3 position, vec3 eulerRoation, float maxSpeed, float mass)
//{
//	initialize
//	(
//		position,
//		eulerRoation,
//		maxSpeed,
//		mass
//	);
//}

RigidBody::RigidBody(Transform transform)
{
	this->transform = transform;
}

RigidBody::~RigidBody()
{
}

void RigidBody::update()
{
	//clamp the acceleration
	acceleration = glm::clamp(acceleration, -1 * maxSpeed, maxSpeed);

	//add acceleration * dt to velocity
	velocity += acceleration * Engine::timer.dt;

	//clamp max velocity
	velocity = glm::clamp(velocity, -1 * maxSpeed, maxSpeed);

	//if the object is moving too slow, then set velocity to 0
	if (magnitude(velocity) < 0.01)
		velocity = vec3();

	//add velocity * dt to the position
	transform.position += velocity * Engine::timer.dt;

	//zero out the velocity
	acceleration = vec3();
}

void RigidBody::push(vec3 force)
{
	acceleration += force / mass;
}

void RigidBody::drag(float frictionCoefficient)
{
	if (velocity != vec3())
	{
		acceleration += glm::normalize(velocity) * -1.f * frictionCoefficient;
	}
}

void RigidBody::turn(float x, float y, float z)
{
	transform.rotation *= glm::yawPitchRoll(x, y, z);
}

float RigidBody::magnitude(vec3 vector)
{
	float sum = vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
	return glm::sqrt(sum);
}
