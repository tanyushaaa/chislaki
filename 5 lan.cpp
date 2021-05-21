#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <string>
#include <iomanip>
#include <algorithm>

//std::map<double, double> source_data {{1.415, 0.888551},
//									  {1.420, 0.889559},
//									  {1.425, 0.890637},
//									  {1.430, 0.891667},
//									  {1.435, 0.892687},
//									  {1.440, 0.893698}};

std::vector<std::pair<double, double>> source_data {{1.415, 0.888551},
													{1.420, 0.889559},
													{1.425, 0.890637},
													{1.430, 0.891667},
													{1.435, 0.892687},
													{1.440, 0.893698}};


int n = source_data.size();

double Lagr(double x_star = 1.4179){
	double sum = 0, multip = 1;
	for (const auto& i : source_data){
		for(const auto& j : source_data){
			if(i != j){
				multip *= (x_star - j.first) / (i.first - j.first);
			}
		}
		sum += multip * i.second;
		multip = 1;
	}
	return sum;
}

void foo(double num, std::vector<double>& s){ //перемножение скобок в числителе (х + х1)(х + х2)()... и тд
	int index = s.size();					  //скобки перемножаются последовательно
	s.push_back(0);							  //эл-ты вектора - коэф-ты при х - наращиваются в ходе перемножения
											  //[0] - х в степени многочлена, [стпень_многочлена] - х в нулевой
	while(index > 1){						  //num - число на кот. умножается
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

double f(double* x, int cnt){ // cnt - кол-во передаваемых в ф параметров
	if(cnt == 1){
		int i = 0;
		while(source_data[i].first != x[0]){
			i++;
		}
		return source_data[i].second;
	} else {
		return (f(&x[1], cnt - 1) - f(&x[0], cnt - 1)) / (x[cnt - 1] - x[0]);
	}
}

double Newt(double x_star = 1.4179){
	double* X = new double [n];
	int j = 0;
	for (const auto& i : source_data){
		X[j] = i.first;
		j++;
	}

	double sum = 0., multip = 1.;

	for(int i = 0; i < n; i++){
		multip *= f(X, i + 1);
		for(int j = 0; j < i; j++){
			multip *= (x_star - X[j]);
		}
		sum += multip;
		multip = 1.;
	}
	return sum;
}

std::vector<double> Newt_polinome(){
	double multip;
	int m = 0;
	std::vector<std::vector<double>> s(n);
	int size = s.size();

	double* X = new double [n];
	for (int i = 0; i < n; i++){
		X[i] = source_data[i].first;
	}

	for (int i = n - 1; i >= 0; i--){
		multip = f(X, i + 1);
		s[m].push_back(1);//koef pri max stepeni

		for(int j = 0; j < i; j++){
			foo(-source_data[j].first, s[m]); //ориентируется на размер, у меня размер имеется ввиду единица, а по факту больше - там нули
		}

		for (auto& j : s[m]){
			j *= multip;
		}
		std::reverse(s[m].begin(), s[m].end());

		for (int j = 0; j < m; j++){
			s[m].push_back(0);
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

	std::reverse(result.begin(), result.end());

	return result;
}

std::string getStringPolinome(std::vector<double>& polinome){
    std::stringstream out;
    out << std::fixed << std::setprecision(6);
    bool first = true;
    for (unsigned long int i = 0; i < polinome.size(); i++){
        if (polinome[i] != 0){
            if (!first){
                out << std::showpos;
            }
            out << std::setw(15) << polinome[i];
            if(first){
                first = false;
            }
            if (i != polinome.size() - 1){
                out << " * x";
                if (i != polinome.size() - 2){
                    out << "^" << polinome.size() - i - 1;
                }
                out << " ";
            }
        }
    }
    return out.str();
}

int main(){
	std::vector<double> aaaaa = Lagr_polinome();
	std::string res = getStringPolinome(aaaaa);
	std::cout << "L(x) = ";
	for(const auto& i : res){
		std::cout << i;
	}
	std::cout << std::endl;

	std::vector<double> aaaa = Newt_polinome();
	std::string ress = getStringPolinome(aaaa);
	std::cout << "N(x) = ";
	for(const auto& i : ress){
		std::cout << i;
	}
	std::cout << std::endl;

	std::cout << "L(1.4179) = " << Lagr() << std::endl;
	std::cout << "N(1.4179) = " << Newt() << std::endl;
	std::cout << "|L(1.4179) - N(1.4179)|" << Newt() - Lagr() << std::endl;

	return 0;
}

