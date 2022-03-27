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
	void multiply(float matrix[7]);
	void add(float matrix[7], float dt);
	void fill(std::vector<Particle*> particles);
private:
	float m[1000][7]{ };
	int num = 1000;
};
