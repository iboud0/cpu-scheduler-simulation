#include "RRScheduler.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>

RRScheduler::RRScheduler() : processTable(), quant(0.1f) {}

void RRScheduler::displayTable(int idx1, int idx2, const ProcessTable& sortedTable, const std::vector<int>& doneProcesses) const {
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

void RRScheduler::schedulerSim(const ProcessTable& table, float timeQuantum) {
    ProcessTable sortedTable = table;
    std::sort(sortedTable.begin(), sortedTable.end(), [](const Process& a, const Process& b) {
        return a.getArrivalTime() < b.getArrivalTime();
    });
    float q = timeQuantum;
    std::queue<int> readyQ;
    std::vector<int> doneProcesses;

    std::cout << "Round Robin Scheduling Simulation:\n";

    int currentTime = 0, currentProcess = 0, lastArrProcess, flag = 0;
    std::set<int> arrivedProcesses;
    // First processes to arrive
    for (int p = 0; p < sortedTable.size(); p++) {
        if (sortedTable[p].getArrivalTime() == sortedTable[p + 1].getArrivalTime() && p != sortedTable.size() - 1) {
            arrivedProcesses.insert(p);
            lastArrProcess = p;
            readyQ.push(p);
        } else {
            arrivedProcesses.insert(p);
            lastArrProcess = p;
            readyQ.push(p);
            break;
        }
    }

    for (auto it = arrivedProcesses.begin(); it != arrivedProcesses.end(); ++it) {
        int value = *it;
        std::cout << "P" << sortedTable[value].getProcessID() << " ";
    }
    std::cout << "arrive: \n";
    displayTable(0, lastArrProcess, sortedTable, doneProcesses);
    arrivedProcesses.clear();

    while (!readyQ.empty() && doneProcesses.size() != sortedTable.size()) {
        currentTime += q;
        currentProcess = readyQ.front();
        readyQ.pop();

        // Check the arrival of processes during the current time quantum
        for (int p = lastArrProcess + 1; p < sortedTable.size(); p++) {
            if (sortedTable[p].getArrivalTime() <= currentTime) {
                readyQ.push(p);
                lastArrProcess = p;
                arrivedProcesses.insert(p);
            } else {
                break;
            }
        }

        // Execute current process & check wether it's done or not
        if (sortedTable[currentProcess].getExecutionTime() + q < sortedTable[currentProcess].getBurstTime()) {
            sortedTable[currentProcess].setExecutionTime(sortedTable[currentProcess].getExecutionTime() + q);
            readyQ.push(currentProcess);
        } else if (sortedTable[currentProcess].getExecutionTime() + q == sortedTable[currentProcess].getBurstTime()){
            sortedTable[currentProcess].setExecutionTime(sortedTable[currentProcess].getBurstTime());
            doneProcesses.push_back(currentProcess);
            flag = 1;
        } else {
            sortedTable[currentProcess].setExecutionTime(sortedTable[currentProcess].getBurstTime());
            doneProcesses.push_back(currentProcess);
            flag = 1;
            currentTime -= sortedTable[currentProcess].getExecutionTime() + q - sortedTable[currentProcess].getBurstTime();
        }

        // Display process table depending on what event happend
        if (!arrivedProcesses.empty()) {
            if (flag) {
                // Processes arrived & current process is done executing
                std::cout << "P" << sortedTable[currentProcess].getProcessID() << " executes ";
                for (auto it = arrivedProcesses.begin(); it != arrivedProcesses.end(); ++it) {
                    int value = *it;
                    std::cout << "P" << sortedTable[value].getProcessID() << " ";
                }
                std::cout << "arrive: \n";
                displayTable(0, lastArrProcess, sortedTable, doneProcesses);
                flag = 0;
                arrivedProcesses.clear();
            } else {
                // Processes arrived & current process is not yet done executing
                for (auto it = arrivedProcesses.begin(); it != arrivedProcesses.end(); ++it) {
                    int value = *it;
                    std::cout << "P" << sortedTable[value].getProcessID() << " ";
                }
                std::cout << "arrive: \n";
                displayTable(0, lastArrProcess, sortedTable, doneProcesses);
                arrivedProcesses.clear();
            }
        } else {
            if (flag) {
                std::cout << "P" << sortedTable[currentProcess].getProcessID() << " executes: \n";
                displayTable(0, lastArrProcess, sortedTable, doneProcesses);
                flag = 0;
            } else {
                continue;
            }
        }
    }

}

void RRScheduler::setProcessTable(const ProcessTable& table) {
    processTable = table;
}
