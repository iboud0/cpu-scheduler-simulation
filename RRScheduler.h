#ifndef RR_SCHEDULER_H
#define RR_SCHEDULER_H

#include "ProcessTable.h"

class RRScheduler {
private:
    ProcessTable processTable;
    float quant;

public:
    RRScheduler();

    
    void schedulerSim(const ProcessTable& table, float timeQuantum);
    void setProcessTable(const ProcessTable& table);

private:
    void displayTable(int idx1, int idx2, const ProcessTable& sortedTable, const std::vector<int>& doneProcesses) const;
};

#endif // RR_SCHEDULER_H