#include "decorator.h"

namespace csci3081 {
    void Decorator::Decorate() {
        for (int i = 0; i < decorations.size(); i++) {
            decorations.at(i)->Decorate();
    	}
    }

    void Decorator::AddDecoration(PackageDecorator* decoration) {
        decorations.push_back(decoration);
    }
}