#include "package.h"

namespace csci3081 {

  Package::Package(std::vector<float> pos, std::vector<float> dir, float wt, Customer* cus, const picojson::object& details) {
    details_ = details;
    position = pos; 
    direction = dir; 
    radius = (float) JsonHelper::GetDouble(details_, "radius");
    weight = wt;
    customer = cus; 
  }

  const std::vector<float>& Package::GetPosition() const {
    return position; 
  }
    
  const std::vector<float>& Package::GetDirection() const {
    return direction; 
  }

  float Package::GetWeight() {
    return weight; 
  }

  const std::vector<float>& Package::GetCustomerPosition() {
    if (customer) {
      return customer->GetPosition(); 
    }
    return position; //returns package position if customer is null
  }

  Customer* Package::GetCustomer() {
    return customer;
  }

  void Package::SetPosition(std::vector<float> pos) {
    position = pos; 
  }

  void Package::SetDirection(std::vector<float> dir) {
    direction = dir; 
  }

  void Package::SetCustomer(Customer* cus) {
    customer = cus; 
  }

  void Package::SetDynamic(bool val) {
    dynamic = val; 
  }

}