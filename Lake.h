#pragma once

#include <array>
#include <vector>
#include <string>

class Lake
{
public:
	static const int num_fish_types = 2;
	static std::array<std::vector<std::string>, num_fish_types> generate_reversed_sprites();
	static void populate_lake();
	static void step_lake(int water_level, int num_lines);
	// Struct to define a decor fish.
	struct decorFish {
	private:
		const std::vector<std::string>& left_sprite; // Lines of the fish, bottom-up
		const std::vector<std::string>& right_sprite; // Lines of the fish, bottom-up
		std::array<float, 2> head_pos; // Bottom left corner
		float speed;
		std::array<float, 2> direction;
	public:
		decorFish(
			const std::vector<std::string>& left_sprite, 
			const std::vector<std::string>& right_sprite, 
			std::array<float, 2> head_pos, 
			float speed, 
			std::array<float, 2> direction) 
			:
			left_sprite(left_sprite),
			right_sprite(right_sprite),
			head_pos(head_pos),
			speed(speed),
			direction(direction)
		{}
		// True if LEFT, false if RIGHT
		const bool get_facing() const {
			return direction.at(0) < 0.0;
		}
		const auto& get_head_pos() const {
			return head_pos;
		}
		const auto& get_lines() const {
			if (get_facing()) {
				return left_sprite;
			}
			return right_sprite;
		}
		void set_head_pos(std::array<float, 2> new_pos) {
			head_pos = new_pos;
		}
		friend class Lake;
	};
	static void bounce_fish(Lake::decorFish& df, bool is_x, int fixer);
	// Holder for active dectorative fish in the lake
	static std::vector<decorFish> decorative_fish;
};

