#ifndef VENDING_MACHINE_MICROSERVICES_WEATHERHANDLER_H
#define VENDING_MACHINE_MICROSERVICES_WEATHERHANDLER_H

#include <iostream>
#include <string>
#include <regex>
#include <future>

#include "../../gen-cpp/WeatherService.h"

#include "../ClientPool.h"
#include "../ThriftClient.h"
#include "../logger.h"

namespace vending_machine{

class WeatherServiceHandler : public WeatherServiceIf {
 public:
  WeatherServiceHandler();
  ~WeatherServiceHandler() override=default;

  WeatherType::type GetWeather(const int64_t city) override;
};

// Constructor
WeatherServiceHandler::WeatherServiceHandler() {

}

// Remote Procedure "PlaceOrder"

WeatherType::type WeatherServiceHandler::GetWeather(const int64_t city) {
     // Your implementation goes here
     printf("GetWeather even odd\n");

    // even odd select a weather
    //return ((city%2) == 0)? WeatherType::type::COLD : WeatherType::type::WARM;
    if((city%2) == 0){
    	return(WeatherType::type::COLD);
    }
    else{
    	return(WeatherType::type::WARM);
    }
}

} // namespace vending_machine


#endif //VENDING_MACHINE_MICROSERVICES_WEATHERHANDLER_H

