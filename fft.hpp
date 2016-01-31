#pragma once

#include <vector>
#include <cmath>
#include <complex>
#include <type_traits>

struct Double {
	Double(): value(0.0) {}

	Double(double x): value(x) {}

	operator double() {
		return value;
	}

	Double& operator+=(const Double& x) {
		value += x.value;
		return *this;
	}

	Double& operator-=(const Double& x) {
		value -= x.value;
		return *this;
	}

	Double& operator/=(const Double& x) {
		value /= x.value;
		return *this;
	}

private:
	double value;
};

bool isnan(Double d) {
	return std::isnan(static_cast<double>(d));
}

bool isinf(Double d) {
	return std::isnan(static_cast<double>(d));
}

using Base = std::complex<Double>;

double impl__cos(std::size_t n) {
	static const double PI = acos(-1.0);
	static std::vector<double> results = {-1};
	while (n >= results.size()) {
		results.push_back(std::cos(2 * PI / results.size()));
	}
	return results[n];
}

double impl__sin(std::size_t n) {
	static const double PI = acos(-1.0);
	static std::vector<double> results = {-1};
	while (n >= results.size()) {
		results.push_back(std::sin(2 * PI / results.size()));
	}
	return results[n];
}

void impl__fft(std::vector<Base>& a, bool invert) {
	std::size_t n = a.size();

	for (std::size_t i = 1, j = 0; i < n; ++i) {
		std::size_t bit = n >> 1;
		for (; j >= bit; bit >>= 1) {
			j -= bit;
		}
		j += bit;
		if (i < j) {
			swap(a[i], a[j]);
		}
	}

	for (std::size_t len = 2; len <= n; len <<= 1) {
		Base wlen(impl__cos(len), impl__sin(len) * (invert ? -1 : 1));
		for (std::size_t i = 0; i < n; i += len) {
			Base w(1);
			for (std::size_t j = 0; j < len / 2; ++j) {
				Base u = a[i + j], v = a[i + j + len / 2] * w;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				w = w * wlen;
			}
		}
	}
	if (invert) {
		for (auto& coef: a) {
			coef /= Double(n);
		}
	}
}

template <typename T, bool is_int = std::is_integral<T>::value>
T impl__convert(double arg) {
	if (is_int) {
		return static_cast<T>(arg + 0.5);
	}
	else {
		return static_cast<T>(arg);
	}
}

template <typename T>
std::vector<T> fft_multiply(const std::vector<T>& a, const std::vector<T>& b) {
	std::size_t n = 1;
	while (n <= a.size() || n <= b.size()) {
		n <<= 1;
	}
	n <<= 1;
	std::vector<Base> input[2];
	for (std::size_t w = 0; w < 2; ++w) {
		input[w].assign(n, Base(0, 0));
	}
	for (std::size_t i = 0; i < a.size(); ++i) {
		input[0][i] = a[i];
	}
	for (std::size_t i = 0; i < b.size(); ++i) {
		input[1][i] = b[i];
	}
	for (std::size_t w = 0; w < 2; ++w) {
		impl__fft(input[w], false);
	}
	std::vector<Base> res(n);
	for (std::size_t i = 0; i < n; ++i) {
		res[i] = input[0][i] * input[1][i];
	}
	impl__fft(res, true);
	std::vector<T> answer(n);
	for (std::size_t i = 0; i < n; ++i) {
		answer[i] = impl__convert<T>(res[i].real());
	}
	return answer;
}
