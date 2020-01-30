#pragma once

#include "Compound.h"

class CraneTop : public Compound {
public:

	CraneTop() {
		float thick = 0.05f;
		float height = 14.0f;
		float dbase = 0.5f; // okresla jak bardzo oddalone sa od siebie dwie pierwsze rury trzonu

		//przeciwwagi
		auto counterweight1 = std::unique_ptr<Cube>(new Cube(GREY));
		counterweight1->scale(glm::vec3(1.4f, 0.17f, 0.4f));
		counterweight1->move(glm::vec3(0.2f, 0.5f, 0.25f));

		auto counterweight2 = std::unique_ptr<Cube>(new Cube(GREY));
		counterweight2->scale(glm::vec3(1.4f, 0.17f, 0.4f));
		counterweight2->move(glm::vec3(0.2f, 0.7f, 0.25f));

		auto counterweight3 = std::unique_ptr<Cube>(new Cube(GREY));
		counterweight3->scale(glm::vec3(1.4f, 0.17f, 0.4f));
		counterweight3->move(glm::vec3(0.2f, 0.9f, 0.25f));

		addObject(std::move(counterweight1));
		addObject(std::move(counterweight2));
		addObject(std::move(counterweight3));

		// przyczep na line
		auto box = std::unique_ptr<Cube>(new Cube(YELLOW));
		box->scale(glm::vec3(0.1f, 0.5f, 0.5f));
		box->move(glm::vec3(0.0f, height/2, dbase/2));

		addObject(std::move(box));

		// lina
		auto rope = std::unique_ptr<Cube>(new Cube(GREY));
		rope->scale(glm::vec3(5.0f, 0.02f, 0.01f));
		rope->move(glm::vec3(0.0f, height / 2, dbase/2));
		rope->move(glm::vec3(-2.5f, 0.02f, 0.01f));

		addObject(std::move(rope));

		std::unique_ptr<Cube> stem[3]; // stem znaczy trzon
		std::generate(
			begin(stem),
			end(stem),
			[]() { return std::make_unique<Cube>(YELLOW); }
		);


		for (auto& x : stem) {

			x->scale(glm::vec3(thick, height, thick));
			x->move(glm::vec3(0.0f, height / 2, 0.0f));
		}

		stem[1]->move(glm::vec3(0.0f, 0.0f, dbase));
		stem[2]->move(glm::vec3(dbase * sqrt(3) / 2, 0.0f, dbase / 2));

		for (auto& x : stem) {
			addObject(std::move(x));
		}

		// poprzeczki
		const int n_bars = 14;
		std::unique_ptr<Cube> bars[n_bars][3][2];
		for (int i = 0; i < n_bars; i++) {
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 2; k++) {
					bars[i][j][k] = std::unique_ptr<Cube>(new Cube(YELLOW));
				}
			}
		}

		float bar_thick = thick * 0.5;

		for (int i = 0; i < n_bars; i++) {
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 2; k++) {
					bars[i][j][k]->scale(glm::vec3(bar_thick, dbase * sqrt(2.0f), bar_thick));
					bars[i][j][k]->move(glm::vec3(0.0f, (2.0f * i + 0.5f) * dbase, dbase / 2.0f));
					if (j == 1) {
						bars[i][j][k]->move(glm::vec3(0.0f, 0.0f, -dbase / 2.0f));
						bars[i][j][k]->rotate(glm::vec3(0.0f, 60.0f, 0.0f));
						bars[i][j][k]->move(glm::vec3(0.0f, 0.0f, dbase / 2.0f));
					}
					else if (j == 2) {
						bars[i][j][k]->move(glm::vec3(0.0f, 0.0f, dbase / 2.0f));
						bars[i][j][k]->rotate(glm::vec3(0.0f, -60.0f, 0.0f));
						bars[i][j][k]->move(glm::vec3(0.0f, 0.0f, -dbase / 2.0f));

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
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 2; k++) {
					addObject(std::move(bars[i][j][k]));
				}
			}
		}

		this->rotate2(glm::vec3(0.0f, 0.0f, 90.0f));
		this->move2(glm::vec3(8 * dbase, 10.0f, -dbase / 2));

	}

	void forward(float deltatime) {
		objects[0]->move(glm::vec3(0.0f, 0.05f, 0.0f) * deltatime);
		objects[1]->move(glm::vec3(0.0f, 0.05f, 0.0f) * deltatime);
	}
	void backwards(float deltatime) {
		objects[0]->move(glm::vec3(0.0f, -0.05f, 0.0f) * deltatime);
		objects[1]->move(glm::vec3(0.0f, -0.05f, 0.0f) * deltatime);
	}
	void down(float deltatime) {
		objects[1]->move2(glm::vec3(0.0f, -10.0f, 0.0f));
		objects[1]->scale2(glm::vec3(1.0f, 1.02f * deltatime, 1.0f));
		objects[1]->move2(glm::vec3(0.0f, 10.0f, 0.0f));

	}
	void up(float deltatime) {
		objects[1]->move2(glm::vec3(0.0f, -10.0f, 0.0f));
		objects[1]->scale2(glm::vec3(1.0f, 0.98f * deltatime, 1.0f));
		objects[1]->move2(glm::vec3(0.0f, 10.0f, 0.0f));
	}

};