#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

char buf[512];

void wc(int fd, char *name)
{
  int i, n;
  int l, w, c, L, Li, inword;

  // l = lines, w = words, c = characters, L = longest line, Li = current line length
  l = w = c = L = Li = 0;
  // Keeps track of whether we are currently inside a word
  inword = 0;

  // Read the file in chunks of up to 512 bytes.
  // 'n' = how many bytes were actually read.
  // When read() returns 0 → end of file.
  while((n = read(fd, buf, sizeof(buf))) > 0)
  {
    // Loop through each byte in the buffer
    for(i=0; i<n; i++)
    {
      // Count every character
      c++;
      Li++;  // Increment current line length

      // If the character is a newline, increment line count
      if(buf[i] == '\n'){
        l++;
        if(Li > L)
          L = Li;  // Update longest line length if current line is longer
        Li = 0;  // Reset current line length for the next line
      }

      // Check if the character is whitespace, if so, we are not in a word
      if(strchr(" \r\t\n\v", buf[i]))
        inword = 0;

      // If it's NOT whitespace and we were NOT already inside a word,
      // this marks the start of a new word
      else if(!inword)
      {
        w++;
        inword = 1;
      }
    }
  }
  // If read() returned a negative value, something went wrong.
  // Print an error message and exit the program.
  if(n < 0)
  {
    printf("wc: read error\n");
    exit(1);
  }

  // Print line count, word count, character count, longest line length, and the file name.
  printf("%d %d %d %d %s\n", l, w, c, L, name);
}

int main(int argc, char *argv[])
{
  int fd, i;

  // If no arguments are given (just 'wc'),
  // read from standard input (fd = 0).
  if(argc <= 1){
    wc(0, "");   // name is empty because stdin has no filename
    exit(0);
  }

  // Otherwise, loop through each filename passed in argv[]
  for(i = 1; i < argc; i++){

    // Try to open the file in read-only mode.
    // open() returns a file descriptor, or -1 if it failed.
    if((fd = open(argv[i], O_RDONLY)) < 0){
      printf("wc: cannot open %s\n", argv[i]);
      exit(1);
    }

    // Run wc() on this file descriptor
    wc(fd, argv[i]);

    // Close the file descriptor after use
    close(fd);
  }

  exit(0);  // End program
}
