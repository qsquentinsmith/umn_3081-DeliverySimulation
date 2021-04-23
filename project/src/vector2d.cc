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

  //converts Vector2D/Vector3D back to vector<float>
  std::vector<float> Vector2D::Convert() {
    std::vector<float> new_vec; 
    new_vec.push_back(this->xPos);
    new_vec.push_back(this->yPos);
    new_vec.push_back(this->zPos);

    return new_vec;
  }

  //returns current vector + input vector (right hand side)
  Vector2D Vector2D::operator+(Vector2D rhsVec) {

    float new_x = this->xPos + rhsVec.GetXPos(); 
    float new_y = this->yPos + rhsVec.GetYPos(); 
    float new_z = this->zPos + rhsVec.GetZPos();

    std::vector<float> new_vec; 
    new_vec.push_back(new_x);
    new_vec.push_back(new_y);
    new_vec.push_back(new_z);

    return Vector2D(new_vec); 
  }

  //returns current vector - input vector (right hand side)
  Vector2D Vector2D::operator-(Vector2D rhsVec) {

    float new_x = this->xPos - rhsVec.GetXPos(); 
    float new_y = this->yPos - rhsVec.GetYPos(); 
    float new_z = this->zPos - rhsVec.GetZPos();

    std::vector<float> new_vec; 
    new_vec.push_back(new_x);
    new_vec.push_back(new_y);
    new_vec.push_back(new_z);

    return Vector2D(new_vec); 
  }

  //returns current vector * num (multiplies vector by scalar)
  //does not work if num * vector 
  Vector2D Vector2D::operator*(float num) {

    float new_x = num * this->xPos; 
    float new_y = num * this->yPos; 
    float new_z = num * this->zPos;

    std::vector<float> new_vec; 
    new_vec.push_back(new_x);
    new_vec.push_back(new_y);
    new_vec.push_back(new_z);

    return Vector2D(new_vec);
  }

  //returns the magnitude of the vector 
  float Vector2D::Magnitude() {

    float x_component = powf(this->xPos, 2); 
    float y_component = powf(this->yPos, 2);
    float z_component = powf(this->zPos, 2);

    return sqrtf(x_component + y_component + z_component); 
  }

  //returns the normalized version of the current vector 
  Vector2D Vector2D::Normalize() {

    float x_component = this->xPos / this->Magnitude();
    float y_component = this->yPos / this->Magnitude(); 
    float z_component = this->zPos / this->Magnitude();

    std::vector<float> new_vec; 
    new_vec.push_back(x_component);
    new_vec.push_back(y_component);
    new_vec.push_back(z_component);

    return Vector2D(new_vec); 
  }

}


