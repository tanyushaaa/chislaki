#include <cmath>
#include <utility>
#include <vector>
#include <iostream>
#include <iomanip>

double a = 0;
double b = 10;
double x_0 = 0;
double y_0 = 0.;
int m = 0;
double epsilon = 0.01;
double h = 1;

void find_h(){
	while(pow(h, 4) >= epsilon){
		m++;
		h = fabs(b - a) / m;
	}
}

double y_(double x, double y){
	return 1 - sin(x + y) + 0.5 * y / (x + 2);
}

////////////////////–унге- утты//////////////////////////
std::vector<std::pair<double, double>> RK(int cnt = m){
	double x, y;
	double k[4];
	std::vector<std::pair<double, double>> coords;

	coords.push_back({x_0, y_0});

	for (double i = 0; i < cnt - 1; i++){
		for (int j = 0; j <= 3; j++){
			x = coords[i].first;
			y = coords[i].second;

			if (j == 3){
				x += h;
				y += k[j - 1];
			} else if (j == 1 || j == 2){
				x += 0.5 * h;
				y += 0.5 * k[j - 1];
			}

			k[j] = h * y_(x, y);
		}
		x = coords[i].first + h;
		y = coords[i].second + (k[0] + 2 * k[1] + 2 * k[2] + k[3]) / 6;//четырех-этапна€ формула –унге- утты
		coords.push_back({x, y});
	}

	for(const auto& i : coords){
		std::cout << i.first << "\t" << i.second << std::endl;
	}

	return coords;
}

//////////////////////јдамса//////////////////////////////
void Adams(){
	int order_of_accuracy = 4;
	double table[m][8];//по столбцам: 1 - х, 2 - у, 3 - d у, 4 - у', 5 - q, 6 - d q, 7 - d ^ 2 q, 8 - d^3q, строки - нижние индексы
	std::vector<std::pair<double, double>> start = RK(order_of_accuracy);

	for(int i = 0; i < m; i++){
		for(int j = 0; j < 8; j++){
			table[i][j] = 0;
		}
	}

	for (int i = 0; i < order_of_accuracy; i++){
		table[i][0] = start[i].first;
		table[i][1] = start[i].second;
		table[i][3] = y_(start[i].first, start[i].second);
		table[i][4] = h * y_(start[i].first, start[i].second);

		if(i > 0){
			table[i - 1][2] = start[i].second - start[i - 1].second;
			table[i - 1][5] = table[i][4] - table[i - 1][4];

			if (i > 1){
				table[i - 2][6] = table[i - 1][5] - table[i - 2][5];
			}

			if (i > 2){
				table[i - 3][7] = table[i - 2][6] - table[i - 3][6];
			}
		}
	}

	for(int i = order_of_accuracy; i < m; i++){
		table[i - 1][2] = table[i - 1][4] + 0.5 * table[i - 2][5] + 5 * table[i - 3][6] / 12 + 3 * table[i - 4][7] / 8;
		table[i][1] = table[i - 1][1] + table[i - 1][2];
		table[i][0] = table[i - 1][0] + h;
		table[i][3] = y_(table[i][0], table[i][1]);
		table[i][4] = table[i][3] * h;
		table[i - 1][5] = table[i][4] - table[i - 1][4];
		table[i - 2][6] = table[i - 1][5] - table[i - 2][5];
		table[i - 3][7] = table[i - 2][6] - table[i - 3][6];
	}

	for(int i = 0; i < m; i++){
		for(int j = 0; j < 8; j++){
			std::cout << std::setw(10);
			std::cout << table[i][j] << "\t";
		}
		std::cout << std::endl;
	}

}

///////////////////Ёйлера//////////////////
void Euler(){
	std::vector<std::pair<double, double>> coords;
	double x_curr = x_0, y_curr = y_0;
	coords.push_back({x_curr, y_curr});
	for(int i = 1; i < m; i++){
		y_curr += h * y_(x_curr, y_curr);
		x_curr += h;
		coords.push_back({x_curr, y_curr});
	}
	for(const auto& i : coords){
		std::cout << i.first << "\t" << i.second << std::endl;
	}
}

int main(){
	find_h();
	std::cout << h << " " << m << std::endl;
	RK();
	std::cout << std::endl;
	std::cout << std::endl;
	Adams();
	std::cout << std::endl;
	std::cout << std::endl;
	Euler();
	return 0;
}
