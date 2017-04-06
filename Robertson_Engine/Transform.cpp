#include "Engine.h"
#include "Transform.h"

void Transform::initialize(vec3 position, vec3 eulerRoation, float maxSpeed, float mass)
{
	this->position = position;
	velocity = vec3();
	acceleration = vec3();
	
	this->eulerRoation = eulerRoation;
	rotation = mat3(glm::yawPitchRoll(eulerRoation.y, eulerRoation.x, eulerRoation.z));

	this->maxSpeed = maxSpeed;
	this->mass = mass;
}

Transform::Transform()
{
	initialize
	(
		vec3(),
		vec3(),
		1,
		1
	);
}

Transform::Transform(vec3 position)
{
	initialize
	(
		position,
		vec3(),
		1,
		1
	);
}

Transform::Transform(vec3 position, float maxSpeed, float mass)
{
	initialize
	(
		position,
		vec3(),
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
	//clamp the acceleration
	acceleration = glm::clamp(acceleration, -1 * maxSpeed, maxSpeed);

	//add acceleration * dt to velocity
	velocity += acceleration * Engine::timer.dt;

	//clamp max velocity
	velocity = glm::clamp(velocity, -1 * maxSpeed, maxSpeed);

	//if the camera is moving too slow, then set velocity to 0
	if (magnitude(velocity) < 0.01)
		velocity = vec3();

	//add velocity * dt to the position
	position += velocity * Engine::timer.dt;

	//zero out the velocity
	acceleration = vec3();

	//get the rotation matrix
	rotation = mat3(glm::yawPitchRoll(eulerRoation.y, eulerRoation.x, eulerRoation.z));

	std::cout << magnitude(velocity);
}

void Transform::push(vec3 force)
{
	acceleration += force / mass;
}

void Transform::drag(float frictionCoefficient)
{

	if (velocity != vec3()) 
	{
		acceleration += glm::normalize(velocity) * -1.f * frictionCoefficient;
	}
}

void Transform::turn(float x, float y, float z)
{
	eulerRoation.x += x;
	eulerRoation.y += y;
	eulerRoation.z += z;
}

float Transform::magnitude(vec3 vector)
{
	float sum = vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
	return glm::sqrt(sum);
}
