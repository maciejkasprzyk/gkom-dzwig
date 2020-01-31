#pragma once

#include "Compound.h"
#include "FenceSegment.h"

#define CENTER_X 10.0
#define CENTER_Z 0.0

class Fence : public Compound
{
public:
	Fence()
	{
		auto segment1 = std::unique_ptr<FenceSegment>(new FenceSegment());
		segment1->move(glm::vec3(segment1->getDepth() / 2, 0.0f, 0.0f));
		addObject(std::move(segment1));

		auto segment2 = std::unique_ptr<FenceSegment>(new FenceSegment());
		segment2->move(glm::vec3(0.0f, 0.0f, segment1->getDepth() / 2));
		segment2->rotate90();
		addObject(std::move(segment2));

		auto segment3 = std::unique_ptr<FenceSegment>(new FenceSegment());
		segment3->move(glm::vec3(-segment3->getDepth() / 2, 0.0f, 0.0f));
		addObject(std::move(segment3));

		auto segment4 = std::unique_ptr<FenceSegment>(new FenceSegment());
		segment4->move(glm::vec3(0.0f, 0.0f, -segment4->getDepth() / 2));
		segment4->rotate90();
		addObject(std::move(segment4));
	}
};