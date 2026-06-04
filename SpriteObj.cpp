#include <vector>
#include <cmath>
#include <memory>
#include "SpriteObj.h"
#include "FishUtil.h"



FishUtil::Vec2i SpriteObj::get_sprite_position() {
	return { std::lround(pos.x), std::lround(pos.y) };
}

void SpriteObj::set_pos(FishUtil::Vec2 new_pos) {
	pos = new_pos;
}

void SpriteObj::draw(std::array<std::string, 30>& frame_data) {
	// TODO: This needs to be more dynamic so that sprites can be enabled or disabled (for animation purposes)
	for (Sprite s : sprites) {
		s.draw(get_sprite_position(), frame_data);
	}
}

SpriteObj::SpriteObj(std::vector<Sprite> sprites, FishUtil::Vec2 initial_pos, FishUtil::RenderLayer render_layer) :
	ProcessObj(render_layer, initial_pos),
	sprites{ std::move(sprites) }
{
}

void SpriteObj::set_facing(FishUtil::Facing facing) {
	for (Sprite& s : sprites) {
		s.facing = facing;
	}
}