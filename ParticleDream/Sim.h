#pragma once
#include <SFML/Graphics.hpp>
#include <omp.h>
#include "Matrix.h"

class Sim {
public:
	Sim();
	~Sim() { delete window; }
	void path(Matrix& matrix,float dt);
	void draw();
private:
	sf::RenderWindow* window;
};