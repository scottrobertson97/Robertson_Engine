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
	//create transform matrix
	glm::mat4 transformMat = transform.rotation * glm::translate(transform.position);
	//uploat transform matrix
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
	/*an object is notkinetic*/
	if (!isKinetic || !other.isKinetic)
	{
		printf("one of these objects are not kinetic");
		return false;
	}
	/*aabb-aabb*/
	else if (rigidBody.collisionbound.type == aabb && other.rigidBody.collisionbound.type == aabb)
	{
		//get the mins and maxes of each box
		glm::vec3 thisMin = transform.position + rigidBody.collisionbound.min;
		glm::vec3 thisMax = transform.position + rigidBody.collisionbound.max;
		glm::vec3 otherMin = other.transform.position + other.rigidBody.collisionbound.min;
		glm::vec3 otherMax = other.transform.position + other.rigidBody.collisionbound.max;
		//check if all the mins of one are lesser than the max of the other, and vice versa
		if (thisMin.x < otherMax.x && thisMin.y < otherMax.y && thisMin.z < otherMax.z && otherMin.x < thisMax.x && otherMin.y < thisMax.y && otherMin.z < thisMax.z)
		{
			printf("\nthe objects ARE colliding");
			return true;
		}
		else
		{
			printf("\nthe objects are NOT colliding");
			return false;
		}
	}
	/*circle-circle*/
	else if (rigidBody.collisionbound.type == sphere && other.rigidBody.collisionbound.type == sphere)
	{
		//vector between the centers of the circle
		glm::vec3 vecBetween = transform.position - other.transform.position;
		//sum of radii
		float sum = rigidBody.collisionbound.radius + other.rigidBody.collisionbound.radius;
		//distance between cinters
		float distance = rigidBody.magnitude(vecBetween);
		//check of collision
		if (sum > distance)
		{
			printf("\nthe objects ARE colliding");
			return true;
		}
		else
		{
			printf("\nthe objects are NOT colliding");
			return false;
		}
	}
	/*circle-aabb*/
	else if (rigidBody.collisionbound.type == sphere && other.rigidBody.collisionbound.type == aabb)
	{
		//get distance between centers
		vec3 d = transform.position - other.transform.position;
		//get clostest point on box to the sphere
		vec3 p = other.transform.position + glm::clamp(d, other.rigidBody.collisionbound.min, other.rigidBody.collisionbound.max);
		//get the vec between that point and the center of the sphere
		vec3 dp = transform.position - p;
		//check for collision
		if(glm::dot(dp,dp) < rigidBody.collisionbound.radius * rigidBody.collisionbound.radius)
		{
			printf("\nthe objects ARE colliding");
			return true;
		}
		else
		{
			printf("\nthe objects are NOT colliding");
			return false;
		}
	}
	/*aabb-circle*/
	else if (rigidBody.collisionbound.type == aabb && other.rigidBody.collisionbound.type == sphere)
	{
		//get distance between centers
		vec3 d = other.transform.position - transform.position;
		//get clostest point on box to the sphere
		vec3 p = transform.position + glm::clamp(d, rigidBody.collisionbound.min, rigidBody.collisionbound.max);
		//get the vec between that point and the center of the sphere
		vec3 dp = other.transform.position - p;
		//check for collision
		if (glm::dot(dp, dp) < other.rigidBody.collisionbound.radius * other.rigidBody.collisionbound.radius)
		{
			printf("\nthe objects ARE colliding");
			return true;
		}
		else
		{
			printf("\nthe objects are NOT colliding");
			return false;
		}
	}
	else
	{
		printf("\nsomething went wrong with the collision");
		return false;
	}
}




