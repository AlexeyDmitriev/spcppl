#pragma once

struct Bool {
	Bool() = default;
	
	/* implicit */ Bool(bool value): value(value) {

	}

	operator bool() const {
		return value;
	}

private:
	bool value;
};
