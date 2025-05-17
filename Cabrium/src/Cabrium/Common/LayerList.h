#pragma once

#include "Layer.h"

#include <algorithm>
#include <list>

namespace cabrium {

class LayerList {
public:
    LayerList();
    ~LayerList();

    void pushLayer(Layer *layer);
    void pushOverlay(Layer *overlay);
    void popLayer(Layer *layer);
    void popOverlay(Layer *overlay);

    // iterators
    std::list<Layer *>::iterator begin() { return layers.begin(); }
    std::list<Layer *>::iterator end() { return layers.end(); }
    std::list<Layer *>::reverse_iterator rbegin() { return layers.rbegin(); }
    std::list<Layer *>::reverse_iterator rend() { return layers.rend(); }

    // const iterators
    std::list<Layer *>::const_iterator begin() const { return layers.begin(); }
    std::list<Layer *>::const_iterator end() const { return layers.end(); }
    std::reverse_iterator<std::list<Layer *>::const_iterator> rbegin() const { return layers.rbegin(); }
    std::reverse_iterator<std::list<Layer *>::const_iterator> rend() const { return layers.rend(); }

private:
    std::list<Layer *> layers;
    std::list<Layer *>::iterator layerInsertPos; // marca dónde empiezan los overlays
};

} // namespace cabrium