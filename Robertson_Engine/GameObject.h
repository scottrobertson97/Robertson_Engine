#pragma once
#include "RigidBody.h"
#include "Model.h";

class GameObject
{
public:
	bool isKinetic;

	Transform transform;
	Model model;
	RigidBody rigidBody;

	GameObject();
	~GameObject();

	virtual void update();
};

