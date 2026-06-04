#pragma once

#include <vector>
#include <memory>
#include "Sprite.h"
#include "FishUtil.h"
#include "ProcessObj.h"

// Process Object with a sprite
class SpriteObj : public ProcessObj
{
public:
	virtual ~SpriteObj() = default; // Virtual destructor necessary for polymorphism

	// Holds the object's sprites
	std::vector<Sprite> sprites; // Mutable so facing can change

	void draw(std::array<std::string, 30>& frame_data) override;

	/*
	* Constructor.DO NOT CALL DIRECTLY.
	* Instead use ProcessObjRegistry::create_sprite<T>(Args...);
	* This ensures clean registry of new objects to the sprite registry (processor)
	*/ 
	SpriteObj(std::vector<Sprite> sprites, FishUtil::Vec2 initial_pos, FishUtil::RenderLayer render_layer);

	// Override to set a sprite offset. By default, matches obj position
	virtual FishUtil::Vec2i get_sprite_position();

	// Set the position of the object
	void set_pos(FishUtil::Vec2 new_pos);

	// Sets the facing of the object and all sprites
	void set_facing(FishUtil::Facing facing);
};

