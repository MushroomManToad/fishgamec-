#pragma once

#include <array>
#include <vector>
#include <string>
#include "Lake.h"

class TwoDSideDraw
{
public:
	static void drawWaves(int water_height, int frame, int line_length, std::array<std::string, 30>& frame_data);
};

