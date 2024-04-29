#include "FCFSScheduler.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

FCFSScheduler::FCFSScheduler() : processTable() {}

void FCFSScheduler::displayTable(int idx1, int idx2, const ProcessTable& sortedTable, const std::vector<int>& doneProcesses) const {
    std::cout << "P | At | Et | Bt\n";
    for (int p = 0; p < doneProcesses.size(); p++) {
            std::cout << "P" << sortedTable[doneProcesses[p]].getProcessID() << " | " 
                      << sortedTable[doneProcesses[p]].getArrivalTime() << " | " 
                      << sortedTable[doneProcesses[p]].getExecutionTime() << " | " 
                      << sortedTable[doneProcesses[p]].getBurstTime() << " \n";
    }
    for (int p = idx1; p <= idx2; ++p) {
        std::cout << "P" << sortedTable[p].getProcessID() << " | "
                  << sortedTable[p].getArrivalTime() << " | "
                  << sortedTable[p].getExecutionTime() << " | "
                  << sortedTable[p].getBurstTime() << "\n";
    }
}

void FCFSScheduler::schedulerSim(const ProcessTable& table) {
    ProcessTable sortedTable = table;
    std::sort(sortedTable.begin(), sortedTable.end(), [](const Process& a, const Process& b) {
        return a.getArrivalTime() < b.getArrivalTime();
    });

    std::cout << "FCFS Scheduling Simulation: \n";

    int currentTime = 0, elapsedTime = 0, currentProcess = 0, lastExecProcess = 0;
    std::vector<int> doneProcesses;

    // Arrival of processes event
    for (int p = 0; p < sortedTable.size(); p++) {
        std::cout << "At P" << sortedTable[p].getProcessID() << " arrival: \n";
        if (!p) {
            displayTable(0, 0, sortedTable, doneProcesses);
        } else {
            elapsedTime = sortedTable[p].getArrivalTime() - currentTime;
            currentTime = sortedTable[p].getArrivalTime();
            
            // Update current process info
            sortedTable[currentProcess].setExecutionTime(sortedTable[currentProcess].getExecutionTime() + elapsedTime);
            displayTable(currentProcess, p, sortedTable, doneProcesses);

            // Check wether current process is done or not
            if (sortedTable[currentProcess].getExecutionTime() == sortedTable[currentProcess].getBurstTime()) {
                doneProcesses.push_back(currentProcess);
                lastExecProcess = currentProcess;
                currentProcess++;
            }
        }
    }

    // If any processes remain unexecuted
    if (sortedTable.size() != doneProcesses.size()) {
        for (int p = lastExecProcess + 1; p < sortedTable.size(); p++) {
            std::cout << "P" << sortedTable[p].getProcessID() << " executes: \n";

            elapsedTime = sortedTable[p].getBurstTime() - sortedTable[p].getExecutionTime();
            currentTime += elapsedTime;

            // Update current executing process info
            sortedTable[p].setExecutionTime(sortedTable[p].getExecutionTime() + elapsedTime);
            displayTable(p, sortedTable.size() - 1, sortedTable, doneProcesses);

            doneProcesses.push_back(currentProcess);
        }
    }
}

void FCFSScheduler::setProcessTable(const ProcessTable& table) {
    processTable = table;
}
