#pragma once
#include "FishUtil.h"

class ProcessObj
{
public:
	// Current position of the ProcessObj
	FishUtil::Vec2 pos;

	// Called each frame before draw()
	virtual void update() = 0;

	// Called each frame after update()
	virtual void draw(std::array<std::string, 30>& frame_data) = 0;

	const FishUtil::RenderLayer render_layer;

	ProcessObj(FishUtil::RenderLayer layer, FishUtil::Vec2 pos):
		render_layer{ layer },
		pos{pos}
	{
	}

	virtual ~ProcessObj() = default;
};

