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
