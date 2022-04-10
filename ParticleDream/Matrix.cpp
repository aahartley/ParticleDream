#include "Matrix.h"

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
//	#pragma omp parallel for num_threads(2)
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
	//#pragma omp parallel for num_threads(2)
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