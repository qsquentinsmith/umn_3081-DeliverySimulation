#include "middle_weight.h"

namespace csci3081 {
    void Middle_Weight::Decorate(IEntity* entity){
        if(((Package*)entity)->GetWeight() >= 2.0 && ((Package*)entity)->GetWeight() < 4.0){
            ((EntityBase*)entity)->SetColor("0xF7DC6F");
        }
        

    }
}