#include "smart_path.h"
#include <iostream>

namespace csci3081 {
  Smart::Smart(const IGraph* graph) {
    graph_ = graph; 
  } 
  
  vector<vector<float>> Smart::GetRoute(vector<float> source, vector<float> destination) {
    vector<vector<float>> route = graph_->GetPath(source, destination);
    return route; 
  }
        
} // csci3081
