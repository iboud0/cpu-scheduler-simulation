#ifndef PROCESS_H
#define PROCESS_H

class Process {
private:
    int processID;
    int arrivalTime;
    int burstTime;
    int priority; // Only applicable for Priority Scheduling

public:
    Process(int processID, int arrivalTime, int burstTime, int priority = 0);

    int getProcessID() const;
    int getArrivalTime() const;
    int getBurstTime() const;
    int getPriority() const;

    void setProcessID(int processID);
    void setArrivalTime(int  arrivalTime);
    void setBurstTime(int burstTime);
    void setPriority(int priority);
};

#endif // PROCESS_H
