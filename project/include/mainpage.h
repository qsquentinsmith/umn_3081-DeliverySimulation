/*! \mainpage CSCI 3081 Delivery Simulation Project

Introduction:
================
<a id="top"></a>
Welcome to our Autonomous Delivery Simulation! 

<b>Table of Contents:</b>
1. <a href="#getCode"> How To Run The Simulation </a>
2. <a href="#newFeat">New Feature</a>
3. <a href="#designPatterns"> Entity Factory Design Choices </a>
    - <a href="#compositeFactory">Composite Factory</a>
    - <a href="#concreteFactory">Concrete Factory</a>
    - <a href="#abstractFactory">Abstract Factory</a>
4. <a href="#observer"> Observer Pattern Design Discussion </a>
5. <a href="#routes"> Design and Implementing New Routes </a>
    - <a href="#beeline">The Beeline Path Route</a>
    - <a href="#smart">The Smart Path Route</a>
    - <a href="#parabolic">The Parabolic Path Route</a>
    - <a href="#strategy">Strategy Pattern</a>
6. <a href="#decorator">Decorator Pattern</a>
7. <a href="#difficulties">Difficulties and Advice</a>
8. <a href="#team">Team Documentation</a>




<a id = "getCode">1. How To Run The Simulation</a>:
------------------------------------------------------------
 
<u> Obtaining the Code: </u>

You can clone the Delivery Simulation from this github repository: https://github.umn.edu/umn-csci-3081-s21/repo-iter2-01-29.git

<u> Compiling the Code: </u>

In order to run the simulation, ensure you are in the project directory.
In your terminal, run the command 'make'. This compiles the project. 

~~~~~
cd /home/user/repo/project
make
~~~~~

Hopefully, the 'make' command compiles without errors; it may take a while. 
After the project compiles, type 'bin/run.sh' to start the server. 
Open a web browser (firefox) and go to this link: http://127.0.0.1:8082/
You should be able to see the environment of the simulation. 


In order to see specific entities, navigate to the top right and choose the entity of your choice.
Choose Drone to see the drone flying towards the package. The drone will eventually pick up the package
and take it to the customer. In fact, there are several scenes you can test, which are listed under web/scenes
directory. In order to run a specific scene, type 'bin/run.sh scenes/(* insert scene name *)' after the
project has compiled. For example, we can test all features with the command 'bin/run.sh scenes/all_features.json'.

<a href="#top">Back to top</a>

<a id = "newFeat">2. New Features</a>:
------------------------------------------------------------

Our additional feature involves the package changing color depending on its weight. Once the package is picked up, it’ll become green if it is a lightweight, yellow if it is a middleweight or red if it is a heavyweight. We defined lightweight packages as less than 2 lbs, middleweight packages as between 2 lbs and 4 lbs and heavyweight packages as any weight above 4 lbs. As a result, these color changes will help indicate the heaviness of the load carried by the drone or robot.

<u> How To Run </u>

If you would like to run our additional feature, run the scene “decorated_packages.json” in a similar fashion described earlier. There are packages that vary in weight in this feature, so you should be able to see the different colors. In all of the other scenes, the packages will be colored green once picked up because the default weight is used. Packages are defaulted to a weight of 1 lb in their constructors. 

<a href="#top">Back to top</a>



<a id ="designPatterns">3. Entity Factory Design Choices</a>:
----------------------------------------------------------------
 
Let's analyze the design pattern used in this project and possible alternatives!


<b><a id = "compositeFactory"> Composite Factory </a></b>


This package delivery simulation is implemented using the <a href = https://refactoring.guru/design-patterns/composite/cpp/example>composite factory pattern</a>, where a composite factory contains all entity-specific factories which construct their respective entites. The advantage of using such a pattern is that it is simple to add other factories to the composite factory. As a result, it is also simple to add entities to the simulation. If the simulation requiresa new type of entity, all that would need to be done to facilitate the creation of these new entities would be to add its factory to the composite factory.
  
On the other hand, a disadvantage of using the composite factory pattern would be its tendency to be too general. Any type of factory can be included within the composite factory. This means the composite factory could be a class that contains several miscellaneous factories, defeating the principle of "one class, one purpose." On a large scale, the composite factory would also have to keep track of many factories, which could be cumbersome. 

Example Composite Factory Pattern:

<u>Composite Factory UML General</u>

<img src="../images/CompositeFactory.png" width="1000">

<u>Delivery Simulation Composite Factory UML</u>

<img src="../images/composite_fact.png" width="1400">


<b><a id = "abstractFactory"> Abstract Factory </a></b>

In terms of the <a href = https://refactoring.guru/design-patterns/abstract-factory/cpp/example>abstract factory pattern</a>, its advantage is that all child classes must implement its pure virtual methods. This results in uniform behavior amongst the child classes. For example, all of the factory classes implemented the CreateEntity method and each factory churned out IEntity objects which could be grouped together through polymorphism. 

A con regarding such a pattern would be that concrete classes extending the abstract factory class might cause more complication within the strucuture of classes. If the newly extended concrete class has its own sub-classes, all of the sub-classes must also implement the pure virtual methods of the abstract factory class. Therefore, this takes away from the convenience of having all related classes extending the same abstract class. While this project has an abstract factory class, it does not solely use the abstract 
factory pattern. 

Example Abstract Factory Pattern:

<img src="../images/AbstractFactory.png" width="600">

 

<b><a id = "concreteFactory"> Concrete Factory </a></b>

Looking at the concrete factory pattern, an advantage is the separation from creation of objects and their use. Creating an object every time it has to be used can be cumbersome. The concrete factory pattern allows you to create all of the necessary objects in one place. As long you know the necessary parameters, 
you can pass them along to the concrete factory which will generate the objects for you. 

In contrast, this is not a very good design choice if you have to keep adding different types of objects to the factory. This would require constantly modifying the the factory class, adding more if-else statements or switch cases. As a consequence, this can be very inconvenient when dealing with many types of objects. Therefore this method was not implemented for this project. 

Example Concrete Factory Pattern: 
 
<img src="../images/ConcreteFactory.png" width="600">


<a href="#top">Back to top</a>




<a id = "observer">4. Observer Pattern Design Discussion</a>:
------------------------------------------------------------
 
The design of our <a href = https://refactoring.guru/design-patterns/observer>observer pattern</a> 
came in two deliverables that we will consider separately.

 
The first deliverable consisted of stand-alone code scattered throughout our program that performed the entirety of observer notifications. This design was great for testing how things worked and to determine if observers were being notified appropriately.  The downside to this was that it was messy and repetitive.  Each notification was embedded within another large chunk of code which caused for more complicated looking code than we prefered. Also, since all the notification types are very similar, there was a lot of code that was being repeated for every notification.

To fix this we did the following . . .
 
Our second deliverable solves all the problems that the first deliverable had.  An Observer class was created to handle all the creations and executions of observer notifications.  This allowed for only a single function call needed to be added to areas in the program that require an observer to be notified of an event. It also allows for all functions within the class to share repetitive code rather than doing it individually multiple times like what was being done before. The structure of our class is very simple with one function per notification type (scheduled, moving, enroute, delivered, idle) that would 
create the json object being sent to the observers.  Then they were all able to use the same Notify() function that iterated through all the observers and executed their OnEvent() function.  And finally in order to populate/manage the vector of observers used in Notify(), we had the AddObserver() and RemoveObserver() functions similar to Delivery_Simulation.


<u>Simulation Observer Pattern UML</u>

<img src="../images/observer.png" width="600">


<a href="#top">Back to top</a>


<a id = "routes">5. Design and Implementing the different routes </a>:
------------------------------------------------------------------

We have created three routes for our simulation: the beeline route, the smart path route, and the parabolic route. 

<b><a id = "beeline"> The Beeline Path Route: </a></b>

The beeline route is one of the strategies implemented by the strategy pattern; the Beeline class generates the route necessary for carriers to move in a beeline way. As of now, only the drone carriers can move in a beeline. More specifically, the drone will rise high enough above the buildings and move to its destination in a straight line. Thereafter, it'll lower down until it reaches its destination. Given the initial position of the drone and its final destination, which is either the package location or the customer location, there is enough information to generate the coordinates. The coordinates are as follows: the initial position, high enough above the initial position, high enough above the destination and the destination. We use a height of 350 above the two endpoints, which should be high enough not to collide with any buildings. In order to better visualize the beeline path, the observer pattern will generate a colored path in the simulation during the drone's flight.  

<img src="../images/beeline.png" width="800">

<b><a id = "smart"> The Smart Path Route: </a></b>

The smart path route utilizes the interface IGraph. IGraph represents a read only graph object. It contains a function named GetPath(source, destination), which when given a source and destination in the form of 3-element x,y,z vectors, the function will return a list of positions to traverse in-order, which avoids the geometry of the scene. The returned path includes the source and destination points. The GetPath function uses <a href = https://www.freecodecamp.org/news/dijkstras-shortest-path-algorithm-visual-introduction/>Dijkstra's algorithm</a> to find the shortest path. 

The observer pattern will trace the smart route if used. The smart route is used in both carrier classes, drone and robot, and is the only option for the robot class. To see all smart paths during the simulation go to the top right menu box and check the all routes box.


<img src="../images/smart.png" width="800">


<b><a id = "parabolic"> The Parabolic Path Route:</a></b>

One of the strategies for entity movement in the strategy pattern is parabolic movement, which is only utilized by the drone. The path forms a parabola from the drones original location to the package and then another parabola to the customer avoiding tall buildings along the way. This parabola is calculated using the Riemann sum which is a set of points along the parabola used to estimate the continuous function. The following equation was used
to graph the parabola:

y = (1 - distance(V, Vm)2 / distance(Vo, Vm)2) * j 

    - Vo is our source point
    - V is the point we are moving to
    - Vm is our midpoint equal to distance(source, destination) / 2
    - T is the number of steps we are estimating
    - Vt is our step interval equal to distance(source, destination) / T
    - j is the maximum height the parabola will reach

<img src="../images/parabolic.png" width="800">

<b><a id = "strategy">Strategy Pattern:</a></b>

Choosing the route relies on our <a href = https://refactoring.guru/design-patterns/strategy/>strategy pattern</a>. The strategy pattern reads the carrier's picojson to see if a route is specified for use. If there is a specific route that needs to be used, the strategy pattern will return the path of that route. The path is returned as a vector of coordinates allowing our carrier to implement the movement by iterating through the vector of coordinates. 

A strategy pattern defines a family of algorithms, encapsulates each one, and then makes them interchangeable. It allows for the algorithms to be independent, which reduces coupling. The concrete classes in our strategy pattern are beeline, smart_path, and parabolic. These concrete classes inherit from our abstract strategy class which ensures interchangeability. The strategy class is called from each of the carriers (drone or robot), so the specific carrier will have a path associated with it. 

<u>Strategy Pattern General UML</u>

<img src="../images/strategyPattern.png" width="600">

<u>Simulation Strategy Pattern UML</u>

<img src="../images/strategy.png" width="600">

<a href="#top">Back to top</a>

<a id = "decorator">5. Decorator Pattern</a>:
------------------------------------------------------------

In order to add color changing behavior to the package, we decided to incorporate the decorator pattern. In terms of the UML diagram, ‘EntityBase’ is an abstract class, which has a pure virtual method called ‘SetDynamic’. This method allows entities to move or stay put; the EntityBase protected variable ‘dynamic’ must be set to true in order for an entity to move. A concrete package class named ‘Package’ inherits from EntityBase and overrides SetDynamic in the most basic way by setting the ‘dynamic’ variable to the value passed into the method. On the other hand, a base package decorator class named ‘PackageDecorator’ also inherits from EntityBase. This is the base class for all of our package decorations. Each decoration has one class: LightWeight, MiddleWeight, HeavyWeight. Each of these subclasses override SetDynamic to not only set whether the package should move, but also to add color depending on the weight. Lastly, the ‘DecoratorFactory’ class utilizes the simple factory pattern to create specific decorations based on the package that is passed in to the ‘GetDecoratedPackage’ method. While handling the movement of the carriers and packages in the DeliveryManager class, the DecoratorFactory churns out a decorated package with type ‘EntityBase✴’. Through polymorphism, calling SetDynamic on this decorated package will execute the SetDynamic method depending on its decoration. 

<u>Decorator Pattern UML</u>

<img src="../images/decorator_uml_gen.png" width="400">

<u>Simulation Decorator Pattern UML</u>

<img src="../images/decorator.png" width="500">

<b>Reasoning for Pattern Used:</b>

We considered using basic inheritance in order to create customized packages. In other words, a LightWeight, a MiddleWeight and a HeavyWeight class could inherit directly from the Package class. While this could work for these three customizations, it becomes more complicated when other customizations are added. This implementation would require a class for every new customization, which could result in an absurd amount of subclasses for the Package class. In this context, the decorator pattern allows us to add behavior to packages without extending the Package class or changing existing code in the Package class. In addition, the decorator pattern allows us to wrap multiple decorations around the package. For example, we could have an ‘Express’ decoration that also extends PackageDecorator. What if we wanted a heavyweight express package? Rather than creating a ‘HeavyWeightExpress’ class, the decorator pattern allows us to use both the HeavyWeight and Express class to add their specific behaviors to a package. Lastly, we decided to generate our decorations using the simple factory pattern, which creates specific objects depending on conditions. The simple factory pattern can become long and hard to read if there are several conditions. However, we can justify using this pattern because we only have three types of decorations. Overall, utilizing a DecoratorFactory follows the single responsibility principle as it handles the creation of decorators separately from where the decorator is used.


<a href="#top">Back to top</a>



<a id = "difficulties">6.Difficulties and Advice </a>
------------------------------------------------------------
<b>Second Iteration:</b>

There were several aspects of this iteration that were difficult: understanding parabolic movement, debugging random errors after refactoring the way the carrier moves and implementing the strategy pattern for the smart path. The biggest tip we all agree on is to plan better before actually coding, because diving right into to coding tends to generate more bugs. Taking down notes on the professor's lectures, lab resources and attending office hours were the most helpful strategies in progressing in our project. In addition, setting aside lots of time for debugging is especially useful because it is a difficult task. 

<b>Third Iteration:</b>

During the third iteration, the decorator pattern was particularly challenging to implement. Our first interpretation of the decorator pattern was incorrect because we didn't implement the class structure properly. We originally changed the color of the package directly instead of passing the entity into the constructor of a decoration class. We then corrected the structure of our decorator pattern so that we included a PackageDecorator class that inherits from our virtual class EntityBase. Our concrete decorations then inherit from this PackageDecorator class, which makes it easier to implement the color change because we can override a function of the concrete package and apply the color change. In order to implement the decorator pattern, it is important to stick to the correct class structure, as well as making sure the constructors of the decorator class family take in the abstract class pointer of the object to be decorated. Visiting TA office hours and studying the examples posted on Canvas are also great resources to be aware of. 


<a href="#top">Back to top</a>

<a id = "team">7. Team Documentation</a>:
------------------------------------------------------------

Roles:
- Peter: Reporter
- Nakul: Development Lead
- Spencer: Project Manager
- Quentin: Scheduler

<b>Meeting #1:</b> 

For our first meeting, we decided to tackle the biggest challenges first.  Both Peter and Spencer worked together on the parabolic path. Nakul created a new carrier class for shared functionality between drones and robots.  Quentin fixed bugs with our smart path that were still causing problems from the previous deliverable.
 
<b>Meeting #2:</b> 
 
Our second meeting consisted of many large changes to our program.  It was at this time that Peter rebuilt the observer pattern into its own class.  Nakul completed the strategy pattern and solved some bugs with our beeline path.  Quentin implemented the battery functionality so that carriers deplete their batteries.  Spencer completed the parabolic path and modified it to fit with Nakul's implementation of the strategy pattern.
 
<b>Meeting #3:</b> 
 
During our last team meeting before the submission deadline, we determined which documentation and testing tasks need to be accomplished. These were delegated based on which tasks each team member had previously completed.  For Peter, he was given the task of completing the testing and documentation on our design and implementation of the observers, as well as completing the team documentation.  Nakul was tasked with documenting the design of the beeline route and testing of the drone. Spencer completed the parabolic testing and design documentation.  
Finally, Quentin was in charge of smart path documentation and testing the robot.
 
<b>Meeting #4:</b> 

During our first team meeting, after deciding on which feature to implement, we all started working on the decorator pattern.  This was a team effort in order to restructure existing code, create a decorator class, and create a simple factory for the pattern to use.  We had a few initial versions that didn’t follow the pattern properly and were then needed to be redone.

<b>Meeting #5:</b> 

For our second meeting we decided to have people finish up some final things for iteration three and also fix some problems from iteration two.  Nakul was given the task of writing our Doxygen for all the new decorator pattern files.  Quentin updated the existing google tests and added more for any additional public functions we created.  And lastly, Peter and Spencer separated a large function into several smaller ones in delivery_manager.cc and also renamed variables for consistency.

<b>Meeting #6:</b> 

In our last meeting we focused on documentation for the iteration.  Nakul completed the description of our feature and our design implementation documentation.  Quentin updated our UML and fixed any problems we had in iteration two.  Spencer wrote out the documentation for the challenges we came across while implementing this feature.  And Peter completed the team documentation.


<a href="#top">Back to top</a>
 



*/
