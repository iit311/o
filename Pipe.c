#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>

int main(){
    pid_t pid;
    char filename[20]={0};
    char buffer[200]={0};

    int fd;
    int pipe1[2];
    int pipe2[2];

    pipe(pipe1);
    pipe(pipe2);

    pid=fork();

    if(pid>0){
        //parent process
        close(pipe1[0]);
        close(pipe2[1]);

        printf("Enter filename:");
        scanf("%s",filename);

        write(pipe1[1],filename,strlen(filename)+1);
        close(pipe1[1]);

        read(pipe2[0],buffer,sizeof(buffer));
        printf("FIle contents:\n%s",buffer);

        close(pipe2[0]);
        wait(NULL);
    }
    else{
        close(pipe1[1]);
        close(pipe2[0]);

        read(pipe1[0],filename,sizeof(filename));
        close(pipe1[0]);

        fd = open(filename,O_RDONLY);

        read(fd,buffer,sizeof(buffer));
        close(fd);

        write(pipe2[1],buffer,strlen(buffer)+1);
        close(pipe2[1]);

        exit(0);
    }
    return 0;
}