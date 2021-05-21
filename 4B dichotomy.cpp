#include <iostream>
#include <cmath>
#include <utility>

double epsilon = 0.01;

double f(double x){
	return (x + std::log10(x) - 0.5);
}

bool check(std::pair<double, double> borders){
	if (f(borders.first) < 0 && f(borders.second) > 0){
		return true;
	} else {
		return false;
	}
}

std::pair<double, double> dich(std::pair<double, double> borders){
	double half = (borders.first + borders.second) / 2;
	if (check(borders) && ((borders.second - borders.first) / 2) > epsilon){
		if (f(borders.first) * f(half) < 0){
			return dich(std::make_pair(borders.first, half));
		} else if (f(half) * f(borders.second) < 0){
			return dich(std::make_pair(half, borders.second));
		}
	}
	return borders;
}

double answer(std::pair<double, double> borders){
	return (borders.first + borders.second) / 2;
}

int main(){
	std::pair<double, double> b(0, 10);
	std::cout << answer(dich(b));
	return 0;
}
