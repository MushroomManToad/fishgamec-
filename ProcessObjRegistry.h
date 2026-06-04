#pragma once

#include <vector>
#include <array>
#include <set>
#include <memory>
#include "ProcessObj.h"
#include "FishUtil.h"

class ProcessObjRegistry
{
public:

	// Called by a sprite obj to register itself
	static void register_sprite_to_loaded(std::unique_ptr<ProcessObj>&& po);

	// Update and draw methods called by main
	static void update_all();
	static void draw_all(std::array<std::string, 30>& frame_data);

	// Factory for ProcessObjs
	template<typename T, typename... Args>
	static T& create(Args&&... args)
	{
		auto obj = std::make_unique<T>(std::forward<Args>(args)...);
		T& ref = *obj;
		register_sprite_to_loaded(std::move(obj));
		return ref;
	}

private:
	// Contains the list of loaded processObjs. processObjs add themselves to this array on load
	static std::array<std::vector<std::unique_ptr<ProcessObj>>, static_cast<size_t>(FishUtil::RenderLayer::COUNT)> loaded_sprites;
};

