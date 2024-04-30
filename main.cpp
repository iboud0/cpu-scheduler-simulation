#include "FCFSScheduler.h"
#include "RRScheduler.h"

int main() {
    // Create a test process table
    ProcessTable processTable;
    processTable.addProcess(Process(1, 0, 7));
    processTable.addProcess(Process(2, 1, 4));
    processTable.addProcess(Process(3, 2, 5));
    processTable.addProcess(Process(4, 3, 2));

    // Create an instance of FCFSScheduler
    RRScheduler scheduler;

    scheduler.schedulerSim(processTable, 2);

    return 0;
}
