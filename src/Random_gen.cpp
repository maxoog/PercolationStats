#include "Random_gen.h"

#include <random>

static std::mt19937 rnd(std::random_device{}());
static std::uniform_real_distribution dist;

double get_random_number()
{
    return dist(rnd);
}
