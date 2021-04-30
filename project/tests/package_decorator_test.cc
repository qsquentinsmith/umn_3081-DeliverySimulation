#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include <string>

#include <iostream>

namespace csci3081 {

    using entity_project::IEntity;

    class PackageDecoratorTest : public ::testing::Test {
        protected:
            Package* package;
            DecoratorFactory* decoratorFactory; 
            EntityBase* decoratedPackage;
            picojson::object obj;
            std::vector<float> position_to_add;
            std::vector<float> direction_to_add;

        virtual void SetUp() {

            //setting up package
            obj = JsonHelper::CreateJsonObject();
            JsonHelper::AddStringToJsonObject(obj, "type", "package");
            
            position_to_add.push_back(498.292);
            position_to_add.push_back(253.883);
            position_to_add.push_back(-228.623);
            JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
            
            direction_to_add.push_back(1);
            direction_to_add.push_back(0);
            direction_to_add.push_back(0);
            JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
            JsonHelper::AddFloatToJsonObject(obj, "radius", 1.0);
            float weight = 5.0;

            package = new Package(position_to_add, direction_to_add, weight, nullptr, obj); 

            decoratedPackage = decoratorFactory->GetDecoratedPackage(package);
            
        }
        virtual void TearDown() {
            delete package;
        }
    };

  /*******************************************************************************
   * Test Cases
   ******************************************************************************/

    TEST_F(PackageDecoratorTest, GetPackageDecoratorTest) {
        ASSERT_NE(decoratedPackage, nullptr);
    }


    TEST_F(PackageDecoratorTest, GetPositionTest) {
        ASSERT_EQ(decoratedPackage->GetDirection(), package->GetDirection());
    }


    TEST_F(PackageDecoratorTest, GetDirectionTest) {
        ASSERT_EQ(decoratedPackage->GetDirection(), package->GetDirection());
    }


    TEST_F(PackageDecoratorTest, SetDynamicTest) {
        decoratedPackage->SetDynamic(true);
        ASSERT_EQ(package->IsDynamic(), true);
        decoratedPackage->SetDynamic(false);
        ASSERT_EQ(package->IsDynamic(), false);
    }


  




}  // namespace csci3081