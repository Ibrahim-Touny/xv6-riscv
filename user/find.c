#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
#include "user/user.h"

void find(char *path, char *filename)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  // Open current path
  if((fd = open(path, O_RDONLY)) < 0){
    printf("find: cannot open %s\n", path);
    return;
  }

  // Get file info
  if(fstat(fd, &st) < 0){
    printf("find: cannot stat %s\n", path);
    close(fd);
    return;
  }

  // If this is a file, check for match
  if(st.type == T_FILE)
  {
    char *name = path + strlen(path); // Start at end of string
    while(name >= path && *name != '/') // Walk backward to last '/'
      name--;
    name++; // Move to first char of basename

    // Compare basename to target filename
    if(strcmp(name, filename) == 0){
      printf("%s\n", path); // Print full path on match
    }
    close(fd); // Done with this file
    return;
  }

  // If this is a directory, move inside it and search its contents
  if(st.type == T_DIR)
  {
    // Example: path = "/home"
    // We will build: "/home/file.txt" OR "/home/docs" etc.

    // Make sure buffer is large enough for: "/home" + "/" + "filename" + '\0'
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf)){
      printf("find: path too long\n");
      close(fd);
      return;
    }

    strcpy(buf, path);         // buf = "/home"
    p = buf + strlen(buf);      // p points to end of "/home"
    *p++ = '/';                  // buf becomes "/home/"

    // Now we start reading what's inside "/home"
    while(read(fd, &de, sizeof(de)) == sizeof(de))
    {
      if(de.inum == 0)           // Empty entry — skip
        continue;

      // Skip "." and ".." entries to avoid infinite loops
      // "."  -> same folder ( /home )
      // ".." -> parent folder ( / )
      if(strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
        continue;

      memmove(p, de.name, DIRSIZ);   // Copy the 14-byte filename (DIRSIZ) into buf (after "path/")
      p[DIRSIZ] = 0;                  // Add '\0' to make it a valid C string


      // Now we call find on new path:
      // find("/home/docs", filename);
      find(buf, filename);
    }
}

  close(fd);
}

int main(int argc, char *argv[])
{
  if(argc == 2 && strcmp(argv[1], "?") == 0)
  {
    printf("Usage: find <start_directory> <filename>\n");
    exit(0);
  }

  if(argc == 3)
    find(argv[1], argv[2]);
  else if (argc == 2)
    find(".", argv[1]);
  else
    printf("Incorrect number of arguments\n");

  exit(0);
}
