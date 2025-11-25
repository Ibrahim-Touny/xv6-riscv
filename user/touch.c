#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"
int
main(int argc, char *argv[])
{
  //law eli dakhel hagten w tany haga "?" yprint el help function
  if(argc == 2 && strcmp(argv[1], "?") == 0) {
    printf("Usage: touch filename\n");
    //terminates the command
    exit(0);
  }
  //law eli dakhel msh 2 yebaa feh error (wahed el command w esm el file)
  if(argc != 2) {
    printf("Invalid command, you can only use a single filename\n");
    exit(0);
  }
  //create file using open
  //open btakhod esm el file wl mode
  //feh mode read only w write only w create w read w write
  //el function betraga3 positive number law elmatlob fl flag et3amal w negative law error
  int fd = open(argv[1], O_CREATE);
  if(fd < 0) {
    printf("Error: cannot create,open file ror file already created %s\n", argv[1]);
    exit(1);
  }
  //close file baad ma etaamalo create alashan el resource allocation w aalshan el descriptor yerga3 fady
  close(fd);

	exit(0);
}
