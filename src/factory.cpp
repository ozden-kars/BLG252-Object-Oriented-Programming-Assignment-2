#include "../include/factory.hpp"


Factory::Factory(float capital){
    m_capital = capital;
    m_is_bankrupt =false;
};

void Factory::passOneDay(){
    if (!m_workers.empty() || !m_machines.empty()){
        for (auto& worker : m_workers){ // Promotion begin
            bool found = false;
            for(auto& hworker : m_head_workers){
                if (worker.getName() == hworker.getName()){
                    found = true;
                    break;
                }
            }
            if (!found && worker.getExperience() >= 10){
                HeadWorker new_headworker(worker);
                m_head_workers.push_back(new_headworker);
                printf("%s is promoted\r\n",worker.getName().c_str()); // Promotion end
            }
        }
        
        for (auto& worker : m_workers){ // calculating capital begin
            if(worker.getExperience() < 10){
                m_capital -= worker.getCostPerDay();
                m_capital += worker.getReturnPerDay();
            }
        }
        for (auto& hworker : m_head_workers){
            m_capital -= hworker.getCostPerDay();
            m_capital += hworker.getReturnPerDay();
        }

        for(auto& machine: m_machines){
            m_capital -= machine.getCostPerDay();
            m_capital += machine.getReturnPerDay(); // calculating capital end
        }
    }
};

void Factory::addUnit(const Worker &rhs_worker){
    m_workers.push_back(rhs_worker);
    printf("%s is hired\r\n",rhs_worker.getName().c_str());
};

void Factory::addUnit(const Machine &rhs_machine){
    m_machines.push_back(rhs_machine);
    m_capital -= rhs_machine.getPrice();
    printf("%s is bought\r\n",rhs_machine.getName().c_str());
};

bool Factory::isBankrupt() const{
    return (m_capital < 0 );
};

float Factory::getCapital() const{
    return m_capital;
};

int Factory::getWorkerCount() const{
    return m_workers.size() - m_head_workers.size();
};

int Factory::getMachineCount() const{
    return m_machines.size();
};

int Factory::getHeadWorkerCount() const{
    return m_head_workers.size();
};