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
		std::unique_ptr<Tree> stem[30]; // stem znaczy trzon
		std::generate(
			begin(stem),
			end(stem),
			[]() { return std::make_unique<Tree>(); }
		);

		for (auto& x : stem) {
			x->move2(glm::vec3(-50.0f + rand() % 100, 0.0f, -50.0f + rand() % 100));
		}

		for (auto& x : stem) {
			addObject(std::move(x));
		}
	}
};

