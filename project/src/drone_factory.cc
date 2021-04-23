#include "drone_factory.h"

namespace csci3081 {

    IEntity* DroneFactory::CreateEntity(const picojson::object& val) {
        if (JsonHelper::GetString(val, "type") == "drone") {
            std::vector<float> position = JsonHelper::GetStdFloatVector(val, "position");
            std::vector<float> direction = JsonHelper::GetStdFloatVector(val, "direction");
            return (IEntity*) (new Drone(position, direction, val));
        }
        return nullptr; 
    }

}