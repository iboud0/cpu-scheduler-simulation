#ifndef PROCESS_H
#define PROCESS_H

class Process {
private:
    int id;
    int arrivalTime;
    int burstTime;
    int startTime;
    int completionTime;
    int executionTime;
    int waitingTime;
    int turnaroundTime;
    int priority;
    bool isComplete;

public:
    Process(int id, int arrival, int burst, int prio = 0);

    int getProcessID() const;
    int getArrivalTime() const;
    int getBurstTime() const;
    int getStartTime() const;
    int getCompletionTime() const;
    int getExecutionTime() const;
    int getWaitingTime() const;
    int getTurnaroundTime() const;
    int getPriority() const;
    bool getIsComplete() const;

    void setProcessID(int id);
    void setArrivalTime(int arrival);
    void setBurstTime(int burst);
    void setStartTime(int start);
    void setCompletionTime(int completion);
    void setExecutionTime(int exec);
    void setWaitingTime(int wait);
    void setTurnaroundTime(int turnaround);
    void setPriority(int prio);
    void setIsComplete(bool complete);
};

#endif // PROCESS_H