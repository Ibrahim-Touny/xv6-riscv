#include "kernel/types.h"
#include "user/user.h"

int main() {
    printf("Uptime ticks = %d\n", uptime());
    exit(0);
}
