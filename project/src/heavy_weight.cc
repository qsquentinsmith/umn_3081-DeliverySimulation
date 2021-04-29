#include "heavy_weight.h"

namespace csci3081 {
    void HeavyWeight::Decorate(){
        if (((Package*) package_)->GetWeight() >= 4.0){
        //     ((EntityBase*)entity)->SetColor("0xEC7063");
        // }
        
        //details_["color"] = picojson::value("0xEC7063"); //red
            ((Package*) package_)->GetDetails()["color"] = picojson::value("0xEC7063");
        }
    }
}