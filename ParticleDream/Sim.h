#pragma once
#include <SFML/Graphics.hpp>
#include <omp.h>
#include "Matrix.h"
#include "Particle.h"

class Sim {
public:
	Sim();
	~Sim() { delete window; }
	void path(Matrix& matrix,float dt, std::vector<Particle*>& buffer);
	void draw();
private:
	sf::RenderWindow* window;
};