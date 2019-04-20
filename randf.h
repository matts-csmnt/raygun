#pragma once
#include <random>

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<> dis(0, 1);

const float randf();