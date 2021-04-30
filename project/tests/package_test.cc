#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "package.h"
#include <iostream>

namespace csci3081 {

  using entity_project::IEntity;

  class PackageTest : public ::testing::Test {
   protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
  };

  /*******************************************************************************
   * Test Cases
   ******************************************************************************/
  //testing package constructor
  TEST_F(PackageTest, PackageConstructor) {
    //setting up package
    picojson::object obj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj, "type", "package");
    std::vector<float> positionToAdd;
    positionToAdd.push_back(498.292);
    positionToAdd.push_back(253.883);
    positionToAdd.push_back(-228.623);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", positionToAdd);
    std::vector<float> directionToAdd;
    directionToAdd.push_back(1);
    directionToAdd.push_back(0);
    directionToAdd.push_back(0);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", directionToAdd);
    JsonHelper::AddFloatToJsonObject(obj, "radius", 1.0);

    Customer* customer = nullptr; 
    float weight = 5.0; 

    Package package = Package(positionToAdd, directionToAdd, weight, customer, obj); 

    //testing position, direction, and weight set in constructor
    ASSERT_FLOAT_EQ(package.GetPosition()[0], 498.292);
    ASSERT_FLOAT_EQ(package.GetPosition()[1], 253.883);
    ASSERT_FLOAT_EQ(package.GetPosition()[2], -228.623);
    ASSERT_FLOAT_EQ(package.GetDirection()[0], 1.0);
    ASSERT_FLOAT_EQ(package.GetDirection()[1], 0.0);
    ASSERT_FLOAT_EQ(package.GetDirection()[2], 0.0);
    ASSERT_FLOAT_EQ(package.GetWeight(), 5.0); 

    // Checks that when GetDetails() is called, the entity returns 
    //  the picojson object that was used to initialize it
    ASSERT_EQ(picojson::value(package.GetDetails()).serialize(), picojson::value(obj).serialize());
  }

  TEST_F(PackageTest, GetCustomerPositionTest) {
    picojson::object obj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj, "type", "package");
    std::vector<float> positionToAdd;
    positionToAdd.push_back(498.292);
    positionToAdd.push_back(253.883);
    positionToAdd.push_back(-228.623);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", positionToAdd);
    std::vector<float> directionToAdd;
    directionToAdd.push_back(1);
    directionToAdd.push_back(0);
    directionToAdd.push_back(0);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", directionToAdd);
    JsonHelper::AddFloatToJsonObject(obj, "radius", 2.0);

    picojson::object cusObj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(cusObj, "type", "customer");
    std::vector<float> cusPositionToAdd;
    cusPositionToAdd.push_back(46.78);
    cusPositionToAdd.push_back(53.159);
    cusPositionToAdd.push_back(-384.23);
    JsonHelper::AddStdFloatVectorToJsonObject(cusObj, "position", cusPositionToAdd);
    JsonHelper::AddFloatToJsonObject(cusObj, "radius", 1.0);

    Customer customer = Customer(cusPositionToAdd, cusObj);  
    float weight = 5.0; 

    Package package = Package(positionToAdd, directionToAdd, weight, &customer, obj); 

  }

  
}  // namespace csci3081