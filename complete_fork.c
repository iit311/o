#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

void Ascending(int arr[],int n){
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(arr[i]>arr[j]){
                int temp =arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }
    }
    printf("Ascending Array\n");
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
}

void Descending(int arr[],int n){
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(arr[i]<arr[j]){
                int temp = arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }
    }
    printf("Descending Array\n");
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
}

int main(){
    pid_t pid;
    int status;
    int n;

    printf("Enter the size of array:");
    scanf("%d",&n);

    int arr[n];
    printf("Enter %d array elemnts\n",n);
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    
    pid =fork();
    
    if(pid==0){
        printf("Child process is executig....\n");
        printf("Child id: %d\n",getpid());
        printf("Child's parent id: %d\n",getppid());

        Ascending(arr,n);
        printf("\n");
        system("ps");
    }
    else if(pid>0){
        wait(&status);
        printf("Parent process is executing...\n");

        printf("Parent ID:%d\n",getpid());
        printf("Child ID:%d\n",pid);

        Descending(arr,n);
        printf("\n");
        system("ps");
    }
    else{
        printf("fork failed\n");
    }
    return 0;
}