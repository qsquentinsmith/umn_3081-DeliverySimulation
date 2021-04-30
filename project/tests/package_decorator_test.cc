#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include <string>
//#include "battery.h"

#include <iostream>

namespace csci3081 {

    using entity_project::IEntity;

    class PackageDecoratorTest : public ::testing::Test {
        protected:
            Package* package;
            Decorator* decorator; 
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

        }
        virtual void TearDown() {
            delete package;
        }
    };

  /*******************************************************************************
   * Test Cases
   ******************************************************************************/

    TEST_F(PackageDecoratorTest, GetPackageDecoratorTest) {
        decorator->GetDecoratedPackage(package);

        ASSERT_NE(picojson::value(package->GetDetails()).serialize(), picojson::value(obj).serialize());
    
        obj["color"] = picojson::value("0xEC7063");

        ASSERT_EQ(picojson::value(package->GetDetails()).serialize(), picojson::value(obj).serialize());
    }

    TEST_F(PackageDecoratorTest, GetPositionTest) {
    
        ASSERT_EQ(((PackageDecorator*) package)->GetPosition(), ((Package*) package)->GetPosition());

    }

    TEST_F(PackageDecoratorTest, GetDirectionTest) {

        ASSERT_EQ(((PackageDecorator*) package)->GetDirection(), ((Package*) package)->GetDirection());

    }

    TEST_F(PackageDecoratorTest, SetDynamicTest) {
        PackageDecorator* decorated;
        decorated = new LightWeight(package);
        ((LightWeight*) decorated)->SetDynamic(true);
        ASSERT_EQ(((Package*) package)->IsDynamic(), true);
        ((LightWeight*) decorated)->SetDynamic(false);
        ASSERT_EQ(((Package*) package)->IsDynamic(), false);
        
    }


  




}  // namespace csci3081