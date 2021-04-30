#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "package_factory.h"

#include <iostream>

namespace csci3081 {

  using entity_project::IEntity;

  class PackageFactoryTest : public ::testing::Test {
   protected:
    Package * package;
    picojson::object obj;

    virtual void SetUp() {
      //setting up picojson::object for creat identity
      obj = JsonHelper::CreateJsonObject();
      JsonHelper::AddStringToJsonObject(obj, "type", "package");
      std::vector<float> position_to_add;
      position_to_add.push_back(-951.412);
      position_to_add.push_back(254.665);
      position_to_add.push_back(298.271);
      JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
      std::vector<float> direction_to_add;
      direction_to_add.push_back(1);
      direction_to_add.push_back(0);
      direction_to_add.push_back(0);
      JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
      JsonHelper::AddFloatToJsonObject(obj, "radius", 1.0);
      JsonHelper::AddFloatToJsonObject(obj, "weight", 1.0);
      package = new Package(position_to_add, direction_to_add, 5.0, nullptr, obj);
    }
    virtual void TearDown() {
      delete package;
    }
  };

  /*******************************************************************************
   * Test Cases
   ******************************************************************************/
  
  TEST_F(PackageFactoryTest, CreateEntityTest) {
    PackageFactory packageFactory;
    IEntity* packageFromFactory = packageFactory.CreateEntity(obj);

    /*** CreateEntity() ***/
    ASSERT_NE(packageFromFactory, nullptr);

    ASSERT_FLOAT_EQ(package->GetPosition()[0], packageFromFactory->GetPosition().at(0));
    ASSERT_FLOAT_EQ(package->GetPosition()[1], packageFromFactory->GetPosition().at(1));
    ASSERT_FLOAT_EQ(package->GetPosition()[2], packageFromFactory->GetPosition().at(2));
    ASSERT_FLOAT_EQ(package->GetDirection()[0], packageFromFactory->GetDirection().at(0));
    ASSERT_FLOAT_EQ(package->GetDirection()[1], packageFromFactory->GetDirection().at(1));
    ASSERT_FLOAT_EQ(package->GetDirection()[2], packageFromFactory->GetDirection().at(2));
    ASSERT_NE(((Package*)packageFromFactory)->GetWeight(), package->GetWeight());
  }

}  // namespace csci3081