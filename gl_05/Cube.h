#pragma once

#include "Primitive.h"
#include <vector>

class Cube : public Primitive {

public:
	GLfloat reps;
	Cube(string textureName, GLfloat texture_repeats) : Primitive(textureName) {
		this->reps = texture_repeats * 1.0f;
		init(); }

private:
	void initVerticies() override {
		vector <GLfloat> vertices = {
			 0.5f,  0.5f,  -0.5f,		0.0f, 0.0f, 0.0f,	reps,  0.0f,	//0
			-0.5f,  0.5f,  -0.5f,		0.0f, 0.0f, 0.0f,	0.0f,  0.0f,	//1
			-0.5f, -0.5f,  -0.5f,		0.0f, 0.0f, 0.0f,	0.0f,  reps,	//2
			0.5f, -0.5f,  -0.5f,		0.0f, 0.0f, 0.0f,	reps,  reps,	//3
			-0.5f, -0.5f,  0.5f,		0.0f, 0.0f, -1.0f,	0.0f,  0.0f,	//4
			-0.5f,  0.5f,  0.5f,		0.0f, 0.0f, -1.0f,	0.0f,  reps,	//5
			0.5f,  0.5f,  0.5f,			0.0f, 0.0f, -1.0f,	reps,  reps,	//6
			0.5f, -0.5f,  0.5f,			0.0f, 0.0f, -1.0f,	reps,  0.0f,	//7
			-0.5f, -0.5f,  -0.5f,		0.0f, 1.0f, 0.0f,	0.0f,  0.0f,	//8
			-0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,	0.0f,  reps,	//9
			0.5f, -0.5f,  0.5f,			0.0f, 1.0f, 0.0f,	reps,  reps,	//10
			0.5f, -0.5f,  -0.5f,		0.0f, 1.0f, 0.0f,	reps,  0.0f,	//11
			-0.5f,  0.5f,  0.5f,		0.0f, -1.0f, 0.0f,	0.0f,  0.0f,	//12
			-0.5f,  0.5f,  -0.5f,		0.0f, -1.0f, 0.0f,	0.0f,  reps,	//13
			0.5f,  0.5f,  -0.5f,		0.0f, -1.0f, 0.0f,	reps,  reps,	//14
			0.5f,  0.5f,  0.5f,			0.0f, -1.0f, 0.0f,	reps,  0.0f,	//15
			-0.5f, -0.5f,  -0.5f,		1.0f, 0.0f, 0.0f,	0.0f,  0.0f,	//16
			-0.5f,  0.5f,  -0.5f,		1.0f, 0.0f, 0.0f,	0.0f,  reps,	//17
			-0.5f,  0.5f,  0.5f,		1.0f, 0.0f, 0.0f,	reps,  reps,	//19
			-0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 0.0f,	reps,  0.0f,	//18
			0.5f, -0.5f,  -0.5f,		-1.0f, 0.0f, 0.0f,	reps,  0.0f,	//20
			0.5f, -0.5f,  0.5f,			-1.0f, 0.0f, 0.0f,	0.0f,  0.0f,	//21
			0.5f,  0.5f,  0.5f,			-1.0f, 0.0f, 0.0f,	0.0f,  reps,	//22
			0.5f,  0.5f,  -0.5f,		-1.0f, 0.0f, 0.0f,	reps,  reps		//23
		};
		this->vertices = std::move(vertices);
	}

	void initIndicies() override {
		vector <GLuint>  indices = {
			0,1,2,
			0,2,3,
			4,5,6,
			4,6,7,
			8,9,10,
			8,10,11,
			12,13,14,
			12,14,15,
			16,17,18,
			16,18,19,
			20,21,22,
			20,22,23
		};
		this->indices = std::move(indices);
	}

};