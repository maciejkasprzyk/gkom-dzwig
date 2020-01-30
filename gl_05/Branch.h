#pragma once
#include <glm/glm.hpp>
#include <GL\glew.h>
#include "Object.h"
#include "Cone.h"
#include "Cube.h"
#include "Leaf.h"
#include "Compound.h"
#include "Constants.h"
#include <algorithm>
#include <cmath>
class Branch : public Compound
{
public:
	Branch() {
		auto leaf1= std::unique_ptr<Leaf>(new Leaf());
		auto leaf2= std::unique_ptr<Leaf>(new Leaf());
		auto leaf3= std::unique_ptr<Leaf>(new Leaf());
		auto leaf4= std::unique_ptr<Leaf>(new Leaf());

		auto leafHeight = 2.6f;
		leaf1->move2(glm::vec3(0.9f, leafHeight, 0.0f));
		leaf2->move2(glm::vec3(0.5f, leafHeight, 0.1f));
		leaf3->move2(glm::vec3(0.2f, leafHeight, 0.3f));
		leaf4->move2(glm::vec3(0.0f, leafHeight, 0.0f));

		addObject(std::move(leaf1));
		addObject(std::move(leaf2));
		addObject(std::move(leaf3));
		addObject(std::move(leaf4));

		auto branchBig = std::unique_ptr<Cone>(new Cone(GREY));
		auto branchSmall1 = std::unique_ptr<Cone>(new Cone(GREY));
		auto branchSmall2 = std::unique_ptr<Cone>(new Cone(GREY));
		auto branchSmall3 = std::unique_ptr<Cone>(new Cone(GREY));
		auto branchSmall4 = std::unique_ptr<Cone>(new Cone(GREY));
		
		branchBig->scale(glm::vec3(0.3f, 2.5f, 0.3f));
		float branchScale = 0.07;
		branchSmall1->scale(glm::vec3(branchScale, 1.0f, branchScale));
		branchSmall2->scale(glm::vec3(branchScale, 1.0f, branchScale));
		branchSmall3->scale(glm::vec3(branchScale, 1.0f, branchScale));
		branchSmall4->scale(glm::vec3(branchScale, 1.0f, branchScale));
		
		auto branchSmallUp = 1.8f;
		branchSmall1->move2(glm::vec3(0.0f, branchSmallUp, 0.0f));
		branchSmall2->move2(glm::vec3(0.0f, branchSmallUp, 0.0f));
		branchSmall3->move2(glm::vec3(0.0f, branchSmallUp, 0.0f));
		branchSmall4->move2(glm::vec3(0.0f, branchSmallUp, 0.0f));
		
		branchSmall1->rotate(glm::vec3(45.0f, 45.0f, 0.0f));
		branchSmall2->rotate(glm::vec3(0.0f, 45.0f, 45.0f));
		branchSmall3->rotate(glm::vec3(-45.0f, 45.0f, 30.0f));
		branchSmall4->rotate(glm::vec3(0.0f, 45.0f, -45.0f));
		

		addObject(std::move(branchBig));
		addObject(std::move(branchSmall1));
		addObject(std::move(branchSmall2));
		addObject(std::move(branchSmall3));
		addObject(std::move(branchSmall4));
	}
};

