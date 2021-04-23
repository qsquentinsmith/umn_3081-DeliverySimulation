#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "customer.h"

#include <iostream>

namespace csci3081 {

  using entity_project::IEntity;

  class CustomerTest : public ::testing::Test {
   protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
  };

  /*******************************************************************************
   * Test Cases
   ******************************************************************************/
  
  //testing constructor
  TEST_F(CustomerTest, CustomerConstructor) {
    //setting up customer
    picojson::object obj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj, "type", "customer");
    std::vector<float> position_to_add;
    position_to_add.push_back(498.292);
    position_to_add.push_back(253.883);
    position_to_add.push_back(-228.623);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
    JsonHelper::AddFloatToJsonObject(obj, "radius", 1.0);

    Customer customer = Customer(position_to_add, obj); 
    
    //testing position and direction set in constructor
    ASSERT_FLOAT_EQ(customer.GetPosition()[0], 498.292);
    ASSERT_FLOAT_EQ(customer.GetPosition()[1], 253.883);
    ASSERT_FLOAT_EQ(customer.GetPosition()[2], -228.623);
    ASSERT_FLOAT_EQ(customer.GetDirection()[0], 0.0);
    ASSERT_FLOAT_EQ(customer.GetDirection()[1], 0.0);
    ASSERT_FLOAT_EQ(customer.GetDirection()[2], 0.0);
    
    // Checks that when GetDetails() is called, the entity returns 
    // the picojson object that was used to initialize it
    ASSERT_EQ(picojson::value(customer.GetDetails()).serialize(), picojson::value(obj).serialize());

  }
}  // namespace csci3081