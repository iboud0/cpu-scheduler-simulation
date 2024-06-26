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
       if (std::find(doneProcesses.begin(), doneProcesses.end(), p) == doneProcesses.end()) {
            std::cout << "P" << sortedTable[p].getProcessID() << " | "
                    << sortedTable[p].getArrivalTime() << " | "
                    << sortedTable[p].getExecutionTime() << " | "
                    << sortedTable[p].getBurstTime() << "\n";
        }
    }
}

void FCFSScheduler::schedulerSim(const ProcessTable& table) {
    ProcessTable sortedTable = table;
    std::sort(sortedTable.begin(), sortedTable.end(), [](const Process& a, const Process& b) {
        return a.getArrivalTime() < b.getArrivalTime();
    });

    std::cout << "FCFS Scheduling Simulation: \n";

    int currentTime = 0, elapsedTime = 0, currentProcess = 0, lastExecProcess = 0, lastArrProcess;
    std::vector<int> doneProcesses;
    std::set<int> arrivedProcesses;

    // Arrival of processes event
    for (int p = 0; p < sortedTable.size(); p++) {
        if (sortedTable[p].getArrivalTime() == sortedTable[p + 1].getArrivalTime() && p != sortedTable.size() - 1) {
            arrivedProcesses.insert(p);
            lastArrProcess = p;
        } else {
            arrivedProcesses.insert(p);
            lastArrProcess = p;
            std::cout << "At ";
            for (auto it = arrivedProcesses.begin(); it != arrivedProcesses.end(); ++it) {
                int value = *it;
                std::cout << "P" << sortedTable[value].getProcessID() << " ";
            }
            std::cout << "arrival: \n";
            arrivedProcesses.clear();

            elapsedTime = sortedTable[p].getArrivalTime() - currentTime;
            currentTime = sortedTable[p].getArrivalTime();

            if (sortedTable[currentProcess].getExecutionTime() + elapsedTime < sortedTable[currentProcess].getBurstTime()) {
                // Update current process info
                sortedTable[currentProcess].setExecutionTime(sortedTable[currentProcess].getExecutionTime() + elapsedTime);
                displayTable(0, lastArrProcess, sortedTable, doneProcesses);
            } else if (sortedTable[currentProcess].getExecutionTime() + elapsedTime == sortedTable[currentProcess].getBurstTime()) {
                // Current process is done
                sortedTable[currentProcess].setExecutionTime(sortedTable[currentProcess].getExecutionTime() + elapsedTime);
                displayTable(0, lastArrProcess, sortedTable, doneProcesses);

                doneProcesses.push_back(currentProcess);
                lastExecProcess = currentProcess;
                currentProcess++;
            } else {
                // Current process is done and we have remaining time
                int remTime = sortedTable[currentProcess].getExecutionTime() + elapsedTime  - sortedTable[currentProcess].getBurstTime();

                sortedTable[currentProcess].setExecutionTime(sortedTable[currentProcess].getBurstTime());

                doneProcesses.push_back(currentProcess);
                lastExecProcess = currentProcess;
                currentProcess++;

                while (remTime != 0) {
                    if (remTime < sortedTable[currentProcess].getBurstTime()) {
                        sortedTable[currentProcess].setExecutionTime(sortedTable[currentProcess].getExecutionTime() + remTime);
                        remTime = 0;
                    } else if (remTime == sortedTable[currentProcess].getBurstTime()) {
                        sortedTable[currentProcess].setExecutionTime(sortedTable[currentProcess].getExecutionTime() + remTime);

                        doneProcesses.push_back(currentProcess);
                        lastExecProcess = currentProcess;
                        remTime = 0;
                        currentProcess++;
                    } else {
                        sortedTable[currentProcess].setExecutionTime(sortedTable[currentProcess].getBurstTime());

                        doneProcesses.push_back(currentProcess);
                        lastExecProcess = currentProcess;
                        remTime -= sortedTable[currentProcess].getBurstTime();
                        currentProcess++;
                    }
                    
                }

                displayTable(0, lastArrProcess, sortedTable, doneProcesses);
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
