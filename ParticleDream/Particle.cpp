#include "Particle.h"

Particle::Particle(sf::Vector2f coord, float mass)
{
	this->coord = coord;
	this->mass = mass;
	this->velocity = sf::Vector2f{00.0,0 };
	this->velocity2 = sf::Vector2f{ 00.0,0 };
	float force = 800.0f * mass;
	this->acceleration = sf::Vector2f{ 0,force / mass };
	this->elasticity = 1.0f;
}
void Particle::constant(float dt) {
	coord.y = coord.y + 10*dt;
	circle.setPosition(coord);
}


void Particle::calculation(float dt)
{

	//V' = V+ A delta t
	float v = velocity.y;
	float v2 = velocity2.y;
	velocity.y = velocity.y + acceleration.y * dt;
	velocity2.y = velocity2.y + acceleration.y * dt;
	velocity.x = velocity.x;
	velocity2.x = velocity2.x;

	//std::cout << "calc v " << velocity.y << ' ' << dt<<'\n';
	// 
	//P' = P + V+V'/2 * delta t        v0 or previous v?
	coord.y = coord.y + ((v + velocity.y) / 2) * dt;
	coord.x = coord.x +velocity.x* dt;

	coord2.y = coord2.y + ((v2 + velocity2.y) / 2) * dt;
	coord2.x = coord2.x + velocity2.x * dt;

	//std::cout << "calc coord " << coord.y << "\n\n";

	/*
	//V' = V-2(V*N)N collision-simple
	if (coord.y >= 690 && circle.getRadius() == 5.0f) {
		//v = velocity.y; // this vel???
		velocity.y = velocity.y - 2 * (velocity.y * 1) * 1;
	//	std::cout << "hit " << velocity.y << '\n';
		coord.y = coord.y + ((v + velocity.y) / 2) * dt;  //change coords again????
		//std::cout << "hit cc " << coord.y << '\n';

	}
	else if (coord.y >= 680 && circle.getRadius() == 10.0f) {
	//	v = velocity.y; // this vel???
		velocity.y = velocity.y - 2 * (velocity.y * 1) * 1;
		coord.y = coord.y + ((v + velocity.y) / 2) * dt;

	}
	*/
	if (coord.y >= 690 && circle.getRadius() == 5.0f) {
		
		//collision-complicated
		// Vn = (V*N)N
		sf::Vector2f Vn{ velocity.x,(velocity.y * 1) * 1 };
		//Vt = V-Vn      
		sf::Vector2f Vt{ velocity.x,(velocity.y - Vn.y) };

		//V' = (1-u)Vt-eVn    //u- friction   //e-resilience   0.0-1.0
		velocity.y = (1 - u) * Vt.y - e * Vn.y;

		//P'h = Ph - 2[(Ph-S)*N]N
		coord.y = coord.y - 2 * ((coord.y - 690.0f) * 1) * 1;
		coord2.y = coord.y - 2 * ((coord.y - 690.0f) * 1) * 1;

		//P't = Pt - 2[(Pt-S)*N]N
		//coord2.y = coord2.y - 2 * ((coord2.y - 690.0f) * 1) * 1;

		/*
		//for spheres N=Ph-C/|Ph-C|,  S = C+rN
		float N = coord.y - 685.0f / std::abs(coord.y - 685.0f);
		float S = 685.0f + 5.0f * N;
		// Vn = (V*N)N
		sf::Vector2f Vn{ velocity.x,(velocity.y * N) * N };
		//Vt = V-Vn      
		sf::Vector2f Vt{ velocity.x,(velocity.y - Vn.y) };

		//V' = (1-u)Vt-eVn    //u- friction   //e-resilience   0.0-1.0
		velocity.y = (1 - 0.5f) * Vt.y - 0.5f * Vn.y;

		//P'h = Ph - 2[(Ph-S)*N]N
		coord.y = coord.y - 2 * ((coord.y - S) * N) * N;

		//P't = Pt - 2[(Pt-S)*N]N
		*/
	}
	if (coord2.y >= 690 && circle.getRadius() == 5.0f) {
		//collision-complicated
		// Vn = (V*N)N
		sf::Vector2f Vn{ velocity2.x,(velocity2.y * 1) * 1 };
		//Vt = V-Vn      
		sf::Vector2f Vt{ velocity2.x,(velocity2.y - Vn.y) };

		//V' = (1-u)Vt-eVn    //u- friction   //e-resilience   0.0-1.0
		velocity2.y = (1 - u) * Vt.y - e * Vn.y;

		//P't = Pt - 2[(Pt-S)*N]N
		//coord2.y = coord2.y - 2 * ((coord2.y - 690.0f) * 1) * 1;
	}
	if (coord.x <= 100 || coord.x >=690 && circle.getRadius() == 5.0f) {

		//collision-complicated
		// Vn = (V*N)N
		sf::Vector2f Vn{ (velocity.x * 1) * 1,velocity.y };
		//Vt = V-Vn      
		sf::Vector2f Vt{ (velocity.y - Vn.y),velocity.y };

		//V' = (1-u)Vt-eVn    //u- friction   //e-resilience   0.0-1.0
		velocity.x = (1 - u) * Vt.x - e * Vn.x;
		float S;
		if (coord.x <= 100)
			S = 100.0f;
		else S = 690.0f;
		//P'h = Ph - 2[(Ph-S)*N]N
		coord.x = coord.x - 2 * ((coord.x - S) * 1) * 1;

		//P't = Pt - 2[(Pt-S)*N]N
		//coord2.x = coord2.x - 2 * ((coord2.x - S) * 1) * 1;
	}
	if (coord2.x <= 100 || coord2.x >= 690 && circle2.getRadius() == 5.0f) {

		//collision-complicated
		// Vn = (V*N)N
		sf::Vector2f Vn{ (velocity2.x * 1) * 1,velocity2.y };
		//Vt = V-Vn      
		sf::Vector2f Vt{ (velocity2.y - Vn.y),velocity2.y };

		//V' = (1-u)Vt-eVn    //u- friction   //e-resilience   0.0-1.0
		velocity2.x = (1 - u) * Vt.x - e * Vn.x;
		float S;
		if (coord2.x <= 100)
			S = 100.0f;
		else S = 690.0f;
		//P'h = Ph - 2[(Ph-S)*N]N
		//coord2.x = coord2.x - 2 * ((coord2.x - S) * 1) * 1;

		//P't = Pt - 2[(Pt-S)*N]N
		//coord2.x = coord2.x - 2 * ((coord2.x - S) * 1) * 1;
	}
	if (coord.y >= 680 && circle.getRadius() == 10.0f) {

		//collision-complicated
		// Vn = (V*N)N
		sf::Vector2f Vn{ velocity.x,(velocity.y * 1) * 1 };
		//Vt = V-Vn      
		sf::Vector2f Vt{ velocity.x,(velocity.y - Vn.y) };

		//V' = (1-u)Vt-eVn    //u- friction   //e-resilience   0.0-1.0
		velocity.y = (1 - u) * Vt.y - e * Vn.y;

		//P'h = Ph - 2[(Ph-S)*N]N
		coord.y = coord.y - 2 * ((coord.y - 680.0f) * 1) * 1;

		//P't = Pt - 2[(Pt-S)*N]N
		//coord2.y = coord2.y - 2 * ((coord2.y - 690.0f) * 1) * 1;

		/*
		//for spheres N=Ph-C/|Ph-C|,  S = C+rN
		float N = coord.y - 685.0f / std::abs(coord.y - 685.0f);
		float S = 685.0f + 5.0f * N;
		// Vn = (V*N)N
		sf::Vector2f Vn{ velocity.x,(velocity.y * N) * N };
		//Vt = V-Vn
		sf::Vector2f Vt{ velocity.x,(velocity.y - Vn.y) };

		//V' = (1-u)Vt-eVn    //u- friction   //e-resilience   0.0-1.0
		velocity.y = (1 - 0.5f) * Vt.y - 0.5f * Vn.y;

		//P'h = Ph - 2[(Ph-S)*N]N
		coord.y = coord.y - 2 * ((coord.y - S) * N) * N;

		//P't = Pt - 2[(Pt-S)*N]N
		*/
	}
	if (coord2.y >= 680 && circle.getRadius() == 10.0f) {
		//collision-complicated
		// Vn = (V*N)N
		sf::Vector2f Vn{ velocity2.x,(velocity2.y * 1) * 1 };
		//Vt = V-Vn      
		sf::Vector2f Vt{ velocity2.x,(velocity2.y - Vn.y) };

		//V' = (1-u)Vt-eVn    //u- friction   //e-resilience   0.0-1.0
		velocity2.y = (1 - u) * Vt.y - e * Vn.y;

		//P't = Pt - 2[(Pt-S)*N]N
		//coord2.y = coord2.y - 2 * ((coord2.y - 680.0f) * 1) * 1;
	}
	if (coord.x <= 100 || coord.x >= 680 && circle.getRadius() == 10.0f) {

		//collision-complicated
		// Vn = (V*N)N
		sf::Vector2f Vn{ (velocity.x * 1) * 1,velocity.y };
		//Vt = V-Vn      
		sf::Vector2f Vt{ (velocity.y - Vn.y),velocity.y };

		//V' = (1-u)Vt-eVn    //u- friction   //e-resilience   0.0-1.0
		velocity.x = (1 - u) * Vt.x - e * Vn.x;
		float S;
		if (coord.x <= 100)
			S = 100.0f;
		else S = 680.0f;
		//P'h = Ph - 2[(Ph-S)*N]N
		coord.x = coord.x - 2 * ((coord.x - S) * 1) * 1;

		//P't = Pt - 2[(Pt-S)*N]N
		//coord2.x = coord2.x - 2 * ((coord2.x - S) * 1) * 1;
	}
	if (coord2.x <= 100 || coord2.x >= 680 && circle2.getRadius() == 10.0f) {

		//collision-complicated
		// Vn = (V*N)N
		sf::Vector2f Vn{ (velocity2.x * 1) * 1,velocity2.y };
		//Vt = V-Vn      
		sf::Vector2f Vt{ (velocity2.y - Vn.y),velocity2.y };

		//V' = (1-u)Vt-eVn    //u- friction   //e-resilience   0.0-1.0
		velocity2.x = (1 - u) * Vt.x - e * Vn.x;
		float S;
		if (coord2.x <= 100)
			S = 100.0f;
		else S = 680.0f;
		//P'h = Ph - 2[(Ph-S)*N]N
		//coord2.x = coord2.x - 2 * ((coord2.x - S) * 1) * 1;

		//P't = Pt - 2[(Pt-S)*N]N
		//coord2.x = coord2.x - 2 * ((coord2.x - S) * 1) * 1;
	}
//	std::cout << "calc y " << coord.y <<'\n';

	circle.setPosition(coord);
	circle2.setPosition(coord2);

}
