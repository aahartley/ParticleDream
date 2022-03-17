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
void Matrix::add(float matrix[5][1], float dt) {
	float v0 = 0 + 10 * dt;

	float transform[5][1]{ { 0},
							{1.05 },
							{0},
							{1},
							{1}
	};

	for (int i = 0; i <2; i++) {
		for (int j = 0; j < 5; j++) {
			//std::cout << "m: " << m[i][j] << " " << " trans: " << transform[j][i] << " ";
			if (j == 3) {
				matrix[j][0] = ((v0 + m[i][j - 2]) / 2) * dt;
			}
			m[i][j] += matrix[j][0];
		
		}
	}
	for (int i = 0; i < 2; i++) {

		if (m[i][3] >= 690) {
			m[i][1] = m[i][1] - 2 * (m[i][1] * 1) * 1;
			m[i][3] += ((v0 + m[i][1]) / 2) * dt;
		}
	}
	std::cout << "\n";
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 5; j++) {
				std::cout << m[i][j] << " \n";

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