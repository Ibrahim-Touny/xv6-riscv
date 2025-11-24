#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// args and argv: for example usage: echo hello world
// argc will have the number of arguments: 3
// argv will be an array of strings: ["echo", "hello", "world"]

// Create Add Command
// add number1 number2
// This command will take two numbers and print their sum
int main(int argc, char *argv[])
{
  if(argc == 2 && strcmp(argv[1], "?") == 0) {
    printf("Usage: add number1 number2\n");
    exit(0);
  }

  if(argc != 3) {
    printf("You can only add two numbers\n");
    exit(0);
  }

  int num1 = atoi(argv[1]);
  int num2 = atoi(argv[2]);

  int total = num1 + num2;

  printf("The sum of %d and %d is %d\n", num1, num2, total);

  exit(0);
}
