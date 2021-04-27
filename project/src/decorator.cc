#include "decorator.h"

namespace csci3081 {
    void Decorator::Decorate(IEntity* entity){
        for (int i = 0; i < decorations.size(); i++) {
            decorations.at(i)->Decorate(entity);
    	}
    }

    void Decorator::AddDecoration(IDecorate* decoration){
        decorations.push_back(decoration);
    }
}