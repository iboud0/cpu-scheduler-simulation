#include "Process.h"

Process::Process(int id, int arrival, int burst, int prio): processID(id), arrivalTime(arrival), burstTime(burst), priority(prio) {}

int Process::getProcessID() const { return processID; }
int Process::getArrivalTime() const { return arrivalTime; }
int Process::getBurstTime() const { return burstTime; }
int Process::getPriority() const { return priority; }

void Process::setProcessID(int id) { processID = id; }
void Process::setArrivalTime(int arrival) { arrivalTime = arrival; }
void Process::setBurstTime(int burst) { burstTime = burst; }
void Process::setPriority(int prio) { priority = prio; }
