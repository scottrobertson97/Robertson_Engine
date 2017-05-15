#include "GameObject.h"



GameObject::GameObject()
{
	isKinetic = false;
	transform = Transform();
	model = Model();
	rigidBody = RigidBody(&transform);
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


