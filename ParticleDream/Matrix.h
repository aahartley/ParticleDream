#pragma once
#include <cstdint>
#include <iostream>
#include <vector>
#include "Particle.h"
class Matrix {
public:
	Matrix() {};
	Matrix(float x, float y, float n);
	const float* operator [] (uint8_t i) const { return m[i]; }
	float* operator [] (uint8_t i) { return m[i]; }
	void multiply(float matrix[5][1]);
	void add(float matrix[5][1], float dt);
	void fill(std::vector<Particle*> particles);
private:
	float m[2][5]{ {100,100,1} };
};