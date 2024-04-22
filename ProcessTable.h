#ifndef PROCESS_TABLE_H
#define PROCESS_TABLE_H

#include <vector>
#include "Process.h"

class ProcessTable {
private:
    std::vector<Process> processes;

public:
    ProcessTable();

    void addProcess(const Process& process);

    int size() const;

    Process& operator[](int index);
    const Process& operator[](int index) const;

    std::vector<Process>::iterator begin();
    std::vector<Process>::iterator end();
    std::vector<Process>::const_iterator begin() const;
    std::vector<Process>::const_iterator end() const;
};

#endif // PROCESS_TABLE_H
