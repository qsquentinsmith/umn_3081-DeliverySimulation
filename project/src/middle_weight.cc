#include "middle_weight.h"

namespace csci3081 {
    void MiddleWeight::SetDynamic(bool val){
        package_->SetDynamic(val);
        ((Package*) package_)->GetDetails()["color"] = picojson::value("0xF7DC6F");
    }
}