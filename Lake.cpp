#include <array>
#include <vector>
#include <string>
#include <random>
#include <cmath>
#include <numbers>
#include "Lake.h"
#include "FishUtil.h"

using namespace std;

std::vector<Lake::decorFish> Lake::decorative_fish;

// Contains fish shape definitions, bottom-up.
static const std::array<std::vector<std::string>, Lake::num_fish_types> fish_shapes = {
	std::vector<std::string>{"<._>_\\", " ____/"},
	std::vector<std::string>{"(:===<"}
};

// Generated dynamically at load_time (before first frame) based on above frame data processed to be flipped
static const std::array<std::vector<std::string>, Lake::num_fish_types> reverse_fish_shapes = Lake::generate_reversed_sprites();

// Init device and distributions only once
static std::mt19937 gen(std::random_device{}());
std::uniform_int_distribution<int> num_fish(7, 10);
std::uniform_int_distribution<int> fish_id_rand(0, fish_shapes.size() - 1);
std::uniform_real_distribution<float> fish_x_rand(0.0f, 119.0f);
std::uniform_real_distribution<float> speeds(0.05f, 0.12f);
std::uniform_real_distribution<float> directions(0.0f, 2.0f * std::numbers::pi);
std::uniform_real_distribution<float> unif(0.0f, 1.0f);

void Lake::populate_lake() {
	// Generate a random number of fish to place into the lake
	int range_max = num_fish(gen);

	for (int i = 0; i < range_max; i++) {
		// Choose fish shape
		int fish_id = fish_id_rand(gen);

		// Get this fish shape
		const auto& left_shape = fish_shapes[fish_id];
		const auto& right_shape = reverse_fish_shapes[fish_id];

		float dir_angle = directions(gen);

		// Store to active fish
		// Use emplace to avoid creating then moving or copying operations (expensive with larger structures for later in dev)
		Lake::decorative_fish.emplace_back(
			left_shape,
			right_shape,
			array<float, 2>{fish_x_rand(gen), 25.0f},
			speeds(gen),
			array<float, 2>{std::sin(dir_angle), std::cos(dir_angle)}
		);
	}
}

// Called each frame before draw
void Lake::step_lake(int water_level, int num_lines = 30) {
	for (Lake::decorFish& df : decorative_fish) {
		std::array<float, 2> new_pos = std::array<float, 2>{df.head_pos.at(0) + df.speed * df.direction.at(0), df.head_pos.at(1) + df.speed * df.direction.at(1)};
		// Bounds checking!
		// fish_height is the height of the sprite, used to keep the fish under the water
		int fish_height = df.get_lines().size();

		// Left check
		if (new_pos[0] <= -4) {
			new_pos[0] = -4;
			bounce_fish(df, true, 1);
		}
		// Right check
		else if (new_pos[0] >= 124) {
			new_pos[0] = 124;
			bounce_fish(df, true, -1);
		}

		// DO Y SECOND CAUSE IT LOOKS WORSE WHEN IT FAILS
		// Top check
		if (new_pos[1] - fish_height <= water_level) {
			new_pos[1] = water_level + fish_height;
			bounce_fish(df, false, 1);
		}
		// Bottom check
		else if(new_pos[1] >= num_lines - 1) {
			new_pos[1] = num_lines - 1.000001;
			bounce_fish(df, false, -1);
		}
		df.set_head_pos(new_pos);
	}
}

// Helper method to handle fish bounce
void Lake::bounce_fish(Lake::decorFish& df, bool is_x, int fixer) {
	// 75% chance to keep horizontal direction and just reverse motion, 25% to flip horizontal sign and randomize direction & speed
	if (unif(gen) <= 0.75) {
		// Flip x dir if x collision
		if (is_x) {
			df.direction[0] = -df.direction[0];
		}
		// Flip y direction if y collision
		else {
			df.direction[1] = -df.direction[1];
		}
	}
	else {
		// Gen new speed and direction
		df.speed = speeds(gen);
		float dir_angle = directions(gen);
		// Swap x direction and keep randomized y
		if (is_x) {
			df.direction[0] = fixer * std::abs(std::sin(dir_angle));
			df.direction[1] = std::cos(dir_angle);
		}
		// Swap y direction and keep randomized x
		else {
			df.direction[0] = std::sin(dir_angle);
			df.direction[1] = fixer * std::abs(std::cos(dir_angle));
		}
	}
}

std::array<std::vector<std::string>, Lake::num_fish_types> Lake::generate_reversed_sprites() {
	// Create a new array
	std::array<std::vector<std::string>, num_fish_types> out_arr;
	for (int i = 0; i < fish_shapes.size(); i++) {
		for (const auto& s : fish_shapes[i]) {
			// Load a string onto it corresponding to each fish_shapes string
			auto& ns = out_arr[i].emplace_back();
			FishUtil::reverse_sprite(s, ns);
		}
	}
	// Return resulting array to be stored to the static reversed_fish_shapes array
	return out_arr;
}