#include "decorator_factory.h"

namespace csci3081 {

    EntityBase* DecoratorFactory::GetDecoratedPackage(Package* package) {
        float weight = ((Package*) package)->GetWeight(); 
        EntityBase* decoratedPackage = (EntityBase*) package; //new PackageDecorator(package); 
        if (weight < 2.0) {
            decoratedPackage = new LightWeight(decoratedPackage); 
             
        }
        else if (weight >= 2.0 && weight < 4.0) {
            decoratedPackage = new MiddleWeight(decoratedPackage);
            
        }
        else if (weight >= 4.0) {
            decoratedPackage = new HeavyWeight(decoratedPackage);
            
        }
        return decoratedPackage; 
    }
}