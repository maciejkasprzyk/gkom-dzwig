#pragma once
#include <glm/glm.hpp>
#include <GL\glew.h>
#include "Object.h"
#include "Cube.h"
#include "Compound.h"
#include "Constants.h"
#include <algorithm>
#include <cmath>
class Fence : public Compound
{
public:
	Fence() {
		const int fenceLen = 30;
		std::unique_ptr<Cube> plates[fenceLen]; // stem znaczy trzon
		std::generate(
			begin(plates),
			end(plates),
			[]() { return std::make_unique<Cube>("wood1.jpg", 6); }
		);
		auto distanceDiff = 0.3f;
		auto dist = 0.0f;
		for (auto& x : plates) {
			x->scale2(glm::vec3(0.15f, 2.5f, 0.15f));
			x->move2(glm::vec3(1.0f, 0.0f, dist));
			dist += 0.3;
		}

		for (auto& x : plates) {
			addObject(std::move(x));
		}
		std::unique_ptr<Cube> connectors[fenceLen * 2 - 2]; // stem znaczy trzon
		std::generate(
			begin(connectors),
			end(connectors),
			[]() { return std::make_unique<Cube>("wood1.jpg", 1); }
		);
		dist = 0.15f;
		auto y_move = 0.1f;
		auto y_h = 0.8f;
		int i = 0;
			for (auto& x : connectors) {
				x->scale2(glm::vec3(0.15f, 0.15f, 0.15f));
				auto y_diff = (i % 2) ? y_h : 0.0;
				auto distDiff = (i++ % 2) ? distanceDiff : 0.0;
				x->move2(glm::vec3(1.0f, y_move + y_diff, dist));
				dist += distDiff;
			}

		for (auto& x : connectors) {
			addObject(std::move(x));
		}

	}
};

