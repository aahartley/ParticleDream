#include "Particle.h"

Particle::Particle(sf::Vector2f coord, float mass)
{
	this->coord = coord;
	this->mass = mass;
	this->velocity = sf::Vector2f{ 0,0 };
	float force = 300.0f * mass;
	this->acceleration = sf::Vector2f{ 0,force / mass };
	this->elasticity = 1.0f;
}
void Particle::constant(float dt) {
	coord.y = coord.y + 10*dt;
	circle.setPosition(coord);
}
void Particle::initialize(float dt) {
	//V=V0 + integration Adt
	velocity.y = velocity.y+ acceleration.y * dt;
	std::cout << "init v "<<velocity.y << '\n';
	//P= P0 + integration V dt
	coord.y = coord.y+ ((velocity.y + velocity.y) / 2) * dt;
	std::cout << "init coord "<<coord.y << '\n';
	circle.setPosition(coord);
}

void Particle::calculation(float dt)
{
	float v0 = 0 + 10 * dt;
	//V' = V+ A delta t
	float v = velocity.y;
	velocity.y = velocity.y + acceleration.y * dt;
	std::cout << "calc v " << velocity.y << ' ' << dt<<'\n';

	//P' = P + V+V'/2 * delta t        v0 or previous v?
	coord.y = coord.y + ((v0 + velocity.y) / 2) * dt;
	std::cout << "calc coord " << coord.y << "\n\n";
	if (coord.y >= 690 && circle.getRadius() == 5.0f) {
		//V' = V-2(V*N)N
		velocity.y = velocity.y - 2 * (velocity.y * 1) * 1;
		std::cout << "hit " << velocity.y << '\n';
		coord.y = coord.y + ((v0 + velocity.y) / 2) * dt;  //change coords again????
		//std::cout << "hit cc " << coord.y << '\n';

	}
	else if (coord.y >= 680 && circle.getRadius() == 10.0f) {
		velocity.y = velocity.y - 2 * (velocity.y * 1) * 1;
		coord.y = coord.y + ((v0 + velocity.y) / 2) * dt;

	}
	circle.setPosition(coord);

}
