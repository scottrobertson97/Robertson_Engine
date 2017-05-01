#pragma once
#include "Transform.h"
#include "Model.h";

class GameObject
{
public:
	Transform transform;
	Model model;

	GameObject();
	~GameObject();
};

