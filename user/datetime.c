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

  fprintf(1, "Current Date and Time:\n");
  fprintf(1, "Year: %d\n", dt.year);
  fprintf(1, "Month: %d\n", dt.month);
  fprintf(1, "Day: %d\n", dt.day);
  fprintf(1, "Hour: %d\n", dt.hour);
  fprintf(1, "Minute: %d\n", dt.minute);
  fprintf(1, "Second: %d\n", dt.second);

  exit(0);
}
