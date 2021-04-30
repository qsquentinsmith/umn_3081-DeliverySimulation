#include "decorator.h"

namespace csci3081 {

    void Decorator::GetDecoratedPackage(Package* package) {
       
        float weight = package->GetWeight(); 
        PackageDecorator* decorated; 
        if (weight < 2.0) {
            decorated = new LightWeight(package); 
            ((LightWeight*)decorated)->SetDynamic(true); 
        }
        else if (weight >= 2.0 && weight < 4.0) {
            decorated = (MiddleWeight*) new MiddleWeight(package);
            ((MiddleWeight*)decorated)->SetDynamic(true); 
        }
        else if (weight >= 4.0) {
            decorated = (HeavyWeight*) new HeavyWeight(package);
            ((HeavyWeight*)decorated)->SetDynamic(true); 
        }
    }

}