#include "kernel/types.h"
#include "user/user.h"
#include "kernel/datetime.h"

// Create the Functionality of the syscall
int main() {
  struct datetime dt;

  if (datetime(&dt) < 0) {
    fprintf(2, "Error retrieving date and time\n");
    exit(1);
  }

  fprintf(1, "Date: %d/%d/%d\tTime: %d:%d:%d\n",
    dt.day, dt.month, dt.year,
    dt.hour, dt.minute, dt.second);

  exit(0);
}
