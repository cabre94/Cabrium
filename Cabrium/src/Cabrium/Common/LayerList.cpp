#include "cbrm_pch.h"

#include "Cabrium/Common/LayerList.h"

namespace cabrium {

LayerList::LayerList() : layers(), layerInsertPos(layers.begin()) {}

LayerList::~LayerList() {
    for (auto layer : layers)
        delete layer;
}

void LayerList::pushLayer(Layer *layer) {
    // insert just before layerInsertPos
    auto it = layers.insert(layerInsertPos, layer);

    layerInsertPos = std::next(it);
}

void LayerList::pushOverlay(Layer *overlay) { layers.push_back(overlay); }

void LayerList::popLayer(Layer *layer) {
    // Search layer only on layer zone (from begin up to layerInsertPos)
    auto it = std::find(layers.begin(), layerInsertPos, layer);

    if (it != layerInsertPos) {
        layers.erase(it);
        --layerInsertPos;
    }
}

void LayerList::popOverlay(Layer *overlay) {
    // Search overlay only on overlay zone (from layerInsertPos up to the end)
    auto it = std::find(layerInsertPos, layers.end(), overlay);

    if (it != layers.end())
        layers.erase(it);
}

} // namespace cabrium
