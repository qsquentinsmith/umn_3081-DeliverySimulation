#include "heavy_weight.h"

namespace csci3081 {
    void HeavyWeight::SetDynamic(bool val){
        package_->SetDynamic(val); 
        ((Package*) package_)->GetDetails()["color"] = picojson::value("0xEC7063"); //red
    }
}