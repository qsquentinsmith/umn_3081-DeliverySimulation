#include "parabolic.h"
#include <iostream>

namespace csci3081 {


std::vector<std::vector<float>> Parabolic::GetRoute(std::vector<float> source, std::vector<float> destination){
  route.clear();
  this->source = source;
  this->destination = destination;
  CreatePath();
  return route;
}

void Parabolic::CreatePath() {
  Vector3D initialPosition = Vector3D(source);
  Vector3D finalPosition = Vector3D(destination);
  Vector3D midPosition = Vector3D(Midpoint(initialPosition, finalPosition));

  SolveEquation(initialPosition, midPosition, finalPosition);
}

std::vector<float> Parabolic::Midpoint(Vector3D initialPosition, Vector3D finalPosition){
  Vector3D difference = finalPosition - initialPosition;
  difference = difference * (0.5);
  std::vector<float> mid;
  
  mid.push_back(initialPosition.GetXPos() + difference.GetXPos());
  mid.push_back(initialPosition.GetYPos() + difference.GetYPos());
  mid.push_back(initialPosition.GetZPos() + difference.GetZPos());
  return mid;
}

void Parabolic::SolveEquation(Vector3D init, Vector3D mid, Vector3D end) {
  int routeIncrements = 41;
  Vector3D vt = (end - init) * (1.0/routeIncrements);
  for(int i = 0; i < routeIncrements; i ++){
    Vector3D nextPosition = init + (vt * i);
    float distance1 = (mid - nextPosition).Magnitude();
    float distance2 = (mid - init).Magnitude();
    float y = init.GetYPos() + (1.0 - (distance1 * distance1) / (distance2 * distance2)) * maximumHeight; //maybe needs to add initial drone position
    nextPosition.SetYPos(nextPosition.GetYPos() + y);
    float x = nextPosition.GetXPos();
    float z = nextPosition.GetZPos();
    vector<float> point;
    point.push_back(x);
    point.push_back(y);
    point.push_back(z);

    route.push_back(point);
  }

}

}