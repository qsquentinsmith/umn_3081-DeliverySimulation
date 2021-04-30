#include "vector3D.h"

namespace csci3081 {

  Vector3D::Vector3D() {
    xPos = 0.0; 
    yPos = 0.0; 
    zPos = 0.0; 
  }

  Vector3D::Vector3D(std::vector<float> pos) {
    xPos = pos.at(0); 
    yPos = pos.at(1);
    zPos = pos.at(2); 
  }

  //returns current vector + input vector (right hand side)
  Vector3D Vector3D::operator+(Vector3D rhsVec) {

    float newX = this->xPos + rhsVec.GetXPos(); 
    float newY = this->yPos + rhsVec.GetYPos(); 
    float newZ = this->zPos + rhsVec.GetZPos();

    std::vector<float> newVec; 
    newVec.push_back(newX);
    newVec.push_back(newY);
    newVec.push_back(newZ);

    return Vector3D(newVec); 
  }

  //returns current vector - input vector (right hand side)
  Vector3D Vector3D::operator-(Vector3D rhsVec) {

    float newX = this->xPos - rhsVec.GetXPos(); 
    float newY = this->yPos - rhsVec.GetYPos(); 
    float newZ = this->zPos - rhsVec.GetZPos();

    std::vector<float> newVec; 
    newVec.push_back(newX);
    newVec.push_back(newY);
    newVec.push_back(newZ);

    return Vector3D(newVec); 
  }

  //returns current vector * num (multiplies vector by scalar)
  Vector3D Vector3D::operator*(float num) {

    float newX = num * this->xPos; 
    float newY = num * this->yPos; 
    float newZ = num * this->zPos;

    std::vector<float> newVec; 
    newVec.push_back(newX);
    newVec.push_back(newY);
    newVec.push_back(newZ);

    return Vector3D(newVec);
  }

  //returns the normalized version of the current vector 
  Vector3D Vector3D::Normalize() {

    float xComponent = this->xPos / this->Magnitude();
    float yComponent = this->yPos / this->Magnitude(); 
    float zComponent = this->zPos / this->Magnitude();

    std::vector<float> newVec; 
    newVec.push_back(xComponent);
    newVec.push_back(yComponent);
    newVec.push_back(zComponent);

    return Vector3D(newVec); 
  }

}