#include <cmath>
#include <iostream>

double epsilon = 0.01;

double f(double x){
	return (x + std::log10(x) - 0.5);
}

double g(double x){
	return (0.5 - std::log10(x));
}

double simple_iter(double x, double x_prev = 1){
	double res = g(x);
	if(((res - x)*(res - x) / fabs(2 * x - res - x_prev) >= epsilon || f(res) >= epsilon)){
		return simple_iter(res, x);
	}
	return res;
}

int main(){
	std::cout << simple_iter(0.1);
	return 0;
}

