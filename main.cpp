#include "FCFSScheduler.h"
#include "SJFScheduler.h"
#include "RRScheduler.h"

int main() {
    // Create a test process table
    ProcessTable processTable;
    processTable.addProcess(Process(1, 0, 2));
    processTable.addProcess(Process(2, 0, 4));
    processTable.addProcess(Process(3, 2, 3));
    processTable.addProcess(Process(4, 3, 2));
    processTable.addProcess(Process(5, 9, 2));
    processTable.addProcess(Process(6, 10, 4));

    // Create an instance of FCFSScheduler
    RRScheduler scheduler;

    scheduler.schedulerSim(processTable, 2);

    return 0;
}
