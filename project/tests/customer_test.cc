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
      std::vector<float> positionToAdd;
      positionToAdd.push_back(498.292);
      positionToAdd.push_back(253.883);
      positionToAdd.push_back(-228.623);
      JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", positionToAdd);
      JsonHelper::AddFloatToJsonObject(obj, "radius", 1.0);
      customer = new Customer(positionToAdd, obj); 

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

  TEST_F(CustomerTest, CustomerIDTest) {
    ((EntityBase*)customer)-> SetId(30);
    ASSERT_EQ(((EntityBase*)customer)-> GetId(), 30);
    ((EntityBase*)customer)-> SetId(40);
    ASSERT_EQ(((EntityBase*)customer)-> GetId(), 40);
  }

  TEST_F(CustomerTest, CustomerDetailsTest) {
    ASSERT_EQ(picojson::value(customer->GetDetails()).serialize(), picojson::value(obj).serialize());

  }

  TEST_F(CustomerTest, CustomerRadiusTest) {
    ASSERT_EQ(customer->GetRadius(), 1.0);
  }

  TEST_F(CustomerTest, CustomerNameTest) {
    ASSERT_EQ(customer->GetName(), "");
  }

  TEST_F(CustomerTest, CustomerColorTest) {
    customer->SetColor("0xF7DC6F");
    ASSERT_NE(picojson::value(customer->GetDetails()).serialize(), picojson::value(obj).serialize());

    obj["color"] = picojson::value("0xF7DC6F");
    ASSERT_EQ(picojson::value(customer->GetDetails()).serialize(), picojson::value(obj).serialize());
  }

  TEST_F(CustomerTest, CustomerVersionTest) {
    customer->SetVersion(1);
    ASSERT_EQ(customer->GetVersion(), 1) << "version";
  }

}  // namespace csci3081