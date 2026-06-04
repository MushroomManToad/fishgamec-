#include <string>;
#include <array>;
#include <vector>;
#include <cmath>;
#include <algorithm>;
#include "TwoDSideDraw.h"
#include "Lake.h"

// Contains the ASCII for a wave graphic, length 4
const std::string wave = "_/)_";

void TwoDSideDraw::drawWaves(int water_height, int frame, int line_length, std::array<std::string, 30>& frame_data) {
	int step = frame % wave.length();

	std::string wave_str = wave.substr(wave.length() - step, step + 1);
	while (wave_str.length() < line_length) {
		wave_str += wave.substr(0, static_cast<int>(fmin(line_length - wave_str.length(), wave.length())));
	}

	frame_data.at(water_height) = wave_str;
}
