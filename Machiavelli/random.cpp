#include "pch.h"
#include "random.h"
#include <cassert>
#include <random>

std::default_random_engine &random_engine() {
	static std::random_device rd{};
	static std::default_random_engine re{ rd() };
	return re;
}

int random_int(const int low, const int high)
{
	assert(high > low);
	std::uniform_int_distribution<int> d{ low, high };
	return d(random_engine());
}
