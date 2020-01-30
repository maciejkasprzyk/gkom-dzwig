#pragma once
#include <glm/glm.hpp>
#include "Camera.h"
#include "Object.h"
#include "Cube.h"
#include "Compound.h"
#include "Constants.h"
#include <algorithm>
#include <cmath>

class CraneBottom : public Compound
{
public:
	CraneBottom() {


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
			x->move(glm::vec3(0.0f, height / 2, 0.0f));
		}
		float dbase = 0.5f; // okresla jak bardzo oddalone sa od siebie dwie pierwsze rury trzonu

		stem[0]->move(glm::vec3(-dbase / 2, 0.0f, -dbase / 2));
		stem[1]->move(glm::vec3(-dbase / 2, 0.0f, dbase / 2));
		stem[2]->move(glm::vec3(dbase / 2, 0.0f, -dbase / 2));
		stem[3]->move(glm::vec3(dbase / 2, 0.0f, dbase / 2));

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
		
		//budka
		float angle = 10.0f;

		auto budka = std::unique_ptr<Cube>(new Cube(YELLOW));
		budka->scale(glm::vec3(0.05f, 2.0f, 0.05f));
		budka->move(glm::vec3(0.0f, 1.0f, 0.0f));
		budka->rotate2(glm::vec3(0.0f, 0.0f, angle));
		budka->rotate2(glm::vec3(0.0f, 45.0f, 0.0f));
		budka->move2(glm::vec3(dbase/2, 0.0f, -dbase/2));
		budka->move2(glm::vec3(0.0f, 10.0f , 0.0f));


		addObject(std::move(budka));

		auto budka2 = std::unique_ptr<Cube>(new Cube(YELLOW));
		budka2->scale(glm::vec3(0.05f, 2.0f, 0.05f));
		budka2->move(glm::vec3(0.0f, 1.0f, 0.0f));
		budka2->rotate2(glm::vec3(0.0f, 0.0f, angle));
		budka2->rotate2(glm::vec3(0.0f, 45.0f, 0.0f));
		budka2->move2(glm::vec3(dbase / 2, 0.0f, -dbase / 2));
		budka2->move2(glm::vec3(0.0f, 10.0f, 0.0f));
		budka2->rotate2(glm::vec3(0.0f, 90.0f, 0.0f));

		addObject(std::move(budka2));

		auto budka3 = std::unique_ptr<Cube>(new Cube(YELLOW));
		budka3->scale(glm::vec3(0.05f, 2.0f, 0.05f));
		budka3->move(glm::vec3(0.0f, 1.0f, 0.0f));
		budka3->rotate2(glm::vec3(0.0f, 0.0f, angle));
		budka3->rotate2(glm::vec3(0.0f, 45.0f, 0.0f));
		budka3->move2(glm::vec3(dbase / 2, 0.0f, -dbase / 2));
		budka3->move2(glm::vec3(0.0f, 10.0f, 0.0f));
		budka3->rotate2(glm::vec3(0.0f, -90.0f, 0.0f));

		addObject(std::move(budka3));

		auto budka4 = std::unique_ptr<Cube>(new Cube(YELLOW));
		budka4->scale(glm::vec3(0.05f, 2.0f, 0.05f));
		budka4->move(glm::vec3(0.0f, 1.0f, 0.0f));
		budka4->rotate2(glm::vec3(0.0f, 0.0f, angle));
		budka4->rotate2(glm::vec3(0.0f, 45.0f, 0.0f));
		budka4->move2(glm::vec3(dbase / 2, 0.0f, -dbase / 2));
		budka4->move2(glm::vec3(0.0f, 10.0f, 0.0f));
		budka4->rotate2(glm::vec3(0.0f, 180.0f, 0.0f));


		addObject(std::move(budka4));


	}
};

