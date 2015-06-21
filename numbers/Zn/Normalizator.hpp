#pragma once

//FIXME: remove {} when CPP-1825 fixed.
template <bool normalize>
struct impl__Normalizator {

};

template <>
struct impl__Normalizator<true> {
	static void softUp(long long& value, long long mod) {
		if (value < 0) {
			value += mod;
		}
	}

	static void softDown(long long& value, long long mod) {
		if (value >= mod) {
			value -= mod;
		}
	}

	static void hardDown(long long& value, long long mod) {
		value %= mod;
	}

	static void hard(long long& value, long long mod) {
		value %= mod;
		softUp(value, mod);
	}
};

template <>
struct impl__Normalizator<false> {
	static void softUp(long long&, long long) {
	}

	static void softDown(long long&, long long) {
	}

	static void hardDown(long long&, long long) {
	}

	static void hard(long long&, long long) {
	}
};