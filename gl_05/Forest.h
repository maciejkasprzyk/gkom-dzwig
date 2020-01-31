#pragma once
#include <glm/glm.hpp>
#include <GL\glew.h>
#include "Object.h"
#include "Tree.h"
#include "Compound.h"
#include "Constants.h"
#include <algorithm>
#include <cmath>
class Forest : public Compound
{
public:
	Forest() {
		// pionowa czesc
		auto t1 = std::unique_ptr<Tree>(new Tree());
		t1->scale2(glm::vec3(1.4f, 1.4f, 1.4f));
		addObject(std::move(t1));


		auto t2 = std::unique_ptr<Tree>(new Tree());
		t2->scale2(glm::vec3(0.6f, 0.6f, 0.6f));
		t2->move2(glm::vec3(-3.0f, 0.0f, 1.0f));
		addObject(std::move(t2));

		auto t3 = std::unique_ptr<Tree>(new Tree());
		t3->move2(glm::vec3(-2.0f, 0.0f, -3.5f));
		addObject(std::move(t3));

		auto t4 = std::unique_ptr<Tree>(new Tree());
		t4->scale2(glm::vec3(0.6f, 0.6f, 0.6f));
		t4->move2(glm::vec3(1.0f, 0.0f, -2.0f));
		addObject(std::move(t4));


	}
};

