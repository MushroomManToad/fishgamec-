#include "DecorFish.h"
#include <random>
#include <cmath>
#include <numbers>
#include <vector>
#include "Lake.h"
#include "FishUtil.h"
#include "Sprite.h"
#include "ProcessObjRegistry.h"

// Contains fish shape definitions, bottom-up.
static const std::array<std::vector<std::string>, 2> fish_shapes = {
	std::vector<std::string>{"<._>_\\", " ____/"},
	std::vector<std::string>{"(:===<"}
};

// Init device and distributions only once
static std::mt19937 gen(std::random_device{}());
std::uniform_int_distribution<int> fish_id_rand(0, fish_shapes.size() - 1);
std::uniform_real_distribution<float> fish_x_rand(0.0f, 119.0f);
std::uniform_real_distribution<float> speeds(0.05f, 0.12f);
std::uniform_real_distribution<float> directions(0.0f, 2.0f * std::numbers::pi);
std::uniform_real_distribution<float> unif(0.0f, 1.0f);

void DecorFish::update() {
	FishUtil::Vec2 new_pos = FishUtil::Vec2{ pos.x + speed * direction.x, pos.y + speed * direction.y };
	// Bounds checking!
	// fish_height is the height of the sprite, used to keep the fish under the water
	int fish_height = sprites.at(0).get_sprite().size();

	// Left check
	if (new_pos.x <= -4) {
		new_pos.x = -4;
		bounce_fish(true, 1);
	}
	// Right check
	else if (new_pos.x >= 124) {
		new_pos.x = 124;
		bounce_fish(true, -1);
	}

	// DO Y SECOND CAUSE IT LOOKS WORSE WHEN IT FAILS
	// Top check
	if (new_pos.y - fish_height <= FishUtil::water_height) {
		new_pos.y = FishUtil::water_height + fish_height;
		bounce_fish(false, 1);
	}
	// Bottom check
	// TODO: Should depend on lake bottom, not num lines
	else if (new_pos.y >= FishUtil::NUM_LINES - 1) {
		new_pos.y = FishUtil::NUM_LINES - 1.000001;
		bounce_fish(false, -1);
	}
	set_pos(new_pos);
}

// Helper method to handle fish bounce
void DecorFish::bounce_fish(bool is_x, int fixer) {
	// 75% chance to keep horizontal direction and just reverse motion, 25% to flip horizontal sign and randomize direction & speed
	if (unif(gen) <= 0.75) {
		// Flip x dir if x collision
		if (is_x) {
			set_direction(FishUtil::Vec2(-direction.x, direction.y));
		}
		// Flip y direction if y collision
		else {
			set_direction(FishUtil::Vec2(direction.x, -direction.y));
		}
	}
	else {
		// Gen new speed and direction
		speed = speeds(gen);
		float dir_angle = directions(gen);
		// Swap x direction and keep randomized y
		if (is_x) {
			set_direction(FishUtil::Vec2(fixer * std::abs(std::sin(dir_angle)), std::cos(dir_angle)));
		}
		// Swap y direction and keep randomized x
		else {
			set_direction(FishUtil::Vec2{ std::sin(dir_angle) , fixer * std::abs(std::cos(dir_angle)) });
		}
	}
}

void DecorFish::set_direction(FishUtil::Vec2 new_dir) {
	direction = new_dir;

	if (direction.x < 0) {
		set_facing(FishUtil::Facing::LEFT);
	}
	else {
		set_facing(FishUtil::Facing::RIGHT);
	}
}

DecorFish::DecorFish(std::vector<Sprite> sprites, FishUtil::Vec2 initial_pos, FishUtil::RenderLayer render_layer, 
	FishUtil::Facing initial_facing, FishUtil::Vec2 direction, float speed) :
	SpriteObj(sprites, initial_pos, render_layer),
	speed{speed}
{
	set_direction(direction);
}

DecorFish& DecorFish::create_fish() {
	{
		// Choose fish shape
		int fish_id = fish_id_rand(gen);

		// Get this fish shape
		auto& base_shape = fish_shapes[fish_id];

		float dir_angle = directions(gen);

		FishUtil::Vec2 dir = FishUtil::Vec2{sin(dir_angle), cos(dir_angle)};

		Sprite s = Sprite(base_shape, FishUtil::Facing::LEFT, FishUtil::RenderLayer::LAKE_FISH);

		DecorFish& new_fish = ProcessObjRegistry::create<DecorFish>(std::vector<Sprite>{std::move(s)}, FishUtil::Vec2{fish_x_rand(gen), 25}, FishUtil::RenderLayer::LAKE_FISH,
			(dir.x < 0 ? FishUtil::Facing::LEFT : FishUtil::Facing::RIGHT), std::move(dir), speeds(gen));

		return new_fish;
	}
}