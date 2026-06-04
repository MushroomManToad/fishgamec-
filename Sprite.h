#pragma once

#include <string>
#include <vector>
#include <array>
#include "FishUtil.h"

// TODO: ERASE SPRITE FROM SPRITE REGISTRY ON DELETION
class Sprite
{
	// Store the sprites depending on which way the object is facing
	const std::vector<std::string>& sprite;
	const std::vector<std::string> flipped_sprite;

public:
	const FishUtil::Facing initial_facing;
	FishUtil::Facing facing;
	const FishUtil::RenderLayer render_layer;

	/*
	* Constructor
	*
	* @param sprite_data Contains the sprite, a vector of strings bottom-up
	* @param initial_facing Sets the default facing associated with the sprite_data variant of the sprite
	* @param render_layer
	*/
	Sprite(const std::vector<std::string>& sprite_data, FishUtil::Facing initial_facing, FishUtil::RenderLayer render_layer);

	// Helper function to set a direction
	void set_facing(FishUtil::Facing dir);

	// Called each frame to draw the sprite
	void draw(FishUtil::Vec2i pos, std::array<std::string, 30>& frame_data);

	const std::vector<std::string>& get_sprite() const;
};

