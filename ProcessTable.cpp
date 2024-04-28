#include "ProcessTable.h"

ProcessTable::ProcessTable() {}

void ProcessTable::addProcess(const Process& process) {
    processes.push_back(process);
}

int ProcessTable::size() const {
    return processes.size();
}

Process& ProcessTable::operator[](int index) {
    return processes[index];
}

const Process& ProcessTable::operator[](int index) const {
    return processes[index];
}

std::vector<Process>::iterator ProcessTable::begin() {
    return processes.begin();
}

std::vector<Process>::iterator ProcessTable::end() {
    return processes.end();
}

std::vector<Process>::const_iterator ProcessTable::begin() const {
    return processes.begin();
}

std::vector<Process>::const_iterator ProcessTable::end() const {
    return processes.end();
}
