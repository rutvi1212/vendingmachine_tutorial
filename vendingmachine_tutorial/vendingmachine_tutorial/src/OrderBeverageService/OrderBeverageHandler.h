#ifndef VENDING_MACHINE_MICROSERVICES_ORDERBEVERAGEHANDLER_H
#define VENDING_MACHINE_MICROSERVICES_ORDERBEVERAGEHANDLER_H

#include <iostream>
#include <string>
#include <regex>
#include <future>

#include "../../gen-cpp/OrderBeverageService.h"
#include "../../gen-cpp/WeatherService.h"
#include "../../gen-cpp/BeveragePreferenceService.h"

#include "../ClientPool.h"
#include "../ThriftClient.h"
#include "../logger.h"

namespace vending_machine{

class OrderBeverageServiceHandler : public OrderBeverageServiceIf {
 public:
  OrderBeverageServiceHandler(
		  ClientPool<ThriftClient<WeatherServiceClient>> *,ClientPool<ThriftClient<BeveragePreferenceServiceClient>> *) ;
  ~OrderBeverageServiceHandler() override=default;

  void PlaceOrder(std::string& _return, const int64_t city) override;
 private:
  ClientPool<ThriftClient<WeatherServiceClient>> *_weather_client_pool;
  ClientPool<ThriftClient<BeveragePreferenceServiceClient>> *_beverage_preference_client_pool;
};

// Constructor
OrderBeverageServiceHandler::OrderBeverageServiceHandler(ClientPool<ThriftClient<WeatherServiceClient>>*weather_client_pool,
					ClientPool<ThriftClient<BeveragePreferenceServiceClient>>*beverage_preference_client_pool) {

     // Storing the clientpool
     _weather_client_pool = weather_client_pool;
     _beverage_preference_client_pool = beverage_preference_client_pool;
}

// Remote Procedure "PlaceOrder"
void OrderBeverageServiceHandler::PlaceOrder(std::string& _return, const int64_t city){
     // Your implementation goes here
     printf("PlaceOrder\n");

     //return BeverageType::type::COLD;
#if 1   
    // 1. get the weather service client pool
    auto weather_client_wrapper = _weather_client_pool->Pop();
    if (!weather_client_wrapper) {
      ServiceException se;
      se.errorCode = ErrorCode::SE_THRIFT_CONN_ERROR;
      se.message = "Failed to connect to weather-service";
      throw se;
    }
    auto weather_client = weather_client_wrapper->GetClient();
    
    auto beverage_preference_client_wrapper = _beverage_preference_client_pool->Pop();
    if (!beverage_preference_client_wrapper) {
      ServiceException se;
      se.errorCode = ErrorCode::SE_THRIFT_CONN_ERROR;
      se.message = "Failed to connect to Beverage-Preference-Service";
      throw se;
    }
    auto beverage_preference_client = beverage_preference_client_wrapper->GetClient();

    // by default get cold
    WeatherType::type weatherType = WeatherType::type::COLD;
    BeverageType::type Beverage = BeverageType::type::HOT;
    std::string b;
    // 2. call the remote procedure : GetWeather
    try {
      weatherType = weather_client->GetWeather(city);
    } catch (...) {
      _weather_client_pool->Push(weather_client_wrapper);
      LOG(error) << "Failed to send call GetWeather to weather-client";
      throw;
    }
    _weather_client_pool->Push(weather_client_wrapper);
    
    if(weatherType == WeatherType::type::WARM){
    Beverage = BeverageType::type::COLD;
    try {
      beverage_preference_client->GetBeverage(b,Beverage);
    } catch (...) {
      _beverage_preference_client_pool->Push(beverage_preference_client_wrapper);
      LOG(error) << "Failed to send call GetWeather to beverage-preference-client";
      throw;
    }
    _beverage_preference_client_pool->Push(beverage_preference_client_wrapper);
    _return = b;
    }
    
    else{
        Beverage = BeverageType::type::HOT;
     try {
      beverage_preference_client->GetBeverage(b,Beverage);
    } catch (...) {
      _beverage_preference_client_pool->Push(beverage_preference_client_wrapper);
      LOG(error) << "Failed to send call GetWeather to beverage-preference-client";
      throw;
    }
    _beverage_preference_client_pool->Push(beverage_preference_client_wrapper);
    _return = b;
    }
    
    
   // 3. business logic
  /* if(weatherType == WeatherType::type::WARM)
	_return = b;//BeverageType::type::COLD;
   else
	   _return = b;//BeverageType::type::HOT;*/
#endif
}

} // namespace vending_machine


#endif //VENDING_MACHINE_MICROSERVICES_ORDERBEVERAGEHANDLER_H

