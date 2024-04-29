#ifndef PROCESS_H
#define PROCESS_H

class Process {
private:
    int processID;
    int arrivalTime;
    int burstTime;
    int executionTime = 0;
    int priority; // Only applicable for Priority Scheduling

public:
    Process(int id, int arrival, int burst, int prio = 0);

    int getProcessID() const;
    int getArrivalTime() const;
    int getBurstTime() const;
    int getExecutionTime() const;
    int getPriority() const;

    void setProcessID(int id);
    void setArrivalTime(int  arrival);
    void setBurstTime(int burst);
    void setExecutionTime(int exec);
    void setPriority(int prio);
};

#endif // PROCESS_H
