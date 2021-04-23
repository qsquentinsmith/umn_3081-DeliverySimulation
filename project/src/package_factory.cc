#include "package_factory.h"

namespace csci3081 {

    IEntity* PackageFactory::CreateEntity(const picojson::object& val) {
        if (JsonHelper::GetString(val, "type") == "package") {
            std::vector<float> position = JsonHelper::GetStdFloatVector(val, "position");
	        std::vector<float> direction = JsonHelper::GetStdFloatVector(val, "direction");
            return (IEntity*) (new Package(position, direction, 5.0, nullptr, val)); //arbitrary weight of 5.0 and nullptr for Customer*
        }
        return nullptr; 
    }

}