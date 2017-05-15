#include "CollisionBound.h"



CollisionBound::CollisionBound()
{
	offset = glm::vec3();
	min = glm::vec3(-1, -1, -1);
	max = glm::vec3(1, 1, 1);
	radius = 1;
	type = sphere;
}


CollisionBound::~CollisionBound()
{
}
