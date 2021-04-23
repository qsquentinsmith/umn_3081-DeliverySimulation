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
    std::vector<float> position_to_add;
    position_to_add.push_back(498.292);
    position_to_add.push_back(253.883);
    position_to_add.push_back(-228.623);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
    std::vector<float> direction_to_add;
    direction_to_add.push_back(1);
    direction_to_add.push_back(0);
    direction_to_add.push_back(0);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
    JsonHelper::AddFloatToJsonObject(obj, "radius", 1.0);

    Customer* customer = nullptr; 
    float weight = 5.0; 

    Package package = Package(position_to_add, direction_to_add, weight, customer, obj); 

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
    std::vector<float> position_to_add;
    position_to_add.push_back(498.292);
    position_to_add.push_back(253.883);
    position_to_add.push_back(-228.623);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
    std::vector<float> direction_to_add;
    direction_to_add.push_back(1);
    direction_to_add.push_back(0);
    direction_to_add.push_back(0);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
    JsonHelper::AddFloatToJsonObject(obj, "radius", 2.0);

    picojson::object cusObj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(cusObj, "type", "customer");
    std::vector<float> cus_position_to_add;
    cus_position_to_add.push_back(46.78);
    cus_position_to_add.push_back(53.159);
    cus_position_to_add.push_back(-384.23);
    JsonHelper::AddStdFloatVectorToJsonObject(cusObj, "position", cus_position_to_add);
    JsonHelper::AddFloatToJsonObject(cusObj, "radius", 1.0);

    Customer customer = Customer(cus_position_to_add, cusObj);  
    float weight = 5.0; 

    Package package = Package(position_to_add, direction_to_add, weight, &customer, obj); 

    // ASSERT_FLOAT_EQ(package.GetCustomerPosition().at(0),(float) 46.78);
    // ASSERT_FLOAT_EQ(package.GetCustomerPosition().at(1), (float) 53.159);
    // ASSERT_FLOAT_EQ(package.GetCustomerPosition().at(2), (float) -384.23);
  }

  
}  // namespace csci3081