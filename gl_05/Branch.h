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
		auto leaf5= std::unique_ptr<Leaf>(new Leaf());

		leaf2->rotate2(glm::vec3(-45.0f, 0.0f, 0.0f));
		leaf3->rotate2(glm::vec3(45.0f, 0.0f, 0.0f));
		leaf4->rotate2(glm::vec3(0.0f, 0.0f, -45.0f));
		leaf5->rotate2(glm::vec3(0.0f, 0.0f, 45.0f));
		
		auto leafHeight = 2.0f;
		auto leafMove = 0.81f;
		leaf1->move2(glm::vec3(0.0f, leafHeight * 1.07, 0.0f));
		leaf2->move2(glm::vec3(0.0f, leafHeight, -leafMove));
		leaf3->move2(glm::vec3(0.0f, leafHeight, leafMove));
		leaf4->move2(glm::vec3(leafMove, leafHeight, 0.0f));
		leaf5->move2(glm::vec3(-leafMove, leafHeight, 0.0f));


		addObject(std::move(leaf1));
		addObject(std::move(leaf2));
		addObject(std::move(leaf3));
		addObject(std::move(leaf4));
		addObject(std::move(leaf5));
		auto textNum = 1;
		auto name = "wood1.jpg";
		auto branchBig = std::unique_ptr<Cone>(new Cone(name, textNum));
		auto branchSmall1 = std::unique_ptr<Cone>(new Cone(name, textNum));
		auto branchSmall2 = std::unique_ptr<Cone>(new Cone(name, textNum));
		auto branchSmall3 = std::unique_ptr<Cone>(new Cone(name, textNum));
		auto branchSmall4 = std::unique_ptr<Cone>(new Cone(name, textNum));
		
		branchBig->scale(glm::vec3(0.15f, 2.05f, 0.15f));
		float branchScale = 0.07;
		float branchScaleLong = 1.2;
		branchSmall1->scale(glm::vec3(branchScale, branchScaleLong, branchScale));
		branchSmall2->scale(glm::vec3(branchScale, branchScaleLong, branchScale));
		branchSmall3->scale(glm::vec3(branchScale, branchScaleLong, branchScale));
		branchSmall4->scale(glm::vec3(branchScale, branchScaleLong, branchScale));
		
		auto branchSmallUp = 1.2f;
		branchSmall1->move2(glm::vec3(0.0f, branchSmallUp, 0.0f));
		branchSmall2->move2(glm::vec3(0.0f, branchSmallUp, 0.0f));
		branchSmall3->move2(glm::vec3(0.0f, branchSmallUp, 0.0f));
		branchSmall4->move2(glm::vec3(0.0f, branchSmallUp, 0.0f));
		
		branchSmall1->rotate(glm::vec3(45.0f, 0.0f, 0.0f));
		branchSmall2->rotate(glm::vec3(0.0f, 0.0f, 45.0f));
		branchSmall3->rotate(glm::vec3(-45.0f, 0.0f, 0.0f));
		branchSmall4->rotate(glm::vec3(0.0f, 0.0f, -45.0f));
		

		addObject(std::move(branchBig));
		addObject(std::move(branchSmall1));
		addObject(std::move(branchSmall2));
		addObject(std::move(branchSmall3));
		addObject(std::move(branchSmall4));
	}
};

