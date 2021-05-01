#include "package_factory.h"

namespace csci3081 {

    IEntity* PackageFactory::CreateEntity(const picojson::object& val) {
        if (JsonHelper::GetString(val, "type") == "package") {
            
            if(JsonHelper::ContainsKey(val, "weight")) {
                weight = JsonHelper::GetDouble(val, "weight");
            }
            
            std::vector<float> position = JsonHelper::GetStdFloatVector(val, "position");
	        std::vector<float> direction = JsonHelper::GetStdFloatVector(val, "direction");
            return (IEntity*) (new Package(position, direction, ((float) weight), nullptr, val));
        }
        return nullptr; 
    }

}