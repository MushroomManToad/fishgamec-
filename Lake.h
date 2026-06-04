#pragma once

#include <array>
#include <vector>
#include <string>
#include "Sprite.h"
#include "DecorFish.h"

class Lake
{
public:
	static const int num_fish_types = 2;
	static void populate_lake();
	// Holder for active dectorative fish in the lake
	static std::vector<DecorFish> decorative_fish;
};

