#include <iostream>
#include "Process.h"
#include "ProcessTable.h"

int main() {
    ProcessTable processTable;

    processTable.addProcess(Process(1, 0, 10));
    processTable.addProcess(Process(2, 2, 5)); 
    processTable.addProcess(Process(3, 4, 8));

    std::cout << "Number of processes in the table: " << processTable.size() << std::endl;
    std::cout << "Processes in the table:" << std::endl;
    for (const auto& process : processTable) {
        std::cout << "Process ID: " << process.getProcessID()
                  << ", Arrival Time: " << process.getArrivalTime()
                  << ", Burst Time: " << process.getBurstTime() << std::endl;
    }

    return 0;
}
