#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"
int
main(int argc, char *argv[])
{
  //law eli dakhel hagten w tany haga "?" yprint el help function
  if(argc == 2 && strcmp(argv[1], "?") == 0) {
    printf("Usage: diff [source file] [destination file]\n");
    //terminates the command
    exit(0);
  }
  //law eli dakhel msh 2 yebaa feh error (wahed el command w esm el file)
  if(argc != 3) {
    printf("Invalid command, you can only enter source file and destination file\n");
    exit(0);
  }
  //check eno el source w el destination howa files msh directories w msh habal
  if(!strchr(argv[1],'.')|| !strchr(argv[2],'.')){
    printf("Error: both source and destination must be files\n");
    exit(1);
  }
  //hnopen el two files w ne2rahom byte by byte w ncompare benhom (elflag read only)
  int fd1 = open(argv[1], O_RDONLY);
  int fd2 = open(argv[2], O_RDONLY);
  int differs = 0;
  //check el files etfataho wala la
  if(fd1 < 0 || fd2 < 0){
    printf("Error: cannot open one of the files\n");
    exit(1);
  }
  else {
    //aamlen max size le kol line 512 byte
    char line1[512], line2[512];
    int line_num = 1;
      //nloop baa lghayer ma yeb2a feh eof
      while (1) {
        //counters w characters w number of bytes read le kol file
        int i1 = 0, i2 = 0;
        char c1, c2;
        int n1, n2;

    // Read one line from fd1
    //deh global condition eno no2af abl ma el buffer yebaa full b wahed w tool ma feh character byt2ery
    while (i1 < sizeof(line1) - 1 && (n1 = read(fd1, &c1, 1)) > 0) {
        //nhot fl buffer el character eli 2erynah mlfile
        line1[i1++] = c1;
        //deh el condition eli fl aghlab bttha2a2 en el line kheles yaany wesel le '\n' eli howa el enter
        if (c1 == '\n') break;
    }
    //nhot null char 3ashan n2fel el string bta3t el line eli f awel file
    line1[i1] = '\0';

    // Read one line from fd2
    //nafs el kalam le file 2
    while (i2 < sizeof(line2) - 1 && (n2 = read(fd2, &c2, 1)) > 0) {
        line2[i2++] = c2;
        if (c2 == '\n') break;
    }
    line2[i2] = '\0';

    // Check EOF
    //n = 0 yaany mafish haga et2aret mn el filen
    if (n1 == 0 && n2 == 0) break;

    // Compare compare kol line feh w law feh ekhtelaf nprint el ekhtelaf w nexit
    if (strcmp(line1, line2) != 0) {
        // If one file ends but the other continues → different-length files
      if (n1 == 0 && n2 > 0) {
        printf("line %d only differs at %s\n", line_num,argv[1]);
        printf("> %s", line2);
        differs = 1;
        break;
    }

    if (n2 == 0 && n1 > 0) {
        printf("line %d only differs at %s\n", line_num,argv[2]);
        printf("< %s", line1);
        differs = 1;
        break;
    }
        printf("line %d differs\n", line_num);
        printf("< %s", line1);
        printf("> %s", line2);
        differs=1;
    }
    //increment el line number kol ma ne2ra line alshan nedkhol 3ali baado
    line_num++;
      }
      if(differs==0)
       printf("Files are identical\n");

    close(fd1);
   close(fd2);
  exit(0);
    }
}
