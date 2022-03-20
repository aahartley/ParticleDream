#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Particle {
public:
	Particle(sf::Vector2f coord, float mass);
	sf::Vector2f coord;
	sf::Vector2f coord2;
	sf::CircleShape circle;
	sf::CircleShape circle2;
	sf::Vector2f velocity;
	sf::Vector2f velocity2;
	sf::Vector2f acceleration;
	float startY = coord.y;
	void calculation(float dt);
	void initialize(float dt);
	void constant(float dt);
	//sf::Vector2f rotate(sf::Vector2f& velocity, float angle);
	//void collisionDetection(float dt, std::vector<Particle*>& buffer);
	//void forces(float dt);
	//void draw(float dt);
	float getMass() { return mass; }
private:

	float mass, elasticity;
	float u = 0.7f;
	float e = 0.7f;


};
