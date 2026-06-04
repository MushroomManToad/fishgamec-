#pragma once

#include <string>

namespace FishUtil
{
	inline const int NUM_LINES = 30;
	inline const int LINE_LENGTH = 120;
	inline int water_height = 20;
	inline int frame_num = 0;

	struct Vec2 {
		float x, y;
	};
	struct Vec2i {
		int x, y;
	};

	// Helper ENUM for directions
	enum Facing {
		LEFT,
		RIGHT
	};
	// Helper ENUM for render layers. Layers listed first draw first.
	enum RenderLayer {
		LAKE_FISH,

		// Add render layers above this line!!
		COUNT // Always last, used to determine how many buckets are used for rendering, so DO NOT TOUCH THIS
	};
};