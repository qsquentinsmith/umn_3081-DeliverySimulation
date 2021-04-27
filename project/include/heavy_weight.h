/**
 *@file heavy_weight.h
 */
#ifndef HEAVY_WEIGHT_H_
#define HEAVY_WEIGHT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
 #include "idecorate.h"
namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A decoration used in the decorator pattern that changes heavier packages to red
 *
 */
	class Heavy_Weight : public IDecorate  {
		public:
		   /**
		    * @brief Changes the packages color to red if it weighs more than 4.0 
		    * 
	        * @param entity: entity to be decorated 
		    */
            void Decorate(IEntity* entity);

	};
}  // namespace csci3081


#endif  // HEAVY_WEIGHT_H_