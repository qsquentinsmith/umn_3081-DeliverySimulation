/**
 * @file battery.h
 */
#ifndef BATTERY_H_
#define BATTERY_H_


namespace csci3081 {

/*******************************************************************************
 * Class Definition
 ******************************************************************************/
/**
 * @brief The Battery Class represents the battery that will be used for the carriers: drone and robot. 
 * 
 */  
  class Battery {
    public:
       /**
		* @brief Constructs Battery object 
		*
		* Used in the drone and robot classes. Each carrier has a battery. Max Charge will default to 10,000.
		*
		*/
	    Battery() {};

		/**
		* @brief Destructs Battery object 
		*
		*/
		~Battery() {};

		/**
		* @brief Constructs Battery object and initiallizes battery max charge to maxCharge.
		*
		* Used in the drone and robot classes. Each carrier has a battery. 
		*
		* @param maxCharge: float to initialize batteries max charge attribute.  
		*/
		Battery(float maxCharge);

	    /**
		* @brief Checks if the battery has charge  
		*
		* @return true or false depending on if the battery is dead 
		*/
	    bool IsDead(); 

	    /**
		* @brief Gets the remaining charge of the battery 
		*
		* @return the remaining battery charge 
		*/
	    float GetChargeRemaining(); 

	    /**
		* @brief Drains the battery's charge at a constant rate of 1 charge unit per second. 
		*
		* @param dt: the time step for each update 
		*
		*/
	    void DrainBattery(float dt); 


    private:
	    float maxCharge = 10000;
	    float chargeRemaining = 10000;
		bool deadBattery = false; 
  };

}
#endif  // BATTERY_H_
