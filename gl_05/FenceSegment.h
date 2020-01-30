#pragma once

#include "Cube.h"
#include "Compound.h"
#include <vector>

#define BLOCK_HEIGHT 0.1
#define BLOCK_WIDTH 0.2
#define BLOCK_DEPTH 3.0
#define FENCE_HEIGHT 1.0
#define CENTER_X 10.0
#define CENTER_Z 0.0
#define SPACE 0.1
#define BAR_WIDTH 0.03
#define BAR_DEPTH 0.03
#define N_OF_BARS 100

class FenceSegment : public Compound {
public:
	FenceSegment(glm::vec3 )
	{
		auto bottom = std::unique_ptr<Cube>(new Cube(ORANGE));
		auto top = std::unique_ptr<Cube>(new Cube(ORANGE));

		bottom->move(glm::vec3(CENTER_X, BLOCK_HEIGHT/2, CENTER_Z));
		bottom->scale(glm::vec3(BLOCK_WIDTH, BLOCK_HEIGHT, getDepth()));
		addObject(std::move(bottom));

		top->move(glm::vec3(CENTER_X, FENCE_HEIGHT, CENTER_Z));
		top->scale(glm::vec3(BLOCK_WIDTH, BLOCK_HEIGHT, getDepth()));
		addObject(std::move(top));

		std::unique_ptr<Cube> bars[N_OF_BARS];
		for (int i = 0; i < N_OF_BARS; ++i)
		{
			bars[i] = std::unique_ptr<Cube>(new Cube(BLACK));
			bars[i]->move(glm::vec3(CENTER_X, getBarPos(), CENTER_Z - getOffset() + i * SPACE));
			bars[i]->scale(glm::vec3(BAR_WIDTH, getBarHeight(), BAR_DEPTH));
			addObject(std::move(bars[i]));
		}

	}
private:
	float getBarPos()
	{
		return FENCE_HEIGHT / 2 + BLOCK_HEIGHT / 4;
	}
	float getBarHeight()
	{
		return FENCE_HEIGHT - 3 * BLOCK_HEIGHT / 2;
	}
	float getDepth()
	{
		return N_OF_BARS * SPACE + SPACE;
	}
	float getOffset()
	{
		return (N_OF_BARS * SPACE - SPACE) / 2;
	}
};