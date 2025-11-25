#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  //law eli dakhel hagten w tany haga "?" yprint el help function
  if(argc == 2 && strcmp(argv[1], "?") == 0) {
    printf("Usage: move 'soure file' 'destination file'\n");
    exit(0);
  }
  //law eli dakhel msh 3 yebaa feh error (mv w source file w destination file)
  if(argc != 3) {
    printf("Invalid command, you must input source file and destination file\n");
    exit(0);
  }
  // benshof el awel el dest directory wala file fa bnecheck aal directory el awel alashan el default file
  //struct stat betakhod ma3lomat 3an el file zay en kan directory aw file w size
  struct stat st_src, st_dst;


  //stat byakhod esm el file w structure w bymlla el structure b ma3lomat 3an el file
  //law el stat raga3 >= 0 ya3ni el file mawgod w el st.type byshof en kan directory aw file
  //el stat btraga3 zero law eshtaghal w negative law feh moshkela
  if(stat(argv[1], &st_src) < 0){
    printf("Error: source does not exist\n");
    exit(1);
}
  //law el destination mawgood w howa file lazm nms7o abl ma n3mel link alashan link mabyed5olsh fel file el mawgood
  if( stat(argv[2], &st_dst) >= 0 && st_dst.type == T_FILE){
      if(unlink(argv[2]) < 0){
          printf("Error: cannot remove existing destination file %s\n", argv[2]);
          exit(1);
      }
  }
  if(stat(argv[2], &st_dst) >= 0 && st_dst.type == T_DIR){
    // law el destination howa directory lazm n3mel concatenate ben el source file w el destination directory alashan netala3 el path eli hanen2el feh el file
    char newpath[100];

    int i = 0, j = 0;

    // hnloop 3al destination w nhotaha f string gdeed lghayer ma tekhlas (twsal lel null char)
    while(argv[2][i] != '\0') {
        newpath[i] = argv[2][i];
        i++;
    }

    // hanhot slash 3ashan n7ot ba3do esm el source file alashan yeb2a feh path sa7
    newpath[i++] = '/';

    // nloop baa aal source file w n7oto f el string el gedeed baad el slash kaman lghayer ma tekhlas
    while(argv[1][j] != '\0') {
        newpath[i++] = argv[1][j];
        j++;
    }

    //nhoto null char 3ashan n2fel el string
    newpath[i] = '\0';

    // nen2el baa el path el gedeed f argv[2] alashan nsta5demo f el link function ba3d keda
    argv[2] = newpath;

  }
  //link byakhod source w destination w by3mel link benhom, el etneen files hayeb2a feehom nafs el content
  //link btraga3 zero law eshtaghal w negative law feh moshkela
  if(link(argv[1], argv[2])<0) {
    printf("Error: cannot move file from %s to %s,move only works to rename file or move file to directory\n", argv[1], argv[2]);
    exit(1);
  }else{
    printf("File moved successfully from %s to %s\n", argv[1], argv[2]);
  };
  //unlink betms7 el source file ba3d ma 3melnah link b destination file w na2alnah fa byeda effect eno etharak
  //btraga3 zero law eshtaghal w negative law feh moshkela bardo
  if(unlink(argv[1])<0){
    printf("Error: cannot remove source file %s after moving to %s\n", argv[1], argv[2]);
    exit(1);
  }

  exit(0);
}
