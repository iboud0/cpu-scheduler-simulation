#include "FCFSScheduler.h"

int main() {
    // Create a test process table
    ProcessTable processTable;
    processTable.addProcess(Process(1, 0, 1));
    processTable.addProcess(Process(2, 1, 1));
    processTable.addProcess(Process(3, 2, 5));
    processTable.addProcess(Process(4, 3, 2));

    // Create an instance of FCFSScheduler
    FCFSScheduler scheduler;

    scheduler.schedulerSim(processTable);

    return 0;
}
