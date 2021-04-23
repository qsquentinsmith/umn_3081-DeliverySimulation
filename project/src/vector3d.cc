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

    float new_x = this->xPos + rhsVec.GetXPos(); 
    float new_y = this->yPos + rhsVec.GetYPos(); 
    float new_z = this->zPos + rhsVec.GetZPos();

    std::vector<float> new_vec; 
    new_vec.push_back(new_x);
    new_vec.push_back(new_y);
    new_vec.push_back(new_z);

    return Vector3D(new_vec); 
  }

  //returns current vector - input vector (right hand side)
  Vector3D Vector3D::operator-(Vector3D rhsVec) {

    float new_x = this->xPos - rhsVec.GetXPos(); 
    float new_y = this->yPos - rhsVec.GetYPos(); 
    float new_z = this->zPos - rhsVec.GetZPos();

    std::vector<float> new_vec; 
    new_vec.push_back(new_x);
    new_vec.push_back(new_y);
    new_vec.push_back(new_z);

    return Vector3D(new_vec); 
  }

  //returns current vector * num (multiplies vector by scalar)
  Vector3D Vector3D::operator*(float num) {

    float new_x = num * this->xPos; 
    float new_y = num * this->yPos; 
    float new_z = num * this->zPos;

    std::vector<float> new_vec; 
    new_vec.push_back(new_x);
    new_vec.push_back(new_y);
    new_vec.push_back(new_z);

    return Vector3D(new_vec);
  }

  //returns the normalized version of the current vector 
  Vector3D Vector3D::Normalize() {

    float x_component = this->xPos / this->Magnitude();
    float y_component = this->yPos / this->Magnitude(); 
    float z_component = this->zPos / this->Magnitude();

    std::vector<float> new_vec; 
    new_vec.push_back(x_component);
    new_vec.push_back(y_component);
    new_vec.push_back(z_component);

    return Vector3D(new_vec); 
  }

}