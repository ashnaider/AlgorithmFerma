#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

void show_result(vector<int> factors, int n, bool num_is_prime) {
	cout << n << " = ";
	for (unsigned int i = 0; i < factors.size(); i++) {
		if (i == factors.size() - 1) {
			cout << factors[i] << endl;
			break;
		}
		if (factors[i] == 1 && !num_is_prime)
			continue;
		cout << factors[i] << " * ";
	}
	cout << endl;
}

bool is_prime(int a) {
	for (int i = 2; i <= a / 2; i++) {
		if (a % i == 0)
			return false;
	}
	return true;
}

int ferma_calculate(long long n, vector<int>& factors) {

	int sqrt_n = int(sqrt(n));
	double k = 0, s, x_pow2, y_pow2, y;
	int x;

	do {
		s = sqrt_n + k;
		x_pow2 = s * s;
		y_pow2 = x_pow2 - double(n);
		y = sqrt(y_pow2);
		k++;

	} while (y != int(y));

	x = int(sqrt(x_pow2));
	int first_factor = int(x + y);
	int second_factor = x - int(y);

	if (first_factor == second_factor) {
		second_factor = ferma_calculate(second_factor, factors);
	}
	
	if (!is_prime(first_factor)) {
		first_factor = ferma_calculate(first_factor, factors);
	}
	if (!is_prime(second_factor)) {
		second_factor = ferma_calculate(second_factor, factors);
	}
 
	factors.push_back(second_factor);
	return first_factor;
}


void ferma(int n, vector<int>& result, bool& num_is_prime, bool show_info) {

	vector<int> factors;

	if (n == 0) {

		if (show_info)
			cout << "The number is zero." << endl;

		factors.push_back(0);
		result = factors;
		return;
	}

	if (n < 0) {
		n *= -1;
		factors.push_back(-1);
	}

	if (is_prime(n)) {
		if (show_info)
			cout << "The number is prime." << endl;
		factors.push_back(1);
		factors.push_back(n);
		num_is_prime = true;
		result = factors;
		return;
	}


	while (n % 2 == 0) {
		n /= 2;
		factors.push_back(2);
		if (n == 1) {
			result = factors;
			return;
		}
	}

	int x;

	x = ferma_calculate(n, factors);
	factors.push_back(x); 

	result = factors;
}

void run_ferma() {
	
	int n;
	char more = 'b';
	
	while (more != 'n') {
	
		bool num_is_prime = false;
		bool show_info = true;
		
		vector<int> result;

		cout << "Enter number: ";
		cin >> n;

		ferma(n, result, num_is_prime, show_info);

		show_result(result, n, num_is_prime);

		cout << "More?(y/n): ";
		cin >> more;
	}
}

bool test();
void run_test();

int main()
{
	run_ferma();
	// run_test();
	return 0; 
}


void run_test() {
	bool ok = test();
	if (ok) {
		cout << "Hurra!" << endl;
		cout << "All test cleared!" << endl;
	}
}

bool test() {
	int total_tests = 0;
	int tests_num = 1000;
	for (int i = -tests_num; i <= tests_num; i++) {
		bool num_is_prime = false, show_info = false;
		vector<int> factors;
		int temp_result = 1;

		if (i == 0) {
			continue;
		}

		ferma(i, factors, num_is_prime, show_info);

		for (int factor : factors) {
			temp_result *= factor;
		}
		if (i == temp_result) {
			total_tests++;
			cout << "Test " << i << ":.........." << "OK" << endl;
		}
		else {
			cout << "Test " << i << ":.........." << "WRONG" << endl;
		}
	}
	cout << total_tests << " of " << tests_num*2 << " cleared!" << endl;

	if (total_tests == tests_num*2) {
		return true;
	}
	return false;
}


