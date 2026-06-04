#pragma once

#include "SpriteObj.h"
#include "FishUtil.h"

class DecorFish : public SpriteObj
{
private:
	void set_direction(FishUtil::Vec2 new_dir);
public:
	float speed;
	FishUtil::Vec2 direction;

	void update() override;

	void bounce_fish(bool is_x, int fixer);

	static DecorFish& create_fish();

	DecorFish(std::vector<Sprite> sprites, FishUtil::Vec2 initial_facing, FishUtil::RenderLayer render_layer, FishUtil::Facing intial_facing, FishUtil::Vec2 direction, float speed);
};

