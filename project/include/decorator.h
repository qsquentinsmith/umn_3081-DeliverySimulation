/**
 *@file decorator.h
 */
#ifndef DECORATOR_H_
#define DECORATOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
 #include "idecorate.h"
 #include "light_weight.h"
 #include "middle_weight.h"
 #include "heavy_weight.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definition
 ******************************************************************************/
/**
 * @brief The decorator is a base class that contains a vecotr of all decorations to be applied in the simulation 
 * 
 */ 
  class Decorator : public IDecorate {
   public:
      /**
	* @brief Calls decorate on all decorations that apply to entity in the decorations vector
	* 
	* @param entity: entity to be decorated  
	*/
      void Decorate(IEntity* entity);
      /**
	* @brief Adds a new decoration to the decorations vector
	* 
	* @param decoration: Decoration to be added to the decorations vector
	*/
      void AddDecoration(IDecorate* decoration);
  private:
        std::vector<IDecorate*> decorations;
  }; 

};

#endif  // DECORATOR_H_