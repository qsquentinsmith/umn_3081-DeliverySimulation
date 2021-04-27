#include "light_weight.h"

namespace csci3081 {
    void Light_Weight::Decorate(IEntity* entity){
        if(((Package*)entity)->GetWeight() >= 0.0 && ((Package*)entity)->GetWeight() < 2.0){
            ((EntityBase*)entity)->SetColor("0x82E0AA");
        }
        

    }
}