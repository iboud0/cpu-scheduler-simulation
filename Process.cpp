#include "Process.h"

Process::Process(int id, int arrival, int burst, int prio)
    : id(id), arrivalTime(arrival), burstTime(burst), priority(prio), startTime(0), completionTime(0), executionTime(0), waitingTime(0), turnaroundTime(0), isComplete(false) {}

int Process::getProcessID() const { return id; }
int Process::getArrivalTime() const { return arrivalTime; }
int Process::getBurstTime() const { return burstTime; }
int Process::getStartTime() const { return startTime; }
int Process::getCompletionTime() const { return completionTime; }
int Process::getExecutionTime() const { return executionTime; }
int Process::getWaitingTime() const { return waitingTime; }
int Process::getTurnaroundTime() const { return turnaroundTime; }
int Process::getPriority() const { return priority; }
bool Process::getIsComplete() const { return isComplete; }

void Process::setProcessID(int id) { this->id = id; }
void Process::setArrivalTime(int arrival) { arrivalTime = arrival; }
void Process::setBurstTime(int burst) { burstTime = burst; }
void Process::setStartTime(int start) { startTime = start; }
void Process::setCompletionTime(int completion) { completionTime = completion; }
void Process::setExecutionTime(int exec) { executionTime = exec; }
void Process::setWaitingTime(int wait) { waitingTime = wait; }
void Process::setTurnaroundTime(int turnaround) { turnaroundTime = turnaround; }
void Process::setPriority(int prio) { priority = prio; }
void Process::setIsComplete(bool complete) { isComplete = complete; }