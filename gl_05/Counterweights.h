#pragma once

#include "Compound.h"
#include "Cube.h"

class Counterweights : public Compound
{

public:
	Counterweights() {
		float dbase = 0.5f;
		//przeciwwagi
		auto counterweight1 = std::unique_ptr<Cube>(new Cube("betonowy.jpg", 1));
		counterweight1->scale(glm::vec3(1.4f, 0.17f, 0.4f));
		counterweight1->move(glm::vec3(0.2f, 0.5f, 0.25f));

		auto counterweight2 = std::unique_ptr<Cube>(new Cube("betonowy.jpg", 1));
		counterweight2->scale(glm::vec3(1.4f, 0.17f, 0.4f));
		counterweight2->move(glm::vec3(0.2f, 0.7f, 0.25f));

		auto counterweight3 = std::unique_ptr<Cube>(new Cube("betonowy.jpg", 1));
		counterweight3->scale(glm::vec3(1.4f, 0.17f, 0.4f));
		counterweight3->move(glm::vec3(0.2f, 0.9f, 0.25f));

		addObject(std::move(counterweight1));
		addObject(std::move(counterweight2));
		addObject(std::move(counterweight3));

		this->rotate2(glm::vec3(0.0f, 0.0f, 90.0f));
		this->move2(glm::vec3(8 * dbase, 10.0f, -dbase / 2));
	}
};

