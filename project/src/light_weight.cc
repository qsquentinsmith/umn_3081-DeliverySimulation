#include "light_weight.h"

namespace csci3081 {
    void LightWeight::SetDynamic(bool val) {
        package_->SetDynamic(val); 
        ((Package*) package_)->GetDetails()["color"] = picojson::value("0x82E0AA"); //green   
    }
}