#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

char buf[512];

// global flags so wc function can access them
int lflag = 0, wflag = 0, cflag = 0, Lflag = 0;

int total_l = 0, total_w = 0, total_c = 0, total_L = 0;
int file_count = 0;


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

  // Handle file that doesn't end with newline
  if(Li > 0 && Li > L)
    L = Li;

  // If read() returned a negative value, something went wrong.
  // Print an error message and exit the program.
  if(n < 0)
  {
    printf("wc: read error\n");
    exit(1);
  }

  // Update total counts
  total_l += l;
  total_w += w;
  total_c += c;
  if(L > total_L) total_L = L;
  file_count++;

  // Print only selected flags
  if(lflag) printf("%d ", l);
  if(wflag) printf("%d ", w);
  if(cflag) printf("%d ", c);
  if(Lflag) printf("%d ", L);
  printf("%s\n", name);
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

  if(argc >= 2 && strcmp(argv[1], "?") == 0){
    printf("Usage: wc [-lwcL] [file...]\n");
    printf("  -l : print line counts\n");
    printf("  -w : print word counts\n");
    printf("  -c : print character counts\n");
    printf("  -L : print length of longest line\n");
    printf("Output: LineCount WordCount CharacterCount LongestLineLength FileName\n");
    exit(0);
  }

  // Parse flags
  for(i = 1; i < argc && argv[i][0] == '-'; i++){
    char *p = argv[i] + 1;   // to skip '-'
    while(*p){
        if(*p == 'l') lflag = 1;
        else if(*p == 'w') wflag = 1;
        else if(*p == 'c') cflag = 1;
        else if(*p == 'L') Lflag = 1;
        else {
            printf("wc: unknown option %c\n", *p);
            exit(1);
        }
        p++;
    }
  }

  // If no flags were given, use default: -lwc
  if(!lflag && !wflag && !cflag && !Lflag){
    lflag = wflag = cflag = 1;
  }

  // Otherwise, loop through each filename passed in argv[]
  for(; i < argc; i++) // loop from previous i to end of argc
  {

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
  // If more than one file was processed, print total counts
  if(file_count > 1){
    if(lflag) printf("%d ", total_l);
    if(wflag) printf("%d ", total_w);
    if(cflag) printf("%d ", total_c);
    if(Lflag) printf("%d ", total_L);
    printf("total\n");
  }

  exit(0);  // End program
}
