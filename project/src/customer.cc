#include "customer.h"

namespace csci3081 {

  Customer::Customer(std::vector<float> pos, const picojson::object& details) {
    // The following line saves the json object in the details_ member variable
    // from the EntityBase class, in order to return it later in GetDetails()
    details_ = details; 
    position = pos; 
    radius = (float) JsonHelper::GetDouble(details_, "radius");

    std::vector<float> dir; 
    dir.push_back(0.0);
    dir.push_back(0.0);
    dir.push_back(0.0);
    direction = dir; 
  }

  //returns the delivery destination 
  const std::vector<float>& Customer::GetPosition() const {
    return position; 
  }

  //returns zero vector because customer doesn't move 
  const std::vector<float>& Customer::GetDirection () const {
    return direction; 
  }
    
}