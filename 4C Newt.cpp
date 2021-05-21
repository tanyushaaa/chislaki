#include <iostream>
#include <cmath>
#include <utility>

double epsilon = 0.01;

double f(double x){
	return (x + std::log10(x) - 0.5);
}

double f_d(double x){
	return (1 + 1 / (x * std::log(10)));
}

double f_dd(double x){
	return - 1 / (x * x * std::log(10));
}

bool check(double x){
	if (f_dd(x) * f(x) > 0){
		return true;
	} else {
		return false;
	}
}

double newtn(double x){
	if (check(x) && std::fabs(f(x)/f_d(x)) > epsilon){
		return newtn(x - f(x)/f_d(x));
	} else {
		return x - f(x)/f_d(x);
	}
}

int main(){
	std::cout << newtn(0.01); //to find this approximation was not so easy :(
	return 0;
}
