#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main(int argc, char *argv[])
{
    int src_fd, dst_fd;
    char buffer[512];
    int n;

    // Check number of args
    if(argc != 3){
        printf("Usage: cp source_file destination_file\n");
        exit(1);
    }
    // if(strchr(argv[1], '.')==0)
    // {
    //   printf("cp: source file must contain a dot '.'\n");
    //   exit(1);
    // }
    //  if(strchr(argv[2], '.')==0)
    // {
    //   printf("cp: destination file must contain a dot '.'\n");
    //   exit(1);
    // }


    // Open source file (read-only)
    src_fd = open(argv[1], O_RDONLY);
    if(src_fd < 0){
        printf( "cp: cannot open %s\n", argv[1]);
        exit(1);
    }

    // Open/create destination file (write-only)
    dst_fd = open(argv[2], O_CREATE | O_WRONLY);
    if(dst_fd < 0){
        printf("cp: cannot create %s\n", argv[2]);
        close(src_fd);
        exit(1);
    }

    // Read from source, write to destination
    while((n = read(src_fd, buffer, sizeof(buffer))) > 0){
        if(write(dst_fd, buffer, n) != n){
            printf("cp: write error\n");
            close(src_fd);
            close(dst_fd);
            exit(1);
        }

    }

    // Close files
    close(src_fd);
    close(dst_fd);
    printf("copy succcessfully\n");

    exit(0);
}
