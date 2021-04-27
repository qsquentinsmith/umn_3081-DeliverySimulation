#include "heavy_weight.h"

namespace csci3081 {
    void Heavy_Weight::Decorate(IEntity* entity){
        if(((Package*)entity)->GetWeight() >= 4.0){
            ((EntityBase*)entity)->SetColor("0xEC7063");
        }
        

    }
}