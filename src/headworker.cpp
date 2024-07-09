#include "../include/headworker.hpp"

HeadWorker::HeadWorker(Worker &worker):Worker{worker} {};

float HeadWorker::getReturnPerDay(){
    float returnperday = Unit::getReturnPerDay() + (m_experience * 5);
    m_experience++;
    return returnperday;
}