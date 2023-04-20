// ROS service server node
#include <ros/ros.h>
#include <my_custom_msgs/WeatherStatus.h>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>

// callback function for the weather service
bool getWeatherStatus(my_custom_msgs::WeatherStatus::Request &req, my_custom_msgs::WeatherStatus::Response &res)
{
  // create the URL for the OpenWeatherMap API call
  std::string url = "http://api.openweathermap.org/data/2.5/weather?lat=" +
    std::to_string(req.latitude) + "&lon=" + std::to_string(req.longitude) +
    "&appid=YOUR_API_KEY&units=metric";

  // send the API call using libcurl
  CURL *curl = curl_easy_init();
  if (curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);

    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, static_cast<size_t (*)(char *, size_t, size_t, void *)>(
      [](char *ptr, size_t size, size_t nmemb, void *userdata) -> size_t {
        reinterpret_cast<std::string *>(userdata)->append(ptr, size * nmemb);
        return size * nmemb;
      }));
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res == CURLE_OK)
    {
      // parse the JSON response
      Json::Value root;
      Json::Reader reader;
      if (reader.parse(response, root))
      {
        // extract the weather status from the response
        std::string status = root["weather"][0]["description"].asString();
        res.status = status;
        return true;
      }
    }
  }

  ROS_ERROR("Failed to get weather status");
  return false;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "weather_server");
  ros::NodeHandle nh;

  // create a service for the weather status
  ros::ServiceServer service = nh.advertiseService("weather_service", getWeatherStatus);

  ROS_INFO("Ready to get weather status");
  ros::spin();

  return 0;
}
