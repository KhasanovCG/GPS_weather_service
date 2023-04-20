// ROS service client node
#include <ros/ros.h>
#include <my_custom_msgs/WeatherStatus.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "weather_client");
  ros::NodeHandle nh;

  // create a client for the weather service
  ros::ServiceClient client = nh.serviceClient<my_custom_msgs::WeatherStatus>("weather_service");

  // create a service request with GPS location
  my_custom_msgs::WeatherStatus srv;
  srv.request.latitude = 37.7749;  // example latitude
  srv.request.longitude = -122.4194;  // example longitude

  // call the weather service and print the response
  if (client.call(srv))
  {
    ROS_INFO("Weather status: %s", srv.response.status.c_str());
  }
  else
  {
    ROS_ERROR("Failed to call weather service");
    return 1;
  }

  return 0;
}
