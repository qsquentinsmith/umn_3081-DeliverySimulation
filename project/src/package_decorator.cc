#include "package_decorator.h"

namespace csci3081 {
    PackageDecorator::PackageDecorator(AbstractPackage* package) {
        package_ = package; 
    }

    void PackageDecorator::Decorate(){
        package_->Decorate(); 
    }
}