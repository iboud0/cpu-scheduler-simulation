#include "Scheduler.h"
#include <iostream>
#include <climits>
#include <limits>
#include <queue> 


void FCFS(std::vector<Process>& processes) {
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.getArrivalTime() < b.getArrivalTime();
    });

    int currentTime = 0;
    std::cout << "FCFS Scheduling Order: \n";
    for (const auto& process : processes) {
        if (currentTime < process.getArrivalTime()) {
            currentTime = process.getArrivalTime();
        }
        std::cout << "Process ID: " << process.getProcessID() << " starts at " << currentTime
                  << " and finishes at " << currentTime + process.getBurstTime() << std::endl;
        currentTime += process.getBurstTime();
    }
}

void SJF(std::vector<Process>& processes) {
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.getArrivalTime() < b.getArrivalTime();
    });

    int currentTime = 0;
    std::vector<Process> readyQueue;
    std::vector<Process>::iterator it;

    std::cout << "SJF Scheduling Order: \n";
    while (!processes.empty() || !readyQueue.empty()) {
        // Move processes that have arrived by currentTime to the ready queue
        auto processIt = std::remove_if(processes.begin(), processes.end(), [&](Process& p) {
            if (p.getArrivalTime() <= currentTime) {
                readyQueue.push_back(p);
                return true;
            }
            return false;
        });
        processes.erase(processIt, processes.end());

        // Select the process with the shortest burst time from the ready queue
        if (!readyQueue.empty()) {
            it = std::min_element(readyQueue.begin(), readyQueue.end(), [](const Process& a, const Process& b) {
                return a.getBurstTime() < b.getBurstTime();
            });

            Process shortestJob = *it;
            readyQueue.erase(it);

            if (currentTime < shortestJob.getArrivalTime()) {
                currentTime = shortestJob.getArrivalTime();
            }
            std::cout << "Process ID: " << shortestJob.getProcessID() << " starts at " << currentTime
                      << " and finishes at " << currentTime + shortestJob.getBurstTime() << std::endl;
            currentTime += shortestJob.getBurstTime();
        } else {
            // No process is ready; increment time
            if (!processes.empty()) {
                currentTime = processes.front().getArrivalTime();
            }
        }
    }
}


void PriorityScheduling(std::vector<Process>& processes) {
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.getPriority() < b.getPriority() || (a.getPriority() == b.getPriority() && a.getArrivalTime() < b.getArrivalTime());
    });

    int currentTime = 0;
    std::cout << "Priority Scheduling Order:\n";
    for (auto& process : processes) {
        if (currentTime < process.getArrivalTime()) {
            currentTime = process.getArrivalTime();
        }
        std::cout << "Process ID: " << process.getProcessID() << " starts at " << currentTime
                  << " and finishes at " << currentTime + process.getBurstTime() << std::endl;
        currentTime += process.getBurstTime();
    }
}


void RoundRobin(std::vector<Process>& processes, int timeQuantum) {
    std::queue<Process> queue;
    std::vector<Process> tempProcesses = processes;
    std::sort(tempProcesses.begin(), tempProcesses.end(), [](const Process& a, const Process& b) {
        return a.getArrivalTime() < b.getArrivalTime();
    });

    int currentTime = 0;
    auto it = tempProcesses.begin();
    std::cout << "Round Robin Scheduling Order:\n";
    while (!queue.empty() || it != tempProcesses.end()) {
        while (it != tempProcesses.end() && it->getArrivalTime() <= currentTime) {
            queue.push(*it);
            it++;
        }
        if (!queue.empty()) {
            Process process = queue.front();
            queue.pop();
            int start = currentTime;
            int duration = std::min(timeQuantum, process.getBurstTime());
            std::cout << "Process ID: " << process.getProcessID() << " runs from " << start
                      << " to " << start + duration << std::endl;
            process.setBurstTime(process.getBurstTime() - duration);
            currentTime += duration;
            if (process.getBurstTime() > 0) {
                queue.push(process);
            }
        } else {
            currentTime = it->getArrivalTime();
        }
    }
}


void PriorityRoundRobin(std::vector<Process>& processes, int timeQuantum) {
    // Sort by priority first, then by arrival time
    std::stable_sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.getPriority() < b.getPriority();
    });

    int currentTime = 0;
    std::queue<Process> queue;
    std::cout << "Priority + Round Robin Scheduling Order:\n";
    // Process each priority level with Round Robin
    auto startIt = processes.begin();
    while (startIt != processes.end()) {
        auto endIt = std::find_if(startIt, processes.end(), [&startIt](const Process& p) {
            return p.getPriority() != startIt->getPriority();
        });
        std::vector<Process> samePriority(startIt, endIt);
        RoundRobin(samePriority, timeQuantum);
        startIt = endIt;
    }
}