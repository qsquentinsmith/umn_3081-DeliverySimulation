#include "customer.h" //not included in header file because package.h also includes customer.h 
#include "customer_factory.h"

namespace csci3081 {

    IEntity* CustomerFactory::CreateEntity(const picojson::object& val) {
        if (JsonHelper::GetString(val, "type") == "customer") {
            std::vector<float> position = JsonHelper::GetStdFloatVector(val, "position");
            return (IEntity*) (new Customer(position, val));
        }
        return nullptr; 
    }

}