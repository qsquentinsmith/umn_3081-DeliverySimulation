/*! \mainpage CSCI 3081 Delivery Simulation Project

Introduction:
================

Welcome to our Autonomous Delivery Simulation! 

<b>Table of Contents:</b>
1. <a href="#getCode"> How To Run The Simulation </a>
2. <a href="#designPatterns"> Entity Factory Design Choices </a>
    - <a href="#compositeFactory">Composite Factory</a>
    - <a href="#concreteFactory">Concrete Factory</a>
    - <a href="#abstractFactory">Abstract Factory</a>
3. <a href="#observer"> Observer Pattern Design Discussion </a>
4. <a href="#routes"> Design and Implementing New Routes </a>
    - <a href="#beeline">The Beeline Path Route</a>
    - <a href="#smart">The Smart Path Route</a>
    - <a href="#parabolic">The Parabolic Path Route</a>
    - <a href="#strategy">Strategy Pattern</a>
5. <a href="#difficulties">Difficulties and Advice</a>
6. <a href="#team">Team Documentation</a>




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









<a id ="designPatterns">2. Entity Factory Design Choices</a>:
----------------------------------------------------------------
 
Let's analyze the design pattern used in this project and possible alternatives!


<b><a id = "compositeFactory"> Composite Factory </a></b>


This package delivery simulation is implemented using the <a href = https://refactoring.guru/design-patterns/composite/cpp/example>composite factory pattern</a>, where a composite factory contains all entity-specific factories which construct their respective entites. The advantage of using such a pattern is that it is simple to add other factories to the composite factory. As a result, it is also simple to add entities to the simulation. If the simulation requiresa new type of entity, all that would need to be done to facilitate the creation of these new entities would be to add its factory to the composite factory.
  
On the other hand, a disadvantage of using the composite factory pattern would be its tendency to be too general. Any type of factory can be included within the composite factory. This means the composite factory could be a class that contains several miscellaneous factories, defeating the principle of "one class, one purpose." On a large scale, the composite factory would also have to keep track of many factories, which could be cumbersome. 

Example Composite Factory Pattern (Besides This Project):

<img src="../CompositeFactory.png" width="1000">


<b><a id = "abstractFactory"> Abstract Factory </a></b>

In terms of the <a href = https://refactoring.guru/design-patterns/abstract-factory/cpp/example>abstract factory pattern</a>, its advantage is that all child classes must implement its pure virtual methods. This results in uniform behavior amongst the child classes. For example, all of the factory classes implemented the CreateEntity method and each factory churned out IEntity objects which could be grouped together through polymorphism. 

A con regarding such a pattern would be that concrete classes extending the abstract factory class might cause more complication within the strucuture of classes. If the newly extended concrete class has its own sub-classes, all of the sub-classes must also implement the pure virtual methods of the abstract factory class. Therefore, this takes away from the convenience of having all related classes extending the same abstract class. While this project has an abstract factory class, it does not solely use the abstract 
factory pattern. 

Example Abstract Factory Pattern:

<img src="../AbstractFactory.png" width="600">

 

<b><a id = "concreteFactory"> Concrete Factory </a></b>

Looking at the concrete factory pattern, an advantage is the separation from creation of objects and their use. Creating an object every time it has to be used can be cumbersome. The concrete factory pattern allows you to create all of the necessary objects in one place. As long you know the necessary parameters, 
you can pass them along to the concrete factory which will generate the objects for you. 

In contrast, this is not a very good design choice if you have to keep adding different types of objects to the factory. This would require constantly modifying the the factory class, adding more if-else statements or switch cases. As a consequence, this can be very inconvenient when dealing with many types of objects. Therefore this method was not implemented for this project. 

Example Concrete Factory Pattern: 
 
<img src="../ConcreteFactory.png" width="600">







<a id = "observer">3. Observer Pattern Design Discussion</a>:
------------------------------------------------------------
 
The design of our <a href = https://refactoring.guru/design-patterns/observer>observer pattern</a> 
came in two deliverables that we will consider separately.

 
The first deliverable consisted of stand-alone code scattered throughout our program that performed the entirety of observer notifications. This design was great for testing how things worked and to determine if observers were being notified appropriately.  The downside to this was that it was messy and repetitive.  Each notification was embedded within another large chunk of code which caused for more complicated looking code than we prefered. Also, since all the notification types are very similar, there was a lot of code that was being repeated for every notification.

To fix this we did the following . . .
 
Our second deliverable solves all the problems that the first deliverable had.  An Observer class was created to handle all the creations and executions of observer notifications.  This allowed for only a single function call needed to be added to areas in the program that require an observer to be notified of an event. It also allows for all functions within the class to share repetitive code rather than doing it individually multiple times like what was being done before. The structure of our class is very simple with one function per notification type (scheduled, moving, enroute, delivered, idle) that would 
create the json object being sent to the observers.  Then they were all able to use the same Notify() function that iterated through all the observers and executed their OnEvent() function.  And finally in order to populate/manage the vector of observers used in Notify(), we had the AddObserver() and RemoveObserver() functions similar to Delivery_Simulation.


<img src="../observerPattern.png" width="400">







<a id = "routes">4. Design and Implementing the different routes </a>:
------------------------------------------------------------------

We have created three routes for our simulation: the beeline route, the smart path route, and the parabolic route. 

<b><a id = "beeline"> The Beeline Path Route: </a></b>

The beeline route is one of the strategies implemented by the strategy pattern; the Beeline class generates the route necessary for carriers to move in a beeline way. As of now, only the drone carriers can move in a beeline. More specifically, the drone will rise high enough above the buildings and move to its destination in a straight line. Thereafter, it'll lower down until it reaches its destination. Given the initial position of the drone and its final destination, which is either the package location or the customer location, there is enough information to generate the coordinates. The coordinates are as follows: the initial position, high enough above the initial position, high enough above the destination and the destination. We use a height of 350 above the two endpoints, which should be high enough not to collide with any buildings. In order to better visualize the beeline path, the observer pattern will generate a colored path in the simulation during the drone's flight.  

<img src="../beeline.png" width="800">

<b><a id = "smart"> The Smart Path Route: </a></b>

The smart path route utilizes the interface IGraph. IGraph represents a read only graph object. It contains a function named GetPath(source, destination), which when given a source and destination in the form of 3-element x,y,z vectors, the function will return a list of positions to traverse in-order, which avoids the geometry of the scene. The returned path includes the source and destination points. The GetPath function uses <a href = https://www.freecodecamp.org/news/dijkstras-shortest-path-algorithm-visual-introduction/>Dijkstra's algorithm</a> to find the shortest path. 

The observer pattern will trace the smart route if used. The smart route is used in both carrier classes, drone and robot, and is the only option for the robot class. To see all smart paths during the simulation go to the top right menu box and check the all routes box.


<img src="../smart.png" width="800">


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

<img src="../parabolic.png" width="800">

<b><a id = "strategy">Strategy Pattern:</a></b>

Choosing the route relies on our <a href = https://refactoring.guru/design-patterns/strategy/>strategy pattern</a>. The strategy pattern reads the carrier's picojson to see if a route is specified for use. If there is a specific route that needs to be used, the strategy pattern will return the path of that route. The path is returned as a vector of coordinates allowing our carrier to implement the movement by iterating through the vector of coordinates. 

A strategy pattern defines a family of algorithms, encapsulates each one, and then makes them interchangeable. It allows for the algorithms to be independent, which reduces coupling. The concrete classes in our strategy pattern are beeline, smart_path, and parabolic. These concrete classes inherit from our abstract strategy class which ensures interchangeability. The strategy class is called from each of the carriers (drone or robot), so the specific carrier will have a path associated with it. 

<img src="../strategyPattern.png" width="600">



<a id = "difficulties">5.Difficulties and Advice </a>
------------------------------------------------------------
There were several aspects of this iteration that were difficult: understanding parabolic movement, debugging random errors after refactoring the way the carrier moves and implementing the strategy pattern for the smart path. The biggest tip we all agree on is to plan better before actually coding, because diving right into to coding tends to generate more bugs. Taking down notes on the professor's lectures, lab resources and attending office hours were the most helpful strategies in progressing in our project. In addition, setting aside lots of time for debugging is especially useful because it is a difficult task. 


<a id = "team">6. Team Documentation</a>:
------------------------------------------------------------

Roles:
- Peter: Reporter
- Nakul: Development Lead
- Spencer: Project Manager
- Quentin: Scheduler

Meeting #1: 

For our first meeting, we decided to tackle the biggest challenges first.  Both Peter and Spencer worked together on the parabolic path. Nakul created a new carrier class for shared functionality between drones and robots.  Quentin fixed bugs with our smart path that were still causing problems from the previous deliverable.
 
Meeting #2: 
 
Our second meeting consisted of many large changes to our program.  It was at this time that Peter rebuilt the observer pattern into its own class.  Nakul completed the strategy pattern and solved some bugs with our beeline path.  Quentin implemented the battery functionality so that carriers deplete their batteries.  Spencer completed the parabolic path and modified it to fit with Nakul's implementation of the strategy pattern.
 
Meeting #3:
 
During our last team meeting before the submission deadline, we determined which documentation and testing tasks need to be accomplished. These were delegated based on which tasks each team member had previously completed.  For Peter, he was given the task of completing the testing and documentation on our design and implementation of the observers, as well as completing the team documentation.  Nakul was tasked with documenting the design of the beeline route and testing of the drone. Spencer completed the parabolic testing and design documentation.  
Finally, Quentin was in charge of smart path documentation and testing the robot.
 
*/
