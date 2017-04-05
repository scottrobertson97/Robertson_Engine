#include "Engine.h"
#include "Transform.h"

void Transform::initialize(vec3 position, vec3 eulerRoation, float maxSpeed, float mass)
{
	this->position = position;
	velocity = vec3(0, 0, 0);
	acceleration = vec3(0, 0, 0);
	
	this->eulerRoation = eulerRoation;
	rotation = mat3(glm::yawPitchRoll(eulerRoation.y, eulerRoation.x, eulerRoation.z));

	this->maxSpeed = maxSpeed;
	this->mass = mass;
}

Transform::Transform()
{
	initialize
	(
		vec3(0, 0, 0),
		vec3(0, 0, 0),
		1,
		1
	);
}

Transform::Transform(vec3 position)
{
	initialize
	(
		position,
		vec3(0, 0, 0),
		1,
		1
	);
}

Transform::Transform(vec3 position, float maxSpeed, float mass)
{
	initialize
	(
		position,
		vec3(0, 0, 0),
		maxSpeed,
		mass
	);
}

Transform::Transform(vec3 position, vec3 eulerRoation, float maxSpeed, float mass)
{
	initialize
	(
		position, 
		eulerRoation, 
		maxSpeed, 
		mass
	);
}

Transform::~Transform()
{
}

void Transform::update()
{
	velocity += acceleration * Engine::timer.dt;
	if (velocity != vec3())
		velocity = glm::normalize(velocity) * maxSpeed;
	position += velocity * Engine::timer.dt;

	acceleration = vec3(0, 0, 0);

	rotation = mat3(glm::yawPitchRoll(eulerRoation.y, eulerRoation.x, eulerRoation.z));
}

void Transform::push(vec3 force)
{
	acceleration += force / mass;
}

void Transform::drag(float frictionCoefficient)
{

	if (velocity != vec3()) 
	{
		vec3 friction = velocity * -1.f;
		friction = glm::normalize(friction);
		friction *= frictionCoefficient;
		acceleration += friction;
	}
}

void Transform::turn(float x, float y, float z)
{
	eulerRoation.x += x;
	eulerRoation.y += y;
	eulerRoation.z += z;
}
