#include "Scheduler.h"
#include <iostream>
#include <vector>

// Function to create test cases
std::vector<Process> createTestCase(int choice) {
    std::vector<Process> processes;
    switch (choice) {
        case 1: // Test Case 1: Simple sequential processes
            processes = {
                Process(1, 0, 4, 2),
                Process(2, 1, 3, 3),
                Process(3, 2, 2, 1),
                Process(4, 3, 1, 4)
            };
            break;
        case 2: // Test Case 2: Processes with the same arrival time
            processes = {
                Process(1, 0, 8, 8),
                Process(2, 0, 4, 1),
                Process(3, 0, 2, 3),
                Process(4, 0, 6, 2)
            };
            break;
        case 3: // Test Case 3: Processes with high variance in burst and priority
            processes = {
                Process(1, 1, 2, 1),
                Process(2, 2, 1, 3),
                Process(3, 3, 4, 5),
                Process(4, 4, 6, 2)
            };
            break;
        case 4: // Test Case 4: Processes for Round Robin
            processes = {
                Process(1, 0, 10, 2),
                Process(2, 0, 15, 3),
                Process(3, 0, 20, 1),
                Process(4, 10, 5, 4)
            };
            break;
    }
    return processes;
}

int main() {
    int testChoice;
    std::cout << "Enter test case number (1-4): ";
    std::cin >> testChoice;

    std::vector<Process> processes = createTestCase(testChoice);
    if (processes.empty()) {
        std::cout << "Invalid test case number." << std::endl;
        return 1;
    }

    std::cout << "Running FCFS:\n";
    FCFS(processes);

    std::cout << "\nRunning SJF:\n";
    SJF(processes);

    std::cout << "\nRunning Priority Scheduling:\n";
    PriorityScheduling(processes);

    if (testChoice == 4) {
        int timeQuantum = 5;
        std::cout << "\nRunning Round Robin with time quantum = " << timeQuantum << ":\n";
        RoundRobin(processes, timeQuantum);
    } else {
        std::cout << "\nSkipping Round Robin as it's not applicable for this test case." << std::endl;
    }

    return 0;
}
