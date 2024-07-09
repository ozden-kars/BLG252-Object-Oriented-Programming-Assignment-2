#include "../include/unit.hpp"


Unit::Unit(std::string name, float cost_per_day, float base_return_per_day){
    m_name = name;
    m_cost_per_day = cost_per_day;
    m_base_return_per_day = base_return_per_day;
};

std::string Unit::getName() const{
    return m_name;
};

float Unit::getCostPerDay() const{
    return  m_cost_per_day;
};

float Unit::getReturnPerDay() const{
    return m_base_return_per_day;
};