#ifndef VENDING_MACHINE_MICROSERVICES_BEVERAGEPREFERENCEHANDLER_H
#define VENDING_MACHINE_MICROSERVICES_BEVERAGEPREFERENCEHANDLER_H

#include <iostream>
#include <string>
#include <regex>
#include <future>

#include "../../gen-cpp/BeveragePreferenceService.h"

#include "../ClientPool.h"
#include "../ThriftClient.h"
#include "../logger.h"

#include <vector>
#include <random>

namespace vending_machine{

class BeveragePreferenceServiceHandler : public BeveragePreferenceServiceIf {
 public:
  BeveragePreferenceServiceHandler();
  ~BeveragePreferenceServiceHandler() override=default;

  void GetBeverage(std::string& _return,BeverageType::type b) override;
};

// Constructor
BeveragePreferenceServiceHandler::BeveragePreferenceServiceHandler() {

}


void BeveragePreferenceServiceHandler::GetBeverage(std::string& _return,BeverageType::type b) {
     // Your implementation goes here
     std::vector<std::string> hot_beverage = {"latte", "cappuccino", "espresso"};
     std::vector<std::string> cold_beverage = {"lemonade", "ice-tea", "soda"};
     std::random_device rd;
     std::mt19937 gen(rd());
     
     std::uniform_int_distribution<> dist(0,hot_beverage.size()-1);
     int index = dist(gen);
     
     std::string random_hot_drink = hot_beverage[index];
     std::string random_cold_drink = cold_beverage[index];

    if(b == BeverageType::type::HOT){
    	_return=random_hot_drink ; 
    }
    else
    	_return=random_cold_drink ;
}

} // namespace vending_machine


#endif //VENDING_MACHINE_MICROSERVICES_BEVERAGEPREFERENCEHANDLER_H

