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
    picojson::object obj;
    Customer* customer;

    virtual void SetUp() {

      obj = JsonHelper::CreateJsonObject();
      JsonHelper::AddStringToJsonObject(obj, "type", "customer");
      std::vector<float> position_to_add;
      position_to_add.push_back(498.292);
      position_to_add.push_back(253.883);
      position_to_add.push_back(-228.623);
      JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
      JsonHelper::AddFloatToJsonObject(obj, "radius", 1.0);
      customer = new Customer(position_to_add, obj); 

    }
    virtual void TearDown() {
      delete customer;
    }
  };

  /*******************************************************************************
   * Test Cases
   ******************************************************************************/
  
  TEST_F(CustomerTest, CustomerConstructor) {
    /*** Customer(): Constructor ***/
    ASSERT_EQ(picojson::value(customer->GetDetails()).serialize(), picojson::value(obj).serialize());
  }

  TEST_F(CustomerTest, CustomerDirectionTest) {
    /*** GetDirection() ***/
    ASSERT_FLOAT_EQ(customer->GetDirection()[0], 0.0);
    ASSERT_FLOAT_EQ(customer->GetDirection()[1], 0.0);
    ASSERT_FLOAT_EQ(customer->GetDirection()[2], 0.0);
  }

   TEST_F(CustomerTest, CustomerPositionTest) {
    /*** GetPosition() ***/
    ASSERT_FLOAT_EQ(customer->GetPosition()[0], 498.292);
    ASSERT_FLOAT_EQ(customer->GetPosition()[1], 253.883);
    ASSERT_FLOAT_EQ(customer->GetPosition()[2], -228.623);
  }


}  // namespace csci3081