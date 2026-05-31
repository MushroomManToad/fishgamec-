#include <string>;
#include <array>;
#include <vector>;
#include <cmath>;
#include <algorithm>;
#include "TwoDSideDraw.h"
#include "Lake.h"

// Function Prototype
void injectAt(std::string& source, std::string substring, int position, int source_length);

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

void TwoDSideDraw::drawFish(std::vector<Lake::decorFish> decorative_fish, int line_length, std::array<std::string, 30>& frame_data) {
	for (const Lake::decorFish& df : decorative_fish) {
		int curr_line = df.get_head_pos().at(1);
		for (const std::string& line : df.get_lines()) {
			// Failsafe
			if (curr_line < frame_data.size() && curr_line >= 0) {
				injectAt(frame_data.at(curr_line), line, df.get_head_pos().at(0), line_length);
			}
			curr_line--;
		}
	}
}

/*
* Takes a reference to a string source (i.e.line of frame data), 
* a substring to inject(may exceed bounds), 
* a horizontal position at which the head(char[0]) of the string appears, 
* the max length to which the string should be clamped (often string.length() or line_length for frame_data),
*/ 
void injectAt(std::string& source, std::string substring, int position, int source_length) {
	int ss_len = substring.length();

	// Do nothing if the rendering starts outside the frame
	if (position > source_length) {
		return;
	}

	int start_index = std::max(0, position);
	int offset_index = std::max(0, -position); // Ensures we don't draw things off the screen to the LEFT

	// Do nothing if the substring is off the screen to the LEFT entirely
	if (offset_index >= ss_len) {
		return;
	}

	// Bounded by the source_length - start_index (i.e. 120 - [0, n]) OR the length left over after chopping off the left side
	int string_length_to_replace = std::min(source_length - start_index, ss_len - offset_index);

	for (int i = 0; i < string_length_to_replace; i++) {
		source[start_index + i] = substring[offset_index + i];
	}
}
