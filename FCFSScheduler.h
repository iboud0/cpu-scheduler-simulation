#ifndef FCFS_SCHEDULER_H
#define FCFS_SCHEDULER_H

#include "ProcessTable.h"

class FCFSScheduler {
private:
    ProcessTable processTable;

public:
    FCFSScheduler();

    void schedulerSim(const ProcessTable& table);
    void setProcessTable(const ProcessTable& table);
};

#endif // FCFS_SCHEDULER_H
