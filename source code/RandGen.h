#pragma once

#include <random>

class RandGen
{
public:
	RandGen(const RandGen &other) = delete;
	RandGen &operator=(const RandGen &other) = delete;

	static RandGen &getInstance();

	std::mt19937 &getEng();
private:
	RandGen();
	~RandGen() {}

	std::mt19937 eng_;
};