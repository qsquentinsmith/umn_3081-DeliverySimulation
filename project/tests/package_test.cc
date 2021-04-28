#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "customer.h"
#include "package.h"

#include <iostream>

namespace csci3081 {

  using entity_project::IEntity;

  class PackageTest : public ::testing::Test {
   protected:
    picojson::object obj;
    picojson::object CusObj;
    Customer* customer;
    Package* package;

    virtual void SetUp() {
      //setting up customer
      CusObj = JsonHelper::CreateJsonObject();
      JsonHelper::AddStringToJsonObject(CusObj, "type", "customer");

      //setting up package
      obj = JsonHelper::CreateJsonObject();
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
      float weight = 5.0; 

      JsonHelper::AddFloatToJsonObject(CusObj, "radius", 1.0);
      customer = new Customer(position_to_add, CusObj); 
      package = new Package(position_to_add, direction_to_add, weight, customer, obj); 

    }
    virtual void TearDown() {
      delete package;
      delete customer;
      
    }
  };

  /*******************************************************************************
   * Test Cases
   ******************************************************************************/
  
  TEST_F(PackageTest, PackageConstructor) {
    /*** package(): Constructor ***/
    ASSERT_EQ(picojson::value(package->GetDetails()).serialize(), picojson::value(obj).serialize());

  }

  TEST_F(PackageTest, GetPositionTest) {
    /*** GetPosition() ***/
    ASSERT_FLOAT_EQ(package->GetPosition()[0], 498.292);
    ASSERT_FLOAT_EQ(package->GetPosition()[1], 253.883);
    ASSERT_FLOAT_EQ(package->GetPosition()[2], -228.623);
  }

  TEST_F(PackageTest, GetDirectionTest) {
    /*** GetDirection() ***/
    ASSERT_FLOAT_EQ(package->GetDirection()[0], 1.0);
    ASSERT_FLOAT_EQ(package->GetDirection()[1], 0.0);
    ASSERT_FLOAT_EQ(package->GetDirection()[2], 0.0);
  }

  TEST_F(PackageTest, GetWeightTest) {
    /*** GetWeight() ***/
    ASSERT_FLOAT_EQ(package->GetWeight(), 5.0); 
  }

  TEST_F(PackageTest, GetCustomerTest) {
    /*** GetCustomer() ***/
    ASSERT_EQ(package->GetCustomer(), customer);
  }

  TEST_F(PackageTest, GetCustomerPositionTest) {
    /*** GetCustomerPosition() ***/
    ASSERT_FLOAT_EQ(package->GetCustomerPosition()[0], 498.292);
    ASSERT_FLOAT_EQ(package->GetCustomerPosition()[1], 253.883);
    ASSERT_FLOAT_EQ(package->GetCustomerPosition()[2], -228.623);
  }

  TEST_F(PackageTest, SetPositionTest) {
    /*** SetPosition(), GetPosition() ***/
    std::vector<float> new_pos_;
    new_pos_.push_back(0.0);
    new_pos_.push_back(0.0);
    new_pos_.push_back(0.0);
    package->SetPosition(new_pos_);
    ASSERT_FLOAT_EQ(package->GetPosition()[0], 0.0);
    ASSERT_FLOAT_EQ(package->GetPosition()[1], 0.0);
    ASSERT_FLOAT_EQ(package->GetPosition()[2], 0.0);
  }

  TEST_F(PackageTest, SetDirectionTest) {
    /*** SetDirection(), GetDirection() ***/
    std::vector<float> new_dir_;
    new_dir_.push_back(1.0);
    new_dir_.push_back(1.0);
    new_dir_.push_back(1.0);
    package->SetDirection(new_dir_);
    ASSERT_FLOAT_EQ(package->GetDirection()[0], 1.0);
    ASSERT_FLOAT_EQ(package->GetDirection()[1], 1.0);
    ASSERT_FLOAT_EQ(package->GetDirection()[2], 1.0);
  }

  TEST_F(PackageTest, SetCustomerTest) {

    std::vector<float> new_dir_;
    new_dir_.push_back(1.0);
    new_dir_.push_back(1.0);
    new_dir_.push_back(1.0);
    package->SetDirection(new_dir_);

    /*** SetCustomer(), GetCustomerPosition() ***/
    Customer* customer2;
    customer2 = new Customer(new_dir_, CusObj);
    package->SetCustomer(customer2);
    ASSERT_FLOAT_EQ(package->GetCustomerPosition()[0], 1.0);
    ASSERT_FLOAT_EQ(package->GetCustomerPosition()[1], 1.0);
    ASSERT_FLOAT_EQ(package->GetCustomerPosition()[2], 1.0);

    /*** GetCustomer() ***/
    ASSERT_EQ(package->GetCustomer(), customer2);

  }

  
}  // namespace csci3081