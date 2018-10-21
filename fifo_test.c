#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "FIFO_FD"

int main(void) {
        char buf[100] ="\0";
        char buf2[100] = "\0";
        int num,num2,fd;

        /* FIFO 에 사용할 파일 지시자 생성 */
        if(mknod(FIFO_NAME, S_IFIFO | 0666, 0) == -1) {
                perror("mknod error");
        }
        puts("start\n");
        if(!fork()){
                printf("CHILD(PID: %d): Writing to the pipe\n",getpid());
                if(fd = open(FIFO_NAME, O_WRONLY))
                        puts("FILE OPEN! - child\n");
                scanf("%s",&buf);
                puts(buf);
                num = write(fd,buf,strlen(buf));
                printf("Writer : wrote %d bytes\n",num);
                close(fd);
                exit(0);
        }
        else{
                printf("PARENT(PID: %d): Reading to the pipe\n",getpid());
                if(fd = open(FIFO_NAME, O_RDONLY))
                        puts("FILE OPEN! - parent\n");
                num2 = read(fd,buf2,100);
                puts(buf2);
                printf("Reader : read %d bytes\n",num2);
                close(fd);
                wait(NULL);
        }
        return 0;
}

