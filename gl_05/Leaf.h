#pragma once
#include <glm/glm.hpp>
#include <GL\glew.h>
#include "Object.h"
#include "Cone.h"
#include "Compound.h"
#include "Constants.h"
#include <algorithm>
#include <cmath>
class Leaf : public Compound 
{
public:
	Leaf() {
		auto cone1 = std::unique_ptr<Cone>(new Cone(GREEN));
		auto cone2 = std::unique_ptr<Cone>(new Cone(GREEN));
		cone2->rotate(glm::vec3(180.0f, 0.0f, 0.0f));

		auto s = 0.3f;
		cone2->scale(glm::vec3(s, s, s));
		cone1->scale(glm::vec3(s, s, s));
		//cone2->move(glm::vec3(0.0f, 1.0f, 0.0f));
		addObject(std::move(cone1));
		addObject(std::move(cone2));
	}
};

