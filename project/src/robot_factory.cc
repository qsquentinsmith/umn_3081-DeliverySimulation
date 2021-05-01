#include "robot_factory.h"

namespace csci3081 {

    IEntity* RobotFactory::CreateEntity(const picojson::object& val) {
        if (JsonHelper::GetString(val, "type") == "robot") {
            std::vector<float> position = JsonHelper::GetStdFloatVector(val, "position");
            std::vector<float> direction = JsonHelper::GetStdFloatVector(val, "direction");
            return (IEntity*) (new Robot(position, direction, val));
        }
        return nullptr; 
    }

}