#include <cmath>
#include <vector>
#include <iostream>

double a = 0;
double b = 1;
double n = 2;
double h = fabs(a - b) / n;
double epsilon = 0.0001;

double f(double x){
	return sqrt(x) * cos(pow(x, 2));
}

double Simps(float s2 = 0){
	double cnt = a;
	std::vector<double> xi;

	while (cnt != b - h){
		xi.push_back(cnt + h);
		cnt += h;
	}

	double uneven = 0;
	for(int i = 0; i < n - 1; i += 2){
		uneven += f(xi[i]);
	}

	double even = 0;
	for(int i = 1; i < n - 2; i += 2){
		even += f(xi[i]);
	}

	double s1 = h * (f(a) + f(b) + 4 * uneven + 2 * even) / 3;

	n *= 2;
	h /= 2;

	if (fabs((s2 - s1) / 15) >= epsilon){
		return Simps(s1);
	}

	n = 2;
	h = fabs(a - b) / n;
	return s1;
}

double trapeze(double Ti_ = 0){
	double cnt = a;
	std::vector<double> x;

	while (cnt != b - h){
		x.push_back(cnt + h);
		cnt += h;
	}

	double Ti = 0;
	for (const auto& xi : x){// n = xi.size() - 1
		Ti += f(xi);
	}
	Ti *= 2;
	Ti += f(a) + f(b);
	Ti *= h / 2;
	n *= 2;
	h /= 2;

	if (fabs(Ti_ - Ti) >= epsilon){
		return trapeze(Ti);
	}

	n = 2;
	h = fabs(a - b) / n;
	return Ti;
}

double right_rectangle(double prev_sum = 0){
	double cnt = a;
	std::vector<double> x;

	while (cnt <= b){     //n отрезков, n + 1 точек
		x.push_back(cnt); //x.size() = n + 1
		cnt += h;
	}

	double sum = 0;
	for(int i = 0; i < n; i++){
		sum += f(x[i]) * h;
	}

	n *= 2;
	h /= 2;

	if (fabs(prev_sum - sum) >= epsilon){
		return right_rectangle(sum);
	}

	n = 2;
	h = fabs(a - b) / n;
	return sum;
}

double left_rectangle(double prev_sum = 0){
	double cnt = a;
	std::vector<double> x;

	while (cnt <= b){     //n отрезков, n + 1 точек
		x.push_back(cnt); //x.size() = n + 1
		cnt += h;
	}

	double sum = 0;
	for(int i = 1; i <= n; i++){
		sum += f(x[i]) * h;
	}

	n *= 2;
	h /= 2;

	if (fabs(prev_sum - sum) >= epsilon){
		return right_rectangle(sum);
	}

	n = 2;
	h = fabs(a - b) / n;
	return sum;
}

double rectangle(double prev_sum = 0){
	double cnt = a;
	std::vector<double> x;

	while (cnt <= b){     //n отрезков, n + 1 точек
		x.push_back(cnt); //x.size() = n + 1
		cnt += h;
	}

	double sum = 0;
	for(int i = 1; i <= n; i++){
		sum += f(x[i] - 0.5 * h) * h;
	}

	n *= 2;
	h /= 2;

	if (fabs(prev_sum - sum) >= epsilon){
		return right_rectangle(sum);
	}

	n = 2;
	h = fabs(a - b) / n;
	return sum;
}

int main(){
	std::cout << Simps() << std::endl;
	std::cout << trapeze() << std::endl;
	std::cout << right_rectangle() << std::endl;
	std::cout << left_rectangle() << std::endl;
	std::cout << rectangle() << std::endl;
	return 0;
}
