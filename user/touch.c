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
  //hawel tfta7 el file eli esmo argv[1] b mode read only alashan nshofo mawgod wala la
  int fd = open(argv[1], O_RDONLY);
  //law raga3 positive integer ya3ni el file descriptor mahgoz lel file fa howa already mawgod
  if(fd>=0){
    printf("file already exists\n");
    close(fd);
    exit(0);
  }else{
    //law raga3 negative ya3ni el file msh mawgod fa hancreate file gedid b esm argv[1]
    fd = open(argv[1], O_CREATE);
    //law fe ay error khareg aan eradetna
    if(fd < 0) {
    printf("Error: cannot create or open file  %s\n", argv[1]);
    //hyexit el program b error code mokhtalef alashan ne3raf nfara2 ben el normal aw la
    exit(1);
    }
    printf("File %s created successfully\n", argv[1]);
  }
  //close file baad ma etaamalo create alashan el resource allocation w aalshan el descriptor yerga3 fady
  close(fd);

	exit(0);
}
