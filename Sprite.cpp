#include "Sprite.h"
#include "FishUtil.h"
#include <vector>
#include <string>

// Prototype
std::vector<std::string> reverse_all_sprites(const std::vector<std::string>& source);
void injectAt(std::string& source, std::string substring, int position, int source_length);

Sprite::Sprite(const std::vector<std::string>& sprite_data, FishUtil::Facing initial_facing, FishUtil::RenderLayer render_layer) :
	sprite{sprite_data},
	flipped_sprite{ reverse_all_sprites(sprite) },
	initial_facing{initial_facing},
	render_layer{render_layer}
{
	set_facing(initial_facing);
}

void Sprite::set_facing(FishUtil::Facing dir) {
	facing = dir;
}

/*
* Helper function for reversing a sprite. Also flips the common flippable characters automatically. Used to handle objects that may face both ways
*
* @param source a string reference for the original sprite. This function will not change it.
* @param dest a string reference for the sprite to be modified. This variable should be an empty string and will be updated by this method.
*/
void reverse_sprite(const std::string& source, std::string& dest) {
	// Pre-resize it so this operation only happens once, rather than dynamically as characters are added
	dest.reserve(source.size());
	// Iterate through the string with the reverse iterator (pointer)
	for (auto it = source.rbegin(); it != source.rend(); ++it) {
		// Get the char at the pointer
		char c = *it;

		// Char swap dictionary
		switch (c) {
		case '(': c = ')'; break;
		case ')': c = '('; break;
		case '<': c = '>'; break;
		case '>': c = '<'; break;
		case '\\': c = '/'; break;
		case '/': c = '\\'; break;
		case '{': c = '}'; break;
		case '[': c = ']'; break;
		case '}': c = '{'; break;
		case ']': c = '['; break;
		default: break;
		}
		// Add the char to the string and continue to the next char until done
		dest.push_back(c);
	}
}

/*
* Helper function to reverse ALL sprites in a vector in-place
*/
std::vector<std::string> reverse_all_sprites(const std::vector<std::string>& source) {
	std::vector<std::string> out_arr;
	for (const auto& s : source) {
		// Load a string onto it corresponding to each fish_shapes string
		auto& ns = out_arr.emplace_back();
		reverse_sprite(s, ns);
	}
	return out_arr;
}


/*
* Function used to draw sprites. Inserts the sprite at its position
*/
void Sprite::draw(FishUtil::Vec2i pos, std::array<std::string, 30>& frame_data) {
	int curr_line = pos.y;
	for (const std::string& line : (facing == initial_facing ? sprite : flipped_sprite)) {
		// Failsafe for when sprite is out of window / partially out of window
		if (curr_line < frame_data.size() && curr_line >= 0) {
			injectAt(frame_data.at(curr_line), line, pos.x, FishUtil::LINE_LENGTH);
		}
		curr_line--;
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


// Helper method to get the sprite as an immutable reference
const std::vector<std::string>& Sprite::get_sprite() const {
	return sprite;
}