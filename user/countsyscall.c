#include "kernel/types.h"
#include "user/user.h"

int main() {
    int n = countsyscall();
    printf("Total syscalls since boot = %d\n", n);
    exit(0);
}
