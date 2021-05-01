#include "composite_factory.h"

namespace csci3081 {

    IEntity* CompositeFactory::CreateEntity(const picojson::object& val) {
    	for (int i = 0; i < componentFactories.size(); i++) {
    		if (componentFactories.at(i)->CreateEntity(val)) {
    			return componentFactories.at(i)->CreateEntity(val);
    		}
    	}
        return nullptr;
    }

    void CompositeFactory::AddFactory(IEntityFactory* factory) {
    	componentFactories.push_back(factory);
    }

}