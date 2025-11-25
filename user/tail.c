#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main(int argc, char *argv[])
{
int num_lines=10;
int fd=0;
char buf[4096];
int n;

if(argc==2)
{
  fd=opne(argv[1],0_RDONLY)
  if(fd<0)
  {printf(""tail: cannot open %s\n", argv[1]); exit(1)");
  }
}
if(argc==4 &&strcmp )

}
