#pragma once
#pragma once
#include <glm/glm.hpp>
#include "Camera.h"
#include "Object.h"
#include "Cube.h"
#include "Compound.h"
#include "Constants.h"
#include <algorithm>
#include <cmath>
#include "CraneTop.h"

class Crane : public Compound {
public:

	Crane() {

		auto top = std::unique_ptr<CraneTop>(new CraneTop());
		addObject(std::move(top));

		// pionowa czesc
		std::unique_ptr<Cube> stem[4]; // stem znaczy trzon
		std::generate(
			begin(stem),
			end(stem),
			[]() { return std::make_unique<Cube>(YELLOW); }
		);

		float thick = 0.05f;
		float height = 10.0f;

		for (auto& x : stem) {

			x->scale(glm::vec3(thick, height, thick));
			x->move(glm::vec3(0.0f, height/2, 0.0f));
		}
		float dbase = 0.5f; // okresla jak bardzo oddalone sa od siebie dwie pierwsze rury trzonu

		stem[0]->move(glm::vec3(-dbase/2, 0.0f, -dbase/2));
		stem[1]->move(glm::vec3(-dbase/2, 0.0f, dbase/2));
		stem[2]->move(glm::vec3(dbase/2, 0.0f, -dbase/2));
		stem[3]->move(glm::vec3(dbase/2, 0.0f, dbase/2));

		for (auto& x : stem) {
			addObject(std::move(x));
		}
		
		// poprzeczki
		const int n_bars = 10;
		std::unique_ptr<Cube> bars[n_bars][4][2];
		for (int i = 0; i < n_bars; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 2; k++) {
					bars[i][j][k] = std::unique_ptr<Cube>(new Cube(YELLOW));
					bars[i][j][k]->move(glm::vec3(-dbase / 2, 0.0f, -dbase / 2));
				}
			}
		}

		float bar_thick = thick * 0.5;

		for (int i = 0; i < n_bars; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 2; k++) {
					bars[i][j][k]->scale(glm::vec3(bar_thick, dbase * sqrt(2.0f), bar_thick));
					bars[i][j][k]->move(glm::vec3(0.0f, (2.0f * i + 0.5f) * dbase, dbase / 2.0f));
					if (j == 0) {
						bars[i][j][k]->rotate(glm::vec3(0.0f, 180.0f, 0.0f));
					}
					if (j == 1) {
						bars[i][j][k]->move(glm::vec3(0.0f, 0.0f, -dbase / 2.0f));
						bars[i][j][k]->rotate(glm::vec3(0.0f, 90.0f, 0.0f));
						bars[i][j][k]->move(glm::vec3(0.0f, 0.0f, dbase / 2.0f));
					}
					else if (j == 2) {
						bars[i][j][k]->move(glm::vec3(0.0f, 0.0f, dbase / 2.0f));
						bars[i][j][k]->rotate(glm::vec3(0.0f, -90.0f, 0.0f));
						bars[i][j][k]->move(glm::vec3(0.0f, 0.0f, -dbase / 2.0f));

					} if (j == 3) {
						bars[i][j][k]->move(glm::vec3(dbase, 0.0f, 0.0f));
					}
					if (k == 0) {
						bars[i][j][k]->rotate(glm::vec3(45.0f, 0.0f, 0.0f)); 
					}
					else {
						bars[i][j][k]->move(glm::vec3(0.0f, dbase, 0.0f));
						bars[i][j][k]->rotate(glm::vec3(-45.0f, 0.0f, 0.0f));
					}
					
				}
			}
		}

		for (int i = 0; i < n_bars; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 2; k++) {
					addObject(std::move(bars[i][j][k]));
				}
			}
		}

		

	}

};
