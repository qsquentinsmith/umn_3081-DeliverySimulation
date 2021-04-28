#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
//#include "vector2D.h"

#include <iostream>

namespace csci3081 {

  using entity_project::IEntity;

  class Vector2DTest : public ::testing::Test {
   protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
  };

  /*******************************************************************************
   * Test Cases
   ******************************************************************************/

  TEST_F(Vector2DTest, Vector2DConstructor) {
    
    
    Vector2D vec1 = Vector2D(); 

    std::vector<float> position;
    position.push_back(1.0);
    position.push_back(0.0);
    position.push_back(3.0);

    Vector2D vec2 = Vector2D(position);

    /***Vector2D() ***/
    ASSERT_FLOAT_EQ(vec1.GetXPos(), 0.0);
    ASSERT_FLOAT_EQ(vec1.GetYPos(), 0.0);
    ASSERT_FLOAT_EQ(vec1.GetZPos(), 0.0);

    /***Vector2D(position) ***/
    ASSERT_FLOAT_EQ(vec2.GetXPos(), 1.0);
    ASSERT_FLOAT_EQ(vec2.GetYPos(), 0.0);
    ASSERT_FLOAT_EQ(vec2.GetZPos(), 3.0);
  }

  TEST_F(Vector2DTest, ConvertTest) {
    Vector2D vec1 = Vector2D(); 

    std::vector<float> position;
    position.push_back(1.0);
    position.push_back(0.0);
    position.push_back(3.0);
    Vector2D vec2 = Vector2D(position);

    /***Convert(), GetXPos(), GetYPos(), GetZPos() ***/
    std::vector<float> convertedVec1 = vec1.Convert(); 
    std::vector<float> convertedVec2 = vec2.Convert();
    
    ASSERT_FLOAT_EQ(vec1.GetXPos(), 0.0);
    ASSERT_FLOAT_EQ(vec1.GetXPos(), convertedVec1.at(0));

    ASSERT_FLOAT_EQ(vec1.GetYPos(), 0.0);
    ASSERT_FLOAT_EQ(vec1.GetYPos(), convertedVec1.at(1));

    ASSERT_FLOAT_EQ(vec1.GetZPos(), 0.0);
    ASSERT_FLOAT_EQ(vec1.GetZPos(), convertedVec1.at(2));

    ASSERT_FLOAT_EQ(vec2.GetXPos(), 1.0);
    ASSERT_FLOAT_EQ(vec2.GetXPos(), convertedVec2.at(0));

    ASSERT_FLOAT_EQ(vec2.GetYPos(), 0.0);
    ASSERT_FLOAT_EQ(vec2.GetYPos(), convertedVec2.at(1));

    ASSERT_FLOAT_EQ(vec2.GetZPos(), 3.0);
    ASSERT_FLOAT_EQ(vec2.GetZPos(), convertedVec2.at(2));
  }

  TEST_F(Vector2DTest, AddTest) {
    Vector2D vec1 = Vector2D(); 

    std::vector<float> position1;
    position1.push_back(1.0);
    position1.push_back(0.0);
    position1.push_back(3.0);
    Vector2D vec2 = Vector2D(position1); 

    std::vector<float> position2;
    position2.push_back(3.6);
    position2.push_back(0.0);
    position2.push_back(5.8);
    Vector2D vec3 = Vector2D(position2); 

    Vector2D vec4 = vec1 + vec2; 
    Vector2D vec5 = vec2 + vec3; 
    
    ASSERT_FLOAT_EQ(vec4.GetXPos(), 1.0);
    ASSERT_FLOAT_EQ(vec4.GetYPos(), 0.0);
    ASSERT_FLOAT_EQ(vec4.GetZPos(), 3.0);
    ASSERT_FLOAT_EQ(vec5.GetXPos(), 4.6);
    ASSERT_FLOAT_EQ(vec5.GetYPos(), 0.0);
    ASSERT_FLOAT_EQ(vec5.GetZPos(), 8.8);
  }

  TEST_F(Vector2DTest, SubtractTest) {
    Vector2D vec1 = Vector2D(); 

    std::vector<float> position1;
    position1.push_back(1.0);
    position1.push_back(0.0);
    position1.push_back(3.0);
    Vector2D vec2 = Vector2D(position1); 

    std::vector<float> position2;
    position2.push_back(3.6);
    position2.push_back(0.0);
    position2.push_back(5.8);
    Vector2D vec3 = Vector2D(position2); 

    Vector2D vec4 = vec1 - vec2; 
    Vector2D vec5 = vec3 - vec2; 
    
    ASSERT_FLOAT_EQ(vec4.GetXPos(), -1.0);
    ASSERT_FLOAT_EQ(vec4.GetYPos(), 0.0);
    ASSERT_FLOAT_EQ(vec4.GetZPos(), -3.0);
    ASSERT_FLOAT_EQ(vec5.GetXPos(), 2.6);
    ASSERT_FLOAT_EQ(vec5.GetYPos(), 0.0);
    ASSERT_FLOAT_EQ(vec5.GetZPos(), 2.8);
  }

  TEST_F(Vector2DTest, ScalarMultiplyTest) {
    Vector2D vec1 = Vector2D(); 

    std::vector<float> position;
    position.push_back(2.4);
    position.push_back(0.0);
    position.push_back(1.3);
    Vector2D vec2 = Vector2D(position); 

    Vector2D vec3 = vec1 * 3.7; 
    Vector2D vec4 = vec2 * 4.1; 
    
    ASSERT_FLOAT_EQ(vec3.GetXPos(), 0.0);
    ASSERT_FLOAT_EQ(vec3.GetYPos(), 0.0);
    ASSERT_FLOAT_EQ(vec3.GetZPos(), 0.0);
    ASSERT_FLOAT_EQ(vec4.GetXPos(), 9.84);
    ASSERT_FLOAT_EQ(vec4.GetYPos(), 0.0);
    ASSERT_FLOAT_EQ(vec4.GetZPos(), 5.33);
  }

  TEST_F(Vector2DTest, MagnitudeTest) {
    Vector2D vec1 = Vector2D(); 

    std::vector<float> position;
    position.push_back(2.4);
    position.push_back(0.0);
    position.push_back(1.3);
    Vector2D vec2 = Vector2D(position); 

    float mag1 = vec1.Magnitude(); 
    float mag2 = vec2.Magnitude(); 
    
    ASSERT_FLOAT_EQ(mag1, 0.0);
    ASSERT_NEAR(mag2, 2.7295, 0.0001);
  }

  TEST_F(Vector2DTest, NormalizeTest) {
    std::vector<float> position;
    position.push_back(2.4);
    position.push_back(0.0);
    position.push_back(1.3);
    Vector2D vec1 = Vector2D(position); 

    Vector2D vec2 = vec1.Normalize(); 

    ASSERT_NEAR(vec2.GetXPos(), 0.8793, 0.0001);
    ASSERT_FLOAT_EQ(vec2.GetYPos(), 0.0);
    ASSERT_NEAR(vec2.GetZPos(), 0.4763, 0.0001);
  }

}  // namespace csci3081