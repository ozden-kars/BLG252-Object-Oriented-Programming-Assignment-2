#include "../include/machine.hpp"

Machine::Machine(std::string name, float price, float cost_per_day, float base_return_per_day, float failure_probability, int repair_time, float repair_cost)
:Unit(name,cost_per_day,base_return_per_day){
    m_failure_probability = failure_probability;
    m_price = price;
    m_repair_time = repair_time;
    m_repair_cost = repair_cost;
    m_days_until_repair = 0;
};

float Machine::getReturnPerDay(){ // m_days_until_return nasıl azalacak
    if(m_days_until_repair > 0){ // Check if the machine is currently broken. If so, return 0.
        m_days_until_repair--;
        if(m_days_until_repair < 0){
            m_days_until_repair = 0;
        }
        return 0;
    } else {
        if((static_cast<float>(rand()) / RAND_MAX) >= m_failure_probability){  // wiil it fail ??
            m_days_until_repair = m_repair_time;
            return -m_repair_cost;
        } else{
            return Unit::getReturnPerDay();
        } 
     }
};

float Machine::getPrice() const{
    return m_price;
}