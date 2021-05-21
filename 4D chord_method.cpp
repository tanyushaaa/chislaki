#include <cmath>
#include <iostream>

double epsilon = 0.01;

double f(double x){
	return (x + std::log10(x) - 0.5);
}

double chord_m(double a, double b, double res = 0){
	if(f(a) * f(b) >= 0){
		std::cerr << "oooo noooo" << std::endl;
	}

	double c = (a * f(b) - b * f(a)) / (f(b) - f(a));
	if(std::fabs(res - c) < epsilon){
		return c;
	}

	if(f(a) * f(c) < 0){
		return chord_m(a, c, c);
	} else {
		return chord_m(c, b, c);
	}
}

int main(){
	std::cout << chord_m(0.1, 1);
}
