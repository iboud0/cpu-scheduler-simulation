#include "FCFSScheduler.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

FCFSScheduler::FCFSScheduler() : processTable() {}

void FCFSScheduler::schedulerSim(const ProcessTable& table) {
    ProcessTable sortedTable = table;
    std::sort(sortedTable.begin(), sortedTable.end(), [](const Process& a, const Process& b) {
        return a.getArrivalTime() < b.getArrivalTime();
    });

    std::cout << "FCFS Scheduling Simulation: \n";

    int currentProcess = 0;
    std::vector<int> doneProcesses;
    int elapsedTime, pExecTime;
    while ((currentProcess + 1) != sortedTable.size() + 1) {
        std::cout << "At P" << sortedTable[currentProcess].getProcessID() << " arrival: \n";
        std::cout << "P | At | Et | Bt \n";
        if (currentProcess != 0) {
            elapsedTime = sortedTable[currentProcess].getArrivalTime() - sortedTable[currentProcess - 1].getArrivalTime();
        }

        for (int p = 0; p < doneProcesses.size(); p++) {
            std::cout << "P" << sortedTable[doneProcesses[p]].getProcessID() << " | " << sortedTable[doneProcesses[p]].getArrivalTime() << " | " << sortedTable[doneProcesses[p]].getExecutionTime() << " | " << sortedTable[doneProcesses[p]].getBurstTime() << " \n";
        }

        for (int p = 0; p < currentProcess; p++) {
            auto it = std::find(doneProcesses.begin(), doneProcesses.end(), p);
            if (it != doneProcesses.end()) {
                continue;
            } else {
                pExecTime = sortedTable[p].getExecutionTime() + elapsedTime;
                sortedTable[p].setExecutionTime(pExecTime);
                std::cout << "P" << sortedTable[p].getProcessID() << " | " << sortedTable[p].getArrivalTime() << " | " << sortedTable[p].getExecutionTime() << " | " << sortedTable[p].getBurstTime() << " \n";
                if (pExecTime == sortedTable[p].getBurstTime()) {
                    doneProcesses.push_back(p);
                }
            }
        }
        std::cout << "P" << sortedTable[currentProcess].getProcessID() << " | " << sortedTable[currentProcess].getArrivalTime() << " | " << sortedTable[currentProcess].getExecutionTime() << " | " << sortedTable[currentProcess].getBurstTime() << " \n";
        currentProcess++;
    }

    std::vector<std::pair<int, int>> finalExec;
    for (int p = 0; p < currentProcess; p++) {
        auto it = std::find(doneProcesses.begin(), doneProcesses.end(), p);
        if (it != doneProcesses.end()) {
            continue;
        } else {
            std::pair<int, int> temp = std::make_pair(p, sortedTable[p].getBurstTime() - sortedTable[p].getExecutionTime());
            finalExec.push_back(temp);
        }
    }

    auto compareSecond = [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second < b.second;
    };

    std::sort(finalExec.begin(), finalExec.end(), compareSecond);

    int it = 0, prevRemBurst = 0;
    std::set<std::pair<int, int>> temp;
    while (it != finalExec.size()) {
        std::cout << it << " \n";
        temp.insert(finalExec[it]);
        if (finalExec[it + 1].second == finalExec[it].second) {
            it++;
        } else {
            if (temp.size() == 1) {
                auto it_ = temp.begin();
                std::cout << "P" << sortedTable[it_->first].getProcessID() << " finishes: \n";
                std::cout << "P | At | Et | Bt \n";
                elapsedTime = it_->second - prevRemBurst;
                prevRemBurst = it_->second;

                for (int p = 0; p < doneProcesses.size(); p++) {
                    std::cout << "P" << sortedTable[doneProcesses[p]].getProcessID() << " | " << sortedTable[doneProcesses[p]].getArrivalTime() << " | " << sortedTable[doneProcesses[p]].getExecutionTime() << " | " << sortedTable[doneProcesses[p]].getBurstTime() << " \n";
                }

                for (int p = 0; p < currentProcess; p++) {
                    auto it = std::find(doneProcesses.begin(), doneProcesses.end(), p);
                    if (it != doneProcesses.end()) {
                        continue;
                    } else {
                        pExecTime = sortedTable[p].getExecutionTime() + elapsedTime;
                        sortedTable[p].setExecutionTime(pExecTime);
                        std::cout << "P" << sortedTable[p].getProcessID() << " | " << sortedTable[p].getArrivalTime() << " | " << sortedTable[p].getExecutionTime() << " | " << sortedTable[p].getBurstTime() << " \n";
                        if (pExecTime == sortedTable[p].getBurstTime()) {
                            doneProcesses.push_back(p);
                        }
                    }
                }
            } else {
                for (auto it_ = temp.begin(); it_ != temp.end(); ++it_) {
                    std::cout << "P" << sortedTable[it_->first].getProcessID() << " ";
                }
                std::cout << "finish: \n";
                std::cout << "P | At | Et | Bt \n";
                elapsedTime = temp.begin()->second - prevRemBurst;
                prevRemBurst = temp.begin()->second;

                for (int p = 0; p < doneProcesses.size(); p++) {
                    std::cout << "P" << sortedTable[doneProcesses[p]].getProcessID() << " | " << sortedTable[doneProcesses[p]].getArrivalTime() << " | " << sortedTable[doneProcesses[p]].getExecutionTime() << " | " << sortedTable[doneProcesses[p]].getBurstTime() << " \n";
                }

                for (int p = 0; p < currentProcess; p++) {
                    auto it = std::find(doneProcesses.begin(), doneProcesses.end(), p);
                    if (it != doneProcesses.end()) {
                        continue;
                    } else {
                        pExecTime = sortedTable[p].getExecutionTime() + elapsedTime;
                        sortedTable[p].setExecutionTime(pExecTime);
                        std::cout << "P" << sortedTable[p].getProcessID() << " | " << sortedTable[p].getArrivalTime() << " | " << sortedTable[p].getExecutionTime() << " | " << sortedTable[p].getBurstTime() << " \n";
                        if (pExecTime == sortedTable[p].getBurstTime()) {
                            doneProcesses.push_back(p);
                        }
                    }
                }
            }
            temp.clear();
            it++;
        }
    }
}

void FCFSScheduler::setProcessTable(const ProcessTable& table) {
    processTable = table;
}
