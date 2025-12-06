#include "types.h"

// process table
struct ptable {
    int pid;
    int ppid;
    int state;
    uint64 sz; // memory size
    char name[16];
};
