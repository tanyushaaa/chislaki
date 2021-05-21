#include <iostream>
#include <map>
#include <cmath>
#include <vector>
#include <utility>
/*
std::map<double, double> source_data {{1.415, 0.888551},
									  {1.420, 0.889559},
									  {1.425, 0.890637},
									  {1.430, 0.891667},
									  {1.435, 0.892687},
									  {1.440, 0.893698}};
*/
std::vector<std::pair<double, double>> source_data {{1.415, 0.888551},
													{1.420, 0.889559},
													{1.425, 0.890637},
													{1.430, 0.891667},
													{1.435, 0.892687},
													{1.440, 0.893698}};

int n = source_data.size();

double h = source_data[2].first - source_data[1].first;

void foo(double num, std::vector<double>& s){ //перемножение скобок в числителе (х - х1)(х - х2)()... и тд
	int index = s.size();					  //скобки перемножаются последовательно
	s.push_back(0);							  //эл-ты вектора - коэф-ты при х - наращиваются в ходе перемножения
											  //[0] - х в степени многочлена, [стпень_многочлена] - х в нулевой
	while(index > 1){
		s[index] += s[index - 1] * num;
		index--;
	}

	s[index] += num;
}

std::vector<double> Lagr_polinome(){
	double multip;
	int m = 0;
	std::vector<std::vector<double>> s;

	for (const auto& i : source_data){
		multip = i.second;
		s.push_back({1});

		for(const auto& j : source_data){
			if(i != j){
				multip /= (i.first - j.first);
				foo(-j.first, s[m]);
			}
		}

		for (auto& j : s[m]){
			j *= multip;
		}

		m++;
	}

	std::vector<double> result;
	for(int i = 0; i < m; i++){
		result.push_back(0);
		for(int j = 0; j < m; j++){
			result[i] += s[j][i];
		}
	}

	return result;
}

double diff_star(std::vector<double>& polinome, double x_star = 1.4179){ //вектор содержащий все коэффициенты при х в степенях, включая нули
	double res = 0;														//размер вектора - (наибольшая степень х) + 1
	int max_degree = polinome.size() - 1;								// первый элеменет - коэф при х в наиб степени
	for(int i = 0; i < polinome.size() - 1; i--){						//последний элемент poliоnme - число, производная = 0
		res += max_degree * polinome[i] * x_star;
		max_degree--;
	}

	return res;
}

double second_diff_star(std::vector<double>& polinome, double x_star = 1.4179){ //вектор содержащий все коэффициенты при х в степенях, включая нули
	double res = 0;														//размер вектора - (наибольшая степень х) + 1
	int max_degree = polinome.size() - 1;								// первый элеменет - коэф при х в наиб степени
	for(int i = 0; i < polinome.size() - 2; i--){						//последний элемент poliоnme - число, производная = 0
		res += max_degree * (max_degree - 1) * polinome[i] * x_star;
		max_degree--;
	}

	return res;
}

double diff_i(int index = 2){
	return (source_data[index - 2].second - source_data[index].second) / (2 * h);
}

double second_diff_i(int index = 2){
	return (source_data[index - 2].second - 2 * source_data[index - 1].second + source_data[index].second) / (h * h);
}

int main(){
	std::vector<double> polinome = Lagr_polinome();
	std::cout << diff_star(polinome) << std::endl;
	std::cout << second_diff_star(polinome) << std::endl;

	std::cout << diff_i() << std::endl;
	std::cout << second_diff_i() << std::endl;

	return 0;
}
