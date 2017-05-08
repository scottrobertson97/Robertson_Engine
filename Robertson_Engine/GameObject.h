#pragma once
#include "Transform.h"
#include "Model.h";

class GameObject
{
public:
	Transform transform;
	Model model;
	RigidBody ridgidBody;

	GameObject();
	~GameObject();
};

