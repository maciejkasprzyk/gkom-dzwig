#pragma once
#include "Object.h"
#include <vector>


class Compound : public Object
{
protected:
	std::vector<std::unique_ptr<Object>> objects;
public:

	void addObject(std::unique_ptr<Object> o) {
		objects.push_back(std::move(o));
	}

	void draw(int shaderId, Camera camera) override {
		for (auto& o : objects) {
			o->draw(shaderId, camera);
		}
	}
	
	void move(const glm::vec3& vector) override {
		for (auto& o : objects) {
			o->move(vector);
		}
	}
	void scale(const glm::vec3& vector) override {
		for (auto& o : objects) {
			o->scale(vector);
		}
	}
	void rotate(const glm::vec3& vector) override {
		for (auto& o : objects) {
			o->rotate(vector);
		}
	}

};

