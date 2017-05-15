#include "GameObject.h"

GameObject::GameObject()
{
	isKinetic = false;
	transform = Transform();
	model = Model();
	rigidBody = RigidBody(&transform, sphere);
}


GameObject::~GameObject()
{
}

void GameObject::update()
{
	if (isKinetic)
		rigidBody.update();
}

void GameObject::upload()
{
	glm::mat4 transformMat = transform.rotation * glm::translate(transform.position);

	glUniformMatrix4fv(3, 1, GL_FALSE, &transformMat[0][0]);
}

void GameObject::render()
{
	model.bind();
	model.texture.bind();
	upload();
	model.draw();
}

bool GameObject::isColliding(const GameObject &other)
{
	if (!isKinetic || !other.isKinetic)
	{
		printf("one of these objects are not kinetic");
		return false;
	}
	else if (rigidBody.collisionbound.type == aabb && other.rigidBody.collisionbound.type == aabb)
	{
		return false;
	}
	else if (rigidBody.collisionbound.type == sphere && other.rigidBody.collisionbound.type == sphere)
	{
		glm::vec3 vecBetween = transform.position - other.transform.position;
		float sum = rigidBody.collisionbound.radius + other.rigidBody.collisionbound.radius;
		float distance = rigidBody.magnitude(vecBetween);
		if (sum > distance)
		{
			printf("\nthey are colliding");
			return true;
		}
		else
		{
			printf("\nthey are no colliding");
			return false;
		}
	}
	else if (rigidBody.collisionbound.type == aabb && other.rigidBody.collisionbound.type == sphere)
	{
		return false;
	}
	else if (rigidBody.collisionbound.type == aabb && other.rigidBody.collisionbound.type == sphere)
	{
		return false;
	}
	else
	{
		return false;
	}
}


