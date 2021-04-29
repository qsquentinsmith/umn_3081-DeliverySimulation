#include "middle_weight.h"

namespace csci3081 {
    void MiddleWeight::Decorate(){
        if (((Package*) package_)->GetWeight() >= 2.0 && ((Package*) package_)->GetWeight() < 4.0) {
        //     ((EntityBase*)entity)->SetColor("0xF7DC6F");
        // }
        
        //details_["color"] = picojson::value("0xF7DC6F"); //yellow
            ((Package*) package_)->GetDetails()["color"] = picojson::value("0xF7DC6F");
        }
    }
}