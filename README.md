ROS Weather Service
The ROS Weather Service is a simple ROS package that consists of a ROS service client node and a ROS service server node. The client node sends the GPS location of the autonomous vehicle to the server node, 
which retrieves the current weather status using the OpenWeatherMap API and sends it back to the client node.\

  Dependencies
This package has the following dependencies:

ROS noetic
'curl' library
'jsoncpp' library


  Installation

1. Clone the package to your ROS workspace:
cd ~/catkin_ws/src
git clone https://github.com/example/ros-weather-service.git


2.Install the curl and jsoncpp libraries:
sudo apt-get install libcurl4-openssl-dev libjsoncpp-dev


3.Build the package:
cd ~/catkin_ws
catkin_make



    Usage
To use the ROS Weather Service:

1.Launch the server node:
roslaunch ros_weather_service server.launch
//This will launch the server node and start listening for requests on the '/weather_service' service.


2.Launch the client node:
roslaunch ros_weather_service client.launch
//This will launch the client node, which will send a request to the server node with a GPS location (latitude and longitude). 
//The server node will retrieve the current weather status based on the GPS location and send it back to the client node. The client node will then print the weather status to the console.
//Note: You may need to modify the GPS location in the client node to match the location of our autonomous vehicle.


   Configuration

The ROS Weather Service can be configured by modifying the following files:

---'ros_weather_service/server/src/weather_server.cpp': This file contains the 
implementation of the server node, which retrieves the weather status using the
OpenWeatherMap API. You can modify the API key or the units of measurement used 
in the API call by modifying the 'url' variable in the 'getWeatherStatus()' function.
---'ros_weather_service/client/src/weather_client.cpp': This file contains the 
implementation of the client node, which sends a request to the server node with a GPS location.
You can modify the GPS location by modifying the 'latitude' and 'longitude' 
variables in the 'main()' function.

