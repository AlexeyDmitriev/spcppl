/**
* ax + by = result
*/
template <typename T>
T extended_gcd (T a, T b, T& x, T& y) {
	if (a == 0) {
		x = 0;
		y = 1;
		return b;
	}
	T d = extended_gcd(b % a, a, y, x);
	x -= (b / a) * y;
	return d;
}