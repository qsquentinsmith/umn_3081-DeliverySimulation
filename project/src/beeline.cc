#include "beeline.h"

namespace csci3081 {

    vector<vector<float>> Beeline::GetRoute(vector<float> source, vector<float> destination) {
        vector<vector<float>> route; 

        route.push_back(source);

        vector<float> positionAboveSource; 
        positionAboveSource.push_back(source.at(0));
        positionAboveSource.push_back(350.0);
        positionAboveSource.push_back(source.at(2));
        route.push_back(positionAboveSource); 

        vector<float> positionAboveDestination; 
        positionAboveDestination.push_back(destination.at(0));
        positionAboveDestination.push_back(350.0);
        positionAboveDestination.push_back(destination.at(2));
        route.push_back(positionAboveDestination); 

        route.push_back(destination);

        return route; 
    }
    
}