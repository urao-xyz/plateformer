#ifndef PLATEFORME_H
#define PLATEFORME_H

#include "element.h"

class Plateforme : public Element {
public:
    Plateforme() = default;
    sf::FloatRect getBounds() const {
        return sprite.getGlobalBounds();
    }
};

#endif


