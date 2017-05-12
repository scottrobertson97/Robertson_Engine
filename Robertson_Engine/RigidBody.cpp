#include "Engine.h"
#include "RigidBody.h"

RigidBody::RigidBody(Transform * transform)
{
	velocity = vec3();
	acceleration = vec3();
	maxspeed = 1;
	mass = 1;
	scale = 1;
	this->transform = transform;
	collisionbound = CollisionBound();
	collisionbound.position = transform->position;
}

RigidBody::RigidBody()
{
}

RigidBody::~RigidBody()
{
}

void RigidBody::update()
{

	//clamp the acceleration
	acceleration = glm::clamp(acceleration, -1 * maxspeed, maxspeed);

	//add acceleration * dt to velocity
	velocity += acceleration * Engine::timer.dt;

	//clamp max velocity
	velocity = glm::clamp(velocity, -1 * maxspeed, maxspeed);

	//if the object is moving too slow, then set velocity to 0
	if (magnitude(velocity) < 0.01)
		velocity = vec3();

	//add velocity * dt to the position
	transform->position += velocity * Engine::timer.dt;

	//update the collision position
	collisionbound.position = transform->position;

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

void RigidBody::turn(float yaw, float pitch, float roll)
{
	transform->rotation *= glm::yawPitchRoll(yaw, pitch, roll);
}

float RigidBody::magnitude(vec3 vector)
{
	float sum = vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
	return glm::sqrt(sum);
}

bool RigidBody::isColliding(Sphere s)
{
	return false;
}

bool RigidBody::isColliding(AABB b)
{
	return false;
}
