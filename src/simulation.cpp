#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib> // std::srand
#include <vector>
#include <string>

#include "../include/simulation.hpp"
#include "../include/worker.hpp"
#include "../include/machine.hpp"

using namespace std;

Simulation::Simulation(Factory &factory, int total_days, std::string workers_list_path, std::string machines_list_path){
    m_total_days = total_days;
    m_factory = &factory;
    //creating m_labor_market
    std::ifstream file(workers_list_path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
    }

    std::string line;
    getline(file,line);
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name;
        float cost_per_day, base_return_per_day;
        if (iss >> name >> cost_per_day >> base_return_per_day) {
            m_labor_market.emplace_back(name, cost_per_day, base_return_per_day);
        } else {
            std::cerr << "Failed to parse line: 1" << line << std::endl;
        }
    }
    file.close();
    
    //creating m_machines_market
    std::ifstream file1(machines_list_path);
    if (!file1.is_open()) {
        std::cerr << "Failed to open file1." << std::endl;
    }

    std::string line1;
    getline(file1,line1);
    while (std::getline(file1, line1)) {
        std::istringstream iss(line1);
        std::string name;
        float price, daily_cost, daily_return,fail_prob, repair_cost;
        int repair_time;
        if (iss >> name >> price >> daily_cost >> daily_return >> fail_prob >> repair_cost >> repair_time) {
            m_machines_market.emplace_back(name,price,daily_cost,daily_return,fail_prob,repair_time,repair_cost);
        } else {
            std::cerr << "Failed to parse line: 2" << line << std::endl;
        }
    }
    file1.close();
};

Machine Simulation::buyRandomMachine(){
    int index = std::rand() % m_machines_market.size();
    Machine choosen = m_machines_market[index];
    m_machines_market.erase(m_machines_market.begin() + index);
    m_factory->addUnit(choosen);
    return choosen;
};

Worker Simulation::hireRandomWorker(){
    int index = std::rand() % m_labor_market.size();
    Worker choosen = m_labor_market[index];
    m_labor_market.erase(m_labor_market.begin() + index);
    m_factory->addUnit(choosen);
    return choosen;
};

void Simulation::printWelcomeMessage() const
{
    cout << "Welcome to the Car Factory!" << endl;
    cout << "You have " << m_total_days << " days to make as much money as possible" << endl;
    cout << "You can add workers, machines, and fast forward days" << endl;

    cout << "Available commands:" << endl;
    cout << "    wX: adds X workers" << endl;
    cout << "    mX: adds X machines" << endl;
    cout << "    pX: passes X days" << endl;
    cout << "    q: exit the game properly" << endl;
}

void Simulation::run(){
    string command = "b";
    int day;
    int worker_number;
    int machine_number;
    int passed_days = 0;
    float current_capital = m_factory->getCapital();
    float initial_capital = m_factory->getCapital();
 
    while(command[0] != 'q'){
        cout <<"Enter command: ";
        cin >> command;
        std::stringstream ss;
        if (command[0] == 'w') {
            ss << command.substr(1);
            ss >> worker_number;
            current_capital = m_factory->getCapital();
            for (int i = 1; i <= worker_number; i++) {
                if (!m_factory->isBankrupt()) {
                    Worker worker = hireRandomWorker();
                    current_capital -= worker.getCostPerDay();  
                    if (current_capital <= 0) {
                        printf("You went bankrupt!\r\n");
                        command = "q";
                        break;
                    }
                } else {
                    printf("You went bankrupt!\r\n");
                    command = "q";
                    break;
                }
            }
        }

        else if(command[0] == 'm'){
            ss << command.substr(1);
            ss >> machine_number;
            current_capital = m_factory->getCapital();
            for(int i = 1; i<=machine_number;i++){
                if(!m_factory->isBankrupt()){
                    Machine machine = buyRandomMachine();
                    current_capital -= machine.getCostPerDay();
                    if (current_capital <= 0) {
                        printf("You went bankrupt!\r\n");
                        command = "q";
                        break;
                    }
                }    
                else{
                    printf("You went bankrupt!\r\n");
                    command = "q";
                    break;
                }
            }
        }
        
        else if(command[0] == 'p'){
            ss << command.substr(1);
            ss >> day;
            for(int i = 1; i<=day; i++){
                if(passed_days >= m_total_days){
                    printf("Congrats! You have earned %.0f in %d days",(m_factory->getCapital() - initial_capital),m_total_days);
                    command = "q";
                    break;
                }
                m_factory->passOneDay();
                passed_days++;
                if(!m_factory->isBankrupt()){
                    printf("--- Day: %d\r\n",passed_days);
                    printf("\\[C: %.3f, W: %d, M: %d, HW: %d\\]\r\n",m_factory->getCapital(),m_factory->getWorkerCount(),m_factory->getMachineCount(),m_factory->getHeadWorkerCount());
                } else {
                    printf("You went bankrupt!\r\n");
                    command = "q";
                    break;
                }
            }
        }
   
        else if (command[0] == 'q'){
            if(m_factory->isBankrupt()){
                printf("You went bankrupt!\r\n");
                command = "q";
                break;
            }
            else{
                printf("Congrats! You have earned %.0f in %d days",(m_factory->getCapital()- initial_capital),passed_days);
                command = "q";
                break;
            }
        }
    }
}
