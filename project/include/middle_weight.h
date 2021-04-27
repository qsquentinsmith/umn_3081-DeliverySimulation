/**
 *@file middle_weight.h
 */
#ifndef MIDDLE_WEIGHT_H_
#define MIDDLE_WEIGHT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
 #include "idecorate.h"
namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A decoration used in the decorator pattern that changes medium weight packages to yellow
 *
 */
	class Middle_Weight : public IDecorate  {
		public:
		    /**
		    * @brief Changes the packages color to yellow if it weighs between 2.0 and 4.0 
		    * 
	        * @param entity: entity to be decorated 
		    */
            void Decorate(IEntity* entity);

	};
}  // namespace csci3081


#endif  // MIDDLE_WEIGHT_H_