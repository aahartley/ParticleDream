#include "Matrix.h"
void Matrix::collision() {
	constexpr float u = 0.1f;
	constexpr float e = 0.9f;
	//#pragma omp parallel for num_threads(2)
	for (int i = 0; i < num; i++) {
		m[i][6] = 0;

		sf::Vector2f point{ m[i][2],m[i][3] };
		//obstacle  100,500 300,700   

		//std::cout << m * point.x + b << "\n";
		if (point.y >= point.x + 400 && point.y <= 750 && point.x <= 300) {
			// std::cout << "WORKING\n";
			sf::Vector2f N{ (float)std::cos(3.14 / 4),(float)-std::sin(3.14 / 4) };
			//N.x = 0;
		  // N.y = 1;
			// Vn = (V*N)N
			sf::Vector2f Vn{ (m[i][0] * N.x + m[i][1] * N.y) * N.x,    (m[i][0] * N.x + m[i][1] * N.y) * N.y };
			//Vt = V-Vn      
			sf::Vector2f Vt{ m[i][0] - Vn.x,      (m[i][1] - Vn.y) };

			//V' = (1-u)Vt-eVn    //u- friction   //e-resilience   0.0-1.0
			m[i][0] = (1 - u) * Vt.x - e * Vn.x;
			m[i][1] = (1 - u) * Vt.y - e * Vn.y;
			float S = point.y;
			//P'h = Ph - 2[(Ph-S)*N]N
			m[i][2] = m[i][2] - 2 * ((m[i][2] - point.x - 1) * N.x + m[i][3] - S + 2 * N.y) * N.x;
			m[i][3] = m[i][3] - 2 * ((m[i][3] - S + 2) * N.y + m[i][2] - point.x - 1 * N.x) * N.y;
			//P't = Pt - 2[(Pt-S)*N]N
			m[i][4] = m[i][4] - 2 * ((m[i][4] - point.x - 1) * N.x + m[i][5] - S + 2 * N.y) * N.x;
			m[i][5] = m[i][5] - 2 * ((m[i][5] - S + 2) * N.y + m[i][4] - point.x - 1 * N.x) * N.y;
			//   matrix[i][6] = 1;

		}

		//floor and top
		else if ((m[i][3] >= 700 || m[i][3] <= 198)) {
			sf::Vector2f N{ 0,1 };

			// Vn = (V*N)N
			sf::Vector2f Vn{ 0 , (m[i][1] * 1) * 1 };
			//Vt = V-Vn      
			sf::Vector2f Vt{ m[i][0] - Vn.x,(m[i][1] - Vn.y) };

			//V' = (1-u)Vt-eVn    //u- friction   //e-resilience   0.0-1.0
			m[i][0] = (1 - u) * Vt.x - e * Vn.x;
			m[i][1] = (1 - u) * Vt.y - e * Vn.y;
			float S = 0;
			if (m[i][3] <= 198)S = 198.0f;
			if (m[i][3] >= 700)S = 700;
			//P'h = Ph - 2[(Ph-S)*N]N
			m[i][2] = m[i][2] - 2 * ((m[i][2] - point.x - 1) * 1) * 1;
			m[i][3] = m[i][3] - 2 * ((m[i][3] - S) * 1) * 1;
			//P't = Pt - 2[(Pt-S)*N]N
			m[i][4] = m[i][4] - 2 * ((m[i][4] - point.x - 1) * 1) * 1;
			m[i][5] = m[i][5] - 2 * ((m[i][5] - S) * 1) * 1;
			m[i][6] = 1;

		}

		//left and right
		  if ((m[i][2] >= 698 || m[i][2] <= 101)) {
			sf::Vector2f N{ 0,1 };

			// Vn = (V*N)N
			sf::Vector2f Vn{ (m[i][0] * 1) * 1,(m[i][1] * 1) * 1 };
			//Vt = V-Vn      
			sf::Vector2f Vt{ m[i][0] - Vn.x,(m[i][1] - Vn.y) };

			//V' = (1-u)Vt-eVn    //u- friction   //e-resilience   0.0-1.0
			m[i][0] = (1 - u) * Vt.x - e * Vn.x;
			m[i][1] = (1 - u) * Vt.y - e * Vn.y;
			float S = 0;
			if (m[i][2] <= 101)S = 101.0f;
			if (m[i][2] >= 698)S = 698.0f;
			//P'h = Ph - 2[(Ph-S)*N]N
			m[i][2] = m[i][2] - 2 * ((m[i][2] - S) * 1) * 1;
			m[i][3] = m[i][3] - 2 * ((m[i][3] - S) * 1) * 1;
			//P't = Pt - 2[(Pt-S)*N]N
			m[i][4] = m[i][4] - 2 * ((m[i][4] - S) * 1) * 1;
			m[i][5] = m[i][5] - 2 * ((m[i][5] - S) * 1) * 1;
			// matrix.fill();
		}






	}
}
void Matrix::fill() {
	/*
	for (int i = 0; i < particles.size(); i++) {
		for (int j = 0; j < 1; j++) {
			m[i][j] = particles[i]->velocity.x;
			m[i][j + 1] = particles[i]->velocity.y;
			m[i][j + 2] = particles[i]->coord.x;
			m[i][j + 3] = particles[i]->coord.y;
			m[i][j + 4] = 1;


		}
	}*/
	float x = 102.0f;
	float y = 201.0f;
	#pragma omp parallel for num_threads(2)
	for (int i = 0; i < num; i++) {

		
			m[i][3] = y; //cy
			m[i][5] = y; //cy2
		
		m[i][0] = 0.0f; //vx
		m[i][1] = 0.0f; //vy
		m[i][2] = x; //cx
		m[i][4] = x; //cx2
		if (i % 10 == 0) {
						x++;

		}
		if (y > 500)
			y = 0;
		else
			y++;




	}
}

Matrix::Matrix(float x, float y, float n) {
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 1; j++) {
			m[i][j] = x;
			m[i][j + 1] = y;
			m[i][j + 2] = n;

		}
	}
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 3; j++) {
			//std::cout << m[i][j] << " ";

		}
	}
	//std::cout << '\n';
}
void Matrix::add(float trans[7], float dt) {
	#pragma omp parallel for num_threads(2)
	for (int i = 0; i <num; i++) {
		m[i][0] += trans[0];
		m[i][1] += trans[1];// vy
		//std::cout << "3 " << m[i][2] << ' ';
		m[i][4] = m[i][2];
		m[i][5] = m[i][3];
		m[i][2] += trans[2] + m[i][0] * dt; //cx
		m[i][3] += trans[3] + ((m[i][1] - trans[1] + m[i][1]) / 2) * dt; //cy
		//m[i][4] = m[i][2] - m[i][0] * dt;
		//m[i][5] = m[i][3]- ((m[i][1] - trans[1] + m[i][1]) / 2) * dt;
		//std::cout << "5 " << m[i][4] << " \n";
		//std::cout << " 2 " << m[i][1] - trans[1][0] << '\n';	
		/*	for (int j = 0; j < 5; j++) {
			//std::cout << "m: " << m[i][j] << " " << " trans: " << transform[j][i] << " ";
			if (j == 3) {
				trans[j][0] = ((m[i][j - 2] + m[i][j - 2]+acclerarion
				*dt) / 2) * dt; // I need this matrix to have the v' values
			}
			m[i][j] += trans[j][0];
		
		}*/
	}
	
	//std::cout << "\n";
	/*
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 5; j++) {
				//std::cout << m[i][j] << " \n";

		}
	}*/

}
void Matrix::multiply(float matrix[7]) {
	float transform[5][1]{ { 1},
							{1.05 },
							{1}
	};
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 5; j++) {
			//std::cout << "m: " << m[i][j] << " " << " trans: " << transform[j][i] << " ";
			m[i][j] *= transform[j][0];
		}
	}
	//std::cout << "\n";
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 5; j++) {
		//	std::cout << m[i][j] << " ";

		}
	}

}