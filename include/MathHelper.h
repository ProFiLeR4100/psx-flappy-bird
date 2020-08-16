#ifndef MATH_HELPER_H
#define MATH_HELPER_H

long min(long a, long b) {
	return a > b ? b : a;
}

long max(long a, long b) {
	return a > b ? a : b;
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

long clamp(long x, long from, long to) {
	long mi = min(from, to);
	long ma = max(from, to);

	if (x > ma) {
		return ma;
	} else if (x < mi) {
		return mi;
	}

	return x;
}

#endif // MATH_HELPER_H