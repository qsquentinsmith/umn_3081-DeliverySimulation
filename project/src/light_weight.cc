#include "light_weight.h"

namespace csci3081 {
    void LightWeight::Decorate(){
        if (((Package*) package_)->GetWeight() >= 0.0 && ((Package*) package_)->GetWeight() < 2.0) {
        //     ((EntityBase*)entity)->SetColor("0x82E0AA");
        //}
            ((Package*) package_)->GetDetails()["color"] = picojson::value("0x82E0AA");
        //(Package* package_)->details_["color"] = picojson::value("0x82E0AA");
        //details_["color"] = picojson::value("0x82E0AA"); //green 
        }
    }
}