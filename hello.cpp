#include <iostream> 
#include <sstream>
#include <chrono>
#include <array>
#include "TwoDSideDraw.h"
#include "Lake.h"
using namespace std;
using namespace std::chrono;

// Util for time of previous frame to compute if a new frame should be drawn
int last_frame_ms = 0;
// Tracks the current frame number (used for animations that step per frame)
int current_frame = 0;

// Time between frames (1000 / FPS)
int ms_per_frame = 1000 / 60;

// Line Length
const int line_length = 120;
const int num_lines = 30;

// Prototype the functions so the compiler knows about it when it gets to main
static void draw_frame();
static string sanitize_frame_data(array<string, 30>& frame_data);
static void setup();

/*
	MAIN LOOP
*/ 
int main() {
	setup();
	while (true) {
		// Internally handles its own logic to tell if it's ready for a new frame to draw.
		draw_frame();
	}

	return 0;
}

// Runs only once before the first frame
static void setup() {
	Lake::populate_lake();
}

// Draws a new frame every ms_per_frame at most.
static void draw_frame() {
	// Compute current system time
	int current_ms = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
	)
		.count();

	// If enough time has passed between frames, then we do the draw
	if (current_ms - last_frame_ms > ms_per_frame) {
		// Update last frame ms.
		last_frame_ms = current_ms;
		// And frame count for functions
		current_frame += 1;

		// Create new empty frame data to be drawn to.
		std::array<string, 30> frame_data;
		frame_data.fill(std::string(120, ' ')); // populate with empty strings of length 120

		// Define rendered water height. Eventually this will depend on camera, so for now we just hardcode.
		int water_height = 20;

		/*
			MAIN LOGIC PER FRAME [PHYSICS --> DRAW]
		*/


		/*
		---------------------------------------- PHYSICS LOGIC START ----------------------------------------
		*/
		// Update fish positions etc. in the lake
		Lake::step_lake(water_height, num_lines);

		/*
		---------------------------------------- PHYSICS LOGIC START ----------------------------------------
		*/

		/*
		---------------------------------------- DRAW LOGIC START ---------------------------------------- 
		*/ 

		// TWO-D Mode
		TwoDSideDraw::drawWaves(water_height, current_frame / 4, line_length, frame_data);
		TwoDSideDraw::drawFish(Lake::decorative_fish, line_length, frame_data);

		/*
		---------------------------------------- DRAW LOGIC END ----------------------------------------
		*/


		/*
			END MAIN LOGIC
		*/
		string out_string = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" // Flush the ol' fashioned way
			+ sanitize_frame_data(frame_data); // Clean frame data before printing (and add \n to each line)
		// Output this frame
		cout << out_string;
	}
}

/*
	Returns a single string containing the entire 120x30 frame.
	We do this in a single string to prevent console flicker from multiple prints taking longer than monitor refresh rates.
	Logically, strings should be constructed without \n, so that will be added here.
	Also clamps string length to 120 char (i.e. grid width).
*/
static string sanitize_frame_data(array<string, 30>& frame_data) {
	// Create a return string containing the entire frame in a single string.
	string ret_string = "";
	for (string& s : frame_data) {
		// Clamp string length to 120
		s = s.substr(0, 120);
		// Ensures line wrapping even if the console was maximized.
		s += "\n";

		// Add to the return string
		ret_string += s;
	}
	// Drop the last newline so the whole string is used
	ret_string = ret_string.substr(0, ret_string.length() - 1);
	return ret_string;
}