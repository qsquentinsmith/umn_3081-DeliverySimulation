#include "drone.h"

namespace csci3081 {

  Drone::Drone(std::vector<float> pos, std::vector<float> dir, const picojson::object& details) {
    details_ = details;
    position = pos; 
    direction = dir; 
    radius = (float) JsonHelper::GetDouble(details_, "radius");
    speed = (float) JsonHelper::GetDouble(details_, "speed"); 
    
    if(JsonHelper::ContainsKey(this->GetDetails(), "battery_capacity")) {
      double battery_capacity = (float) JsonHelper::GetDouble(this->GetDetails(), "battery_capacity");
      battery_ = new Battery(battery_capacity);
    }
    else {
      battery_ = new Battery();
    }

    if (JsonHelper::ContainsKey(GetDetails(), "path")) {
			  path = JsonHelper::GetString(GetDetails(), "path");
    }
  }

  void Drone::SetStrategy() {
    if (strategy) {
      if (path == "beeline") {
        strategy = new Beeline();
      }
      else if (path == "parabolic") {
        strategy = new Parabolic(); 
      }
      else {
        strategy = new Smart(graph_); 
      }
    }
}

  vector<vector<float>> Drone::GetRoute(vector<float> source, vector<float> destination) {
    return strategy->GetRoute(source, destination); 
  }

}//namespace 

