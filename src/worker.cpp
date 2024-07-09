#include "../include/worker.hpp"

Worker::Worker(std::string name, float cost_per_day, float base_return_per_day):Unit(name,cost_per_day,base_return_per_day)
{};

float Worker::getReturnPerDay(){
    if (m_experience == 10){
        increaseHeadWorkerCount();
    }
    float returnperday = Unit::getReturnPerDay() + (m_experience *2) + (m_num_head_workers*3);
    m_experience++;
    return returnperday;
}

int Worker::getExperience() const{
    return m_experience;
}

void Worker::increaseHeadWorkerCount(){
    m_num_head_workers++;
}