#include "FishUtil.h"
#include <string>

namespace FishUtil {
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
}