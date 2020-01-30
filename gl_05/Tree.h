#pragma once
#include "Compound.h"
#include "Branch.h"
class Tree : public Compound
{
public:
	Tree() {
		auto branch = std::unique_ptr<Branch>(new Branch());
		auto branch2 = std::unique_ptr<Branch>(new Branch());
		auto branch3 = std::unique_ptr<Branch>(new Branch());
		auto branch4 = std::unique_ptr<Branch>(new Branch());
		auto branch5 = std::unique_ptr<Branch>(new Branch());

		branch->rotate2(glm::vec3(45.0f, 0.0f, 0.0f));

		branch2->rotate2(glm::vec3(-45.0f, 0.0f, 0.0f));

		branch3->rotate2(glm::vec3(30.0f, 0.0f, 0.0f));
		branch3->rotate2(glm::vec3(0.0f, 90.0f, 0.0f));

		branch4->rotate2(glm::vec3(15.0f, 0.0f, 0.0f));
		branch4->rotate2(glm::vec3(15.0f, -90.0f, 0.0f));

		branch5->rotate2(glm::vec3(0.0f, 0.0f, 0.0f));

		float branchUp = 1.3f;
		branch->move2(glm::vec3(0.0f, branchUp + 0.1f, 0.0f));
		branch2->move2(glm::vec3(0.0f, branchUp, 0.0f));
		branch3->move2(glm::vec3(0.0f, branchUp - 0.1f, 0.0f));
		branch4->move2(glm::vec3(0.0f, branchUp + 0.01f, 0.0f));
		branch5->move2(glm::vec3(0.0f, branchUp, 0.0f));


		addObject(std::move(branch));
		addObject(std::move(branch2));
		addObject(std::move(branch3));
		addObject(std::move(branch4));
		addObject(std::move(branch5));
		
		

		auto stem = std::unique_ptr<Cone>(new Cone(GREY));
		stem->scale(glm::vec3(0.5f, 3.05f, 0.5f));


		addObject(std::move(stem));
	}

};

