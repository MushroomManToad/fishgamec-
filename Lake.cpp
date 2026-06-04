#include <array>
#include <vector>
#include <string>
#include <random>
#include <cmath>
#include <numbers>
#include "Lake.h"
#include "FishUtil.h"
#include "DecorFish.h"

using namespace std;

std::vector<DecorFish> Lake::decorative_fish;

static std::mt19937 gen(std::random_device{}());
std::uniform_int_distribution<int> num_fish(7, 10);

void Lake::populate_lake() {
	for (int i = 0; i < num_fish(gen); i++) {
		DecorFish::create_fish();
	}
}