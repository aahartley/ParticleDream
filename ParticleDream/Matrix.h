#pragma once
#include <cstdint>
#include <iostream>
#include <vector>
#include "Particle.h"
#include <omp.h>
class Matrix {
public:
	Matrix() {};
	Matrix(float x, float y, float n);
	const float* operator [] (uint8_t i) const { return m[i]; }
	float* operator [] (uint8_t i) { return m[i]; }
	void multiply(float matrix[7]);
	void add(float matrix[7], float dt);
	void fill();
	void collision();
	int num = 1000;
private:
	float m[1000][7]{ };
};
