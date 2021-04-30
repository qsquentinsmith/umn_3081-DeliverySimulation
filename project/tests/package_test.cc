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
      float weight = 5.0; 

      JsonHelper::AddFloatToJsonObject(CusObj, "radius", 1.0);
      customer = new Customer(position_to_add, CusObj); 
      package = new Package(positionToAdd, directionToAdd, weight, customer, obj); 

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


  TEST_F(PackageTest, DynamicTest) {
    /*** SetDynamic() ***/
    package->SetDynamic(true);
    ASSERT_EQ(package->IsDynamic(), true) << "isdynamic";
    package->SetDynamic(false);
    ASSERT_EQ(package->IsDynamic(), false) << "isdynamic";
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
    std::vector<float> newPos;
    newPos.push_back(0.0);
    newPos.push_back(0.0);
    newPos.push_back(0.0);
    package->SetPosition(newPos);
    ASSERT_FLOAT_EQ(package->GetPosition()[0], 0.0);
    ASSERT_FLOAT_EQ(package->GetPosition()[1], 0.0);
    ASSERT_FLOAT_EQ(package->GetPosition()[2], 0.0);
  }


  TEST_F(PackageTest, SetDirectionTest) {
    /*** SetDirection(), GetDirection() ***/
    std::vector<float> newDir;
    newDir.push_back(1.0);
    newDir.push_back(1.0);
    newDir.push_back(1.0);
    package->SetDirection(newDir);
    ASSERT_FLOAT_EQ(package->GetDirection()[0], 1.0);
    ASSERT_FLOAT_EQ(package->GetDirection()[1], 1.0);
    ASSERT_FLOAT_EQ(package->GetDirection()[2], 1.0);
  }


  TEST_F(PackageTest, SetCustomerTest) {
    std::vector<float> newDir;
    newDir.push_back(1.0);
    newDir.push_back(1.0);
    newDir.push_back(1.0);
    package->SetDirection(newDir);

    /*** SetCustomer(), GetCustomerPosition() ***/
    Customer* customer2;
    customer2 = new Customer(newDir, CusObj);
    package->SetCustomer(customer2);
    ASSERT_FLOAT_EQ(package->GetCustomerPosition()[0], 1.0);
    ASSERT_FLOAT_EQ(package->GetCustomerPosition()[1], 1.0);
    ASSERT_FLOAT_EQ(package->GetCustomerPosition()[2], 1.0);

    /*** GetCustomer() ***/
    ASSERT_EQ(package->GetCustomer(), customer2);
  }


  TEST_F(PackageTest, PackageIDTest) {
    ((EntityBase*)package)-> SetId(30);
    ASSERT_EQ(((EntityBase*)package)-> GetId(), 30);
    ((EntityBase*)package)-> SetId(40);
    ASSERT_EQ(((EntityBase*)package)-> GetId(), 40);
  }


  TEST_F(PackageTest, PackageDetailsTest) {
    ASSERT_EQ(picojson::value(package->GetDetails()).serialize(), picojson::value(obj).serialize());
  }


  TEST_F(PackageTest, PackageRadiusTest) {
    ASSERT_EQ(package->GetRadius(), 1.0);
  }


  TEST_F(PackageTest, PackageNameTest) {
    ASSERT_EQ(package->GetName(), "");
  }


  TEST_F(PackageTest, PackageColorTest) {
    package->SetColor("0xF7DC6F");
    ASSERT_NE(picojson::value(package->GetDetails()).serialize(), picojson::value(obj).serialize());

    obj["color"] = picojson::value("0xF7DC6F");
    ASSERT_EQ(picojson::value(package->GetDetails()).serialize(), picojson::value(obj).serialize());
  }


  TEST_F(PackageTest, PackageVersionTest) {
    package->SetVersion(1);
    ASSERT_EQ(package->GetVersion(), 1) << "version";

  }

  
}  // namespace csci3081