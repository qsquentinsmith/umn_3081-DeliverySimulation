#include "carrier.h"

namespace csci3081 {

  const std::vector<float>& Carrier::GetPosition() const {
    return position; 
  }
    
  const std::vector<float>& Carrier::GetDirection() const {
    return direction; 
  }

  float Carrier::GetSpeed() {
    return speed; 
  }

  bool Carrier::IsScheduled() {
    return scheduled; 
  }
  
  Battery* Carrier::GetBattery(){
    return battery_;
  }

  vector<vector<float>> Carrier::GetRoute() {
    return route;
  }

  void Carrier::SetPosition(vector<float> pos) {
    position = pos; 
  }

  void Carrier::SetDirection(vector<float> dir) {
    direction = dir; 
  }

  void Carrier::SetSpeed(float sp) {
    speed = sp; 
  }

  void Carrier::SetRoute(vector<vector<float>> rt) {
    route = rt; 
  }

  void Carrier::SetScheduled(bool val) {
    scheduled = val; 
  }
    
  void Carrier::SetGraph(const IGraph* graph) {
    graph_ = graph; 
  }

  const IGraph* Carrier::GetGraph() {
    return graph_; 
  }

  bool Carrier::ReachedNextPosition(vector<float> nextPosition, float radius) {
    Vector3D carrierPos = Vector3D(position); 
    Vector3D nextPos = Vector3D(nextPosition); 

    float x_dist = abs(nextPos.GetXPos() - carrierPos.GetXPos()); 
    float y_dist = abs(nextPos.GetYPos() - carrierPos.GetYPos());
    float z_dist = abs(nextPos.GetZPos() - carrierPos.GetZPos());

    if (x_dist < radius && y_dist < radius && z_dist < radius) {
      return true;
    }
    return false; 
  }

  Vector3D Carrier::GetNewDirection(vector<float> nextPosition) {
      Vector3D origin = Vector3D(position); 
      Vector3D nextPos = Vector3D(nextPosition); 
      Vector3D newDirection = nextPos - origin; 
      newDirection = newDirection.Normalize(); 
      return newDirection; 
  }

  vector<float> Carrier::GetNewPosition(Vector3D dir, float dt) {
      Vector3D currentPosition = Vector3D(position); 
      Vector3D distanceMoved = (dir * speed) * dt; 
      Vector3D newPosition = currentPosition + distanceMoved;
      vector<float> newPositionConverted = newPosition.Convert();
      return newPositionConverted; 
  }

  bool Carrier::Move(float dt) {
    //NO ROUTE AVAILABLE 
    if (route.size() <= 1) {
      return true; 
    }

    //REACHED DESTINATION 
    if (iter == route.size() - 2 && ReachedNextPosition(route.at(iter+1), GetRadius())) { //radius parameter is temporarily 2
      iter = 0; 
      return true; 
    }

    else {
      if (ReachedNextPosition(route.at(iter+1), GetRadius())) {
        iter++; 
      }

       // see if battery is dead
      if (battery_->GetChargeRemaining() > 5.0){
        vector<float> nextPosition = route.at(iter+1); 
        Vector3D newDirection = GetNewDirection(nextPosition); 
        vector<float> newPosition = GetNewPosition(newDirection, dt); 

        SetDirection(newDirection.Convert());
        SetPosition(newPosition); 

        battery_->DrainBattery(dt);  
        
        return false; 
      }

      // lower to ground and die
      else{        
        vector<float> groundPosition;
        groundPosition.push_back(position.at(0));
        groundPosition.push_back(253.883);
        groundPosition.push_back(position.at(2));

        Vector3D newDirection = GetNewDirection(groundPosition); 
        vector<float> newPosition = GetNewPosition(newDirection, dt); 
        SetPosition(newPosition); 
        battery_->DrainBattery(dt);
        
        return false;
      }

    }

    return false; 
}

int Carrier::GetVersion() {
  return version;
}

void Carrier::SetVersion(int ver) {
  version = ver;
}

std::string Carrier::GetPath() {
  return path; 
}

}//namespace 