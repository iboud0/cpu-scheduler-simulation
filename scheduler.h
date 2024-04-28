#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Process.h"
#include <vector>

void FCFS(std::vector<Process>& processes);
void SJF(std::vector<Process>& processes);
void PriorityScheduling(std::vector<Process>& processes);
void RoundRobin(std::vector<Process>& processes, int timeQuantum);

#endif // SCHEDULER_H
