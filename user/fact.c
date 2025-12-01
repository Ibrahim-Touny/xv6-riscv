#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"
int  factorial_function(int n)
{
   if(n == 0 || n == 1)
        return 1;
    else
        return n * factorial_function(n - 1);
}
int valid_number(char *s){
    for(int i=0; s[i]; i++){
        if(s[i] < '0' || s[i] > '9') return 0;
    }
    return 1;
}
int main(int argc, char *argv[])
{
  if(argc!=2)
  {
  printf("you should enter one number\n");
  exit(1);
  }
  if(!valid_number(argv[1]))
  {
      printf("Error: input must be a non-negative integer\n");
      exit(1);
  }

  int num=atoi(argv[1]);

  if(num<0)
  {
  printf("enter a positive number\n");
  exit(1);
  }


  printf("%d! = %d\n", num, factorial_function(num));
  exit(0);
}

