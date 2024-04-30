#ifndef SJF_SCHEDULER_H
#define SJF_SCHEDULER_H

#include "ProcessTable.h"

class SJFScheduler {
private:
    ProcessTable processTable;

public:
    SJFScheduler();

    
    void schedulerSim(const ProcessTable& table);
    void setProcessTable(const ProcessTable& table);

private:
    void displayTable(int idx1, int idx2, const ProcessTable& sortedTable, const std::vector<int>& doneProcesses) const;
};

#endif // SJF_SCHEDULER_H
