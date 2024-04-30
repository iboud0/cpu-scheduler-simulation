#include "SJFScheduler.h"
#include <iostream>
#include <algorithm>
#include <set>

SJFScheduler::SJFScheduler() : processTable() {}

void SJFScheduler::displayTable(int idx1, int idx2, const ProcessTable& sortedTable, const std::vector<int>& doneProcesses) const {
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

void SJFScheduler::schedulerSim(const ProcessTable& table) {
    ProcessTable sortedTable = table;
    std::sort(sortedTable.begin(), sortedTable.end(), [](const Process& a, const Process& b) {
        if (a.getArrivalTime() == b.getArrivalTime()) {
            // If arrival times are equal, sort by burst time
            return a.getBurstTime() < b.getBurstTime();
        } else {
            return a.getArrivalTime() < b.getArrivalTime();
        }
    });

    std::cout << "SJF Scheduling Simulation: \n";

    int currentTime = 0, elapsedTime = 0, currentProcess = 0, lastExecProcess = 0, lastArrProcess;
    std::vector<int> doneProcesses;
    std::set<int> arrivedProcesses;
    std::vector<int> availableProcesses;

    // Arrival of processes event
    for (int p = 0; p < sortedTable.size(); p++) {
        if (sortedTable[p].getArrivalTime() == sortedTable[p + 1].getArrivalTime() && p != sortedTable.size() - 1) {
            arrivedProcesses.insert(p);
            availableProcesses.push_back(p);
            lastArrProcess = p;
        } else {
            arrivedProcesses.insert(p);
            availableProcesses.push_back(p);
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

                // Deleting the executed process from available processes vector
                int valueToBeDeleted = currentProcess;
                auto it = find(availableProcesses.begin(), availableProcesses.end(), valueToBeDeleted);
                if (it != availableProcesses.end()) {
                    availableProcesses.erase(it);
                }

                std::sort(availableProcesses.begin(), availableProcesses.end(), [&](int a, int b) {
                    return sortedTable[a].getBurstTime() < sortedTable[b].getBurstTime();
                });

                currentProcess = availableProcesses[0];
            } else {
                // Current process is done and we have remaining time
                int remTime = sortedTable[currentProcess].getExecutionTime() + elapsedTime  - sortedTable[currentProcess].getBurstTime();

                sortedTable[currentProcess].setExecutionTime(sortedTable[currentProcess].getBurstTime());

                doneProcesses.push_back(currentProcess);
                lastExecProcess = currentProcess;

                // Deleting the executed process from available processes vector
                int valueToBeDeleted = currentProcess;
                auto it = find(availableProcesses.begin(), availableProcesses.end(), valueToBeDeleted);
                if (it != availableProcesses.end()) {
                    availableProcesses.erase(it);
                }

                std::sort(availableProcesses.begin(), availableProcesses.end(), [&](int a, int b) {
                    return sortedTable[a].getBurstTime() < sortedTable[b].getBurstTime();
                });

                int temp = 0;
                currentProcess = availableProcesses[temp];

                while (remTime != 0) {
                    if (remTime < sortedTable[currentProcess].getBurstTime()) {
                        sortedTable[currentProcess].setExecutionTime(sortedTable[currentProcess].getExecutionTime() + remTime);
                        remTime = 0;
                    } else if (remTime == sortedTable[currentProcess].getBurstTime()) {
                        sortedTable[currentProcess].setExecutionTime(sortedTable[currentProcess].getExecutionTime() + remTime);

                        doneProcesses.push_back(currentProcess);
                        lastExecProcess = currentProcess;

                        int valueToBeDeleted = currentProcess;
                        auto it = find(availableProcesses.begin(), availableProcesses.end(), valueToBeDeleted);
                        if (it != availableProcesses.end()) {
                            availableProcesses.erase(it);
                        }

                        remTime = 0;
                        currentProcess = availableProcesses[temp++];
                    } else {
                        sortedTable[currentProcess].setExecutionTime(sortedTable[currentProcess].getBurstTime());

                        doneProcesses.push_back(currentProcess);
                        lastExecProcess = currentProcess;

                        int valueToBeDeleted = currentProcess;
                        auto it = find(availableProcesses.begin(), availableProcesses.end(), valueToBeDeleted);
                        if (it != availableProcesses.end()) {
                            availableProcesses.erase(it);
                        }

                        remTime -= sortedTable[currentProcess].getBurstTime();
                        currentProcess = availableProcesses[temp++];
                    }
                    
                }

                displayTable(0, lastArrProcess, sortedTable, doneProcesses);
            }
        }
    }

    // If any processes remain unexecuted
    if (!availableProcesses.empty()) {
        std::sort(availableProcesses.begin(), availableProcesses.end(), [&](int a, int b) {
            return sortedTable[a].getBurstTime() < sortedTable[b].getBurstTime();
        });

        for (int p = 0; p < availableProcesses.size(); p++) {
            std::cout << "P" << sortedTable[availableProcesses[p]].getProcessID() << " executes: \n";

            elapsedTime = sortedTable[availableProcesses[p]].getBurstTime() - sortedTable[availableProcesses[p]].getExecutionTime();
            currentTime += elapsedTime;

            // Update current executing process info
            sortedTable[availableProcesses[p]].setExecutionTime(sortedTable[availableProcesses[p]].getExecutionTime() + elapsedTime);
            displayTable(availableProcesses[p], sortedTable.size() - 1, sortedTable, doneProcesses);

            doneProcesses.push_back(currentProcess);
        }
    }
}

void SJFScheduler::setProcessTable(const ProcessTable& table) {
    processTable = table;
}
