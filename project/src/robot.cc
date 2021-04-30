#include "robot.h"


namespace csci3081 {

  Robot::Robot(std::vector<float> pos, std::vector<float> dir, const picojson::object& details) {
    details_ = details;
    position = pos; 
    direction = dir; 
    radius = (float) JsonHelper::GetDouble(details_, "radius");
    speed = (float) JsonHelper::GetDouble(details_, "speed");
    path = "smart";
    
    if(JsonHelper::ContainsKey(this->GetDetails(), "battery_capacity")) {
      double batteryCapacity = (float) JsonHelper::GetDouble(this->GetDetails(), "battery_capacity");
      battery_ = new Battery(batteryCapacity);
    }
    else {
      battery_ = new Battery();
    }
  }

  void Robot::SetStrategy() {
      if (strategy) {
        strategy = new Smart(graph_); 
      }
  }

  vector<vector<float>> Robot::GetRoute(vector<float> source, vector<float> destination) {
    return strategy->GetRoute(source, destination); 
  }

}