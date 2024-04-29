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

private:
    void displayTable(int idx1, int idx2, const ProcessTable& sortedTable, const std::vector<int>& doneProcesses) const;
};

#endif // FCFS_SCHEDULER_H
