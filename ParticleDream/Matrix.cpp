#include "Matrix.h"

void Matrix::fill(std::vector<Particle*> particles) {
	for (int i = 0; i < particles.size(); i++) {
		for (int j = 0; j < 1; j++) {
			m[i][j] = particles[i]->velocity.x;
			m[i][j + 1] = particles[i]->velocity.y;
			m[i][j + 2] = particles[i]->coord.x;
			m[i][j + 3] = particles[i]->coord.y;
			m[i][j + 4] = 1;


		}
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
void Matrix::add(float trans[5][1], float dt) {
	int acclerarion = 10;
	for (int i = 0; i <2; i++) {
		m[i][0] += trans[0][0];
		m[i][1] += trans[1][0];
		m[i][2] += trans[2][0]+m[i][0]*dt;
		m[i][3] +=trans[3][0]+m[i][1]*dt
		for (int j = 0; j < 5; j++) {
			//std::cout << "m: " << m[i][j] << " " << " trans: " << transform[j][i] << " ";
			if (j == 3) {
				trans[j][0] = ((m[i][j - 2] + m[i][j - 2]+acclerarion
				*dt) / 2) * dt; // I need this matrix to have the v' values
			}
			m[i][j] += trans[j][0];
		
		}
	}
	
	//std::cout << "\n";
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 5; j++) {
				//std::cout << m[i][j] << " \n";

		}
	}

}
void Matrix::multiply(float matrix[5][1]) {
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