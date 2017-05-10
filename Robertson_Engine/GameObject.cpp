#include "GameObject.h"



GameObject::GameObject()
{
	isKinetic = false;
	transform = Transform();
	model = Model();
	rigidBody = RigidBody();
	rigidBody.transform = transform;
}


GameObject::~GameObject()
{
}

void GameObject::update()
{
	if (isKinetic)
		rigidBody.update();
}
