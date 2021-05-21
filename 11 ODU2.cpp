#include <vector>
#include <iostream>

double a = 1.4; //= x0
double c = 2; //= y0
double d = 4; //= z0 = y'0
double b = 2.4;

double h = 0.1;
int m = (b - a) / h;

double f(double x, double y, double z){
	return z - 2 * y / x + x + 0.4;
}

void Euler(){
	double x_curr = a;
	std::vector<double> xi;

	double y_curr = c;
	std::vector<double> yi;

	double z_curr = d;
	std::vector<double> zi;

	double y_prev;
	for (int i = 0; i < m; i++){
		xi.push_back(x_curr);
		yi.push_back(y_curr);
		zi.push_back(z_curr);

		y_prev = y_curr;
		y_curr += h * z_curr;
		z_curr += h * f(x_curr, y_prev, z_curr);
		x_curr += h;
	}

	for(int i = 0; i < m; i++){
		std::cout << xi[i] << "\t\t" << yi[i] << "\t\t" << zi[i] << std::endl;
	}
}

double k1y(double x, double y, double z){
	return z;
}

double k1z(double x, double y, double z){
	return f(x, y, z);
}

double k2y(double x, double y, double z){
	return z + h / 2 * k1z(x, y, x);
}

double k2z(double x, double y, double z){
	return f(x + h / 2, y + h / 2 * k1y(x, y, z), z + h / 2 * k1z(x, y, z));
}

double k3y(double x, double y, double z){
	return z + h / 2 * k2z(x, y, z);
}

double k3z(double x, double y, double z){
	return f(x + h / 2, y + h / 2 * k2y(x, y, z), z + h / 2 * k2z(x, y, z));
}

double k4y(double x, double y, double z){
	return z + h * k3z(x, y, z);
}

double k4z(double x, double y, double z){
	return f(x + h, y + h * k3y(x, y, z), z + h * k3z(x, y, z));
}

void RK(){
	double x_curr = a;
	std::vector<double> xi;

	double y_curr = c;
	std::vector<double> yi;

	double z_curr = d;
	std::vector<double> zi;

	double y_prev;
	for(int i = 0; i < m; i++){
		xi.push_back(x_curr);
		yi.push_back(y_curr);
		zi.push_back(z_curr);

		y_prev = y_curr;
		y_curr += h / 6 * (k1y(x_curr, y_curr, z_curr) + 2 * k2y(x_curr, y_curr, z_curr) + 2 * k3y(x_curr, y_curr, z_curr) + k4y(x_curr, y_curr, z_curr));
		z_curr += h / 6 * (k1z(x_curr, y_prev, z_curr) + 2 * k2z(x_curr, y_prev, z_curr) + 2 * k3z(x_curr, y_prev, z_curr) + k4z(x_curr, y_prev, z_curr));
		x_curr += h;
	}

	for(int i = 0; i < m; i++){
		std::cout << xi[i] << "\t\t" << yi[i] << "\t\t" << zi[i] << std::endl;
	}
}

int main(){
	Euler();
	std::cout << std::endl << std::endl;
	RK();

	return 0;
}
