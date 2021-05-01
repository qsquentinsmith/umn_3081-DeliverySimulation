#include "vector2D.h"

namespace csci3081 {

  Vector2D::Vector2D() {
    xPos = 0.0; 
    yPos = 0.0; 
    zPos = 0.0; 
  }

  Vector2D::Vector2D(std::vector<float> pos) {
    xPos = pos.at(0); 
    yPos = 0.0; 
    zPos = pos.at(2); 
  }

  float Vector2D::GetXPos() {
    return xPos; 
  }

  float Vector2D::GetYPos() {
    return yPos;
  } 

  float Vector2D::GetZPos() {
    return zPos;
  }

  void Vector2D::SetYPos(float y){
    yPos = y;
  }

  //converts Vector2D/Vector3D back to vector<float>
  std::vector<float> Vector2D::Convert() {
    std::vector<float> newVec; 
    newVec.push_back(this->xPos);
    newVec.push_back(this->yPos);
    newVec.push_back(this->zPos);

    return newVec;
  }

  //returns current vector + input vector (right hand side)
  Vector2D Vector2D::operator+(Vector2D rhsVec) {

    float newX = this->xPos + rhsVec.GetXPos(); 
    float newY = this->yPos + rhsVec.GetYPos(); 
    float newZ = this->zPos + rhsVec.GetZPos();

    std::vector<float> newVec; 
    newVec.push_back(newX);
    newVec.push_back(newY);
    newVec.push_back(newZ);

    return Vector2D(newVec); 
  }

  //returns current vector - input vector (right hand side)
  Vector2D Vector2D::operator-(Vector2D rhsVec) {

    float newX = this->xPos - rhsVec.GetXPos(); 
    float newY = this->yPos - rhsVec.GetYPos(); 
    float newZ = this->zPos - rhsVec.GetZPos();

    std::vector<float> newVec; 
    newVec.push_back(newX);
    newVec.push_back(newY);
    newVec.push_back(newZ);

    return Vector2D(newVec); 
  }

  //returns current vector * num (multiplies vector by scalar)
  //does not work if num * vector 
  Vector2D Vector2D::operator*(float num) {

    float newX = num * this->xPos; 
    float newY = num * this->yPos; 
    float newZ = num * this->zPos;

    std::vector<float> newVec; 
    newVec.push_back(newX);
    newVec.push_back(newY);
    newVec.push_back(newZ);

    return Vector2D(newVec);
  }

  //returns the magnitude of the vector 
  float Vector2D::Magnitude() {

    float xComponent = powf(this->xPos, 2); 
    float yComponent = powf(this->yPos, 2);
    float zComponent = powf(this->zPos, 2);

    return sqrtf(xComponent + yComponent + zComponent); 
  }

  //returns the normalized version of the current vector 
  Vector2D Vector2D::Normalize() {

    float xComponent = this->xPos / this->Magnitude();
    float yComponent = this->yPos / this->Magnitude(); 
    float zComponent = this->zPos / this->Magnitude();

    std::vector<float> newVec; 
    newVec.push_back(xComponent);
    newVec.push_back(yComponent);
    newVec.push_back(zComponent);

    return Vector2D(newVec); 
  }

}


