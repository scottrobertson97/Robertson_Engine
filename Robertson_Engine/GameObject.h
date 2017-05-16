#pragma once
#include "RigidBody.h"
#include "Model.h"

class GameObject
{
public:
	bool isKinetic;

	Transform transform;
	Model model;
	RigidBody rigidBody;

	GameObject();
	virtual ~GameObject();

	virtual void update();
	virtual void upload();
	void render();

	virtual bool isColliding(const GameObject &other);
};

