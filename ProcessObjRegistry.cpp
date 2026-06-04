#include "ProcessObjRegistry.h"
#include <memory>
#include <array>
#include "ProcessObj.h"
#include "FishUtil.h"

std::array<
    std::vector<std::unique_ptr<ProcessObj>>,
    static_cast<size_t>(FishUtil::RenderLayer::COUNT)
>
ProcessObjRegistry::loaded_sprites{};

void ProcessObjRegistry::register_sprite_to_loaded(std::unique_ptr<ProcessObj>&& po) {
	ProcessObjRegistry::loaded_sprites[po->render_layer].push_back(std::move(po));
}

void ProcessObjRegistry::draw_all(std::array<std::string, 30>& frame_data) {
    // Iterate through draw layers sequentially
    for (auto& layer : ProcessObjRegistry::loaded_sprites)
    {
        // Iterate through layers sequentially
        for (auto& obj : layer)
        {
            obj->draw(frame_data);
        }
    }
}

void ProcessObjRegistry::update_all() {
    // Iterate through draw layers sequentially
    for (auto& layer : ProcessObjRegistry::loaded_sprites)
    {
        // Iterate through layers sequentially
        for (auto& obj : layer)
        {
            obj->update();
        }
    }
}