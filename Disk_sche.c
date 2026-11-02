/*
1)FCFS-> uses the original request order.

2)SSTF->chooses the nearest request.

3)SCAN(Elevator)-Moves in one direction->Reaches the disk boundary(199).Changes direction and services remaining requests.

4)C-Scan-> one direction->reaching the end(199)->returns to the beginning(0)->Starts servicing again in the same direction.

5)LOOK->one direction->last request(not 199)->Reverses at the last pending request(<start)->last queue request

6)C-LOOK->one direction->last request(not 199)->jumps to the lowest request(i=0)->same direction
*/

#include<stdio.h>
#include<stdlib.h>

int a[20],n,start;

void sort(){
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(a[i]>a[j]){
                int temp =a[i];
                a[i]=a[j];
                a[j]=temp;
            }
        }
    }
}

void FCFS(){
    int head=start;
    int total=0;
    printf("FCFS: %d\n",head);
    
    for(int i=0;i<n;i++){
        total+=abs(head-a[i]);
        head=a[i];
        printf(" ->%d ",head);
    }
    printf("\n");
    printf("Total movements:%d\n",total);
}

void SSTF(){
    int head=start;
    int total=0,min;
    int pos=0;
    int visited[20]={0};
    
    for(int i=0;i<n;i++){
        min=99999;
        for(int j=0;j<n;j++){
            if(!visited[j] && abs(head-a[j])<min){
                min=abs(head-a[j]);
                pos=j;
            }
        }
        visited[pos]=1;
        total+=abs(head-a[pos]);
        head=a[pos];
        
        printf(" ->%d ",head);
    }
    printf("Total movements:%d\n",total);
    
}

void Scan(){
    int head=start,total=0;

    printf("\nSCAN: %d",head);

    for(int i=0;i<n;i++){
        if(a[i]>start){
            total+=abs(head-a[i]);
            head=a[i];
            printf(" ->%d",head);
        }
    }
    total+=abs(head-199);
    head=199;
    printf(" ->%d",head);
    
    for(int i=n-1;i>=0;i--){
        if(a[i]<start){
            total+=abs(head-a[i]);
            head=a[i];
            printf(" ->%d",head);
        }
    }
    printf("Total movements:%d\n",total);
}

void CSCAN(){
    int head=start;
    int total=0;

    printf("C-scan:%d",head);

    for(int i=0;i<n;i++){
        if(a[i]>start){
            total+=abs(head-a[i]);
            head=a[i];
            printf(" ->%d",head);
        }
    }
    total+=abs(head-199);
    head=199;
    printf(" ->%d",head);

    total+=199;
    head=0;

    for(int i=0;i<n;i++){
        if(a[i]<start){
            total+=abs(head-a[i]);
            head=a[i];
            printf(" ->%d",head);
        }
    }
    printf("Total Movements:%d\n",total);
}

void look(){
    int head=start,total=0;

    printf("Look -%d",head);

    for(int i=0;i<n;i++){
        if(a[i]>start){
            total+=abs(head-a[i]);
            head=a[i];
            printf(" ->%d",head);
        }
    }
    for(int i=n-1;i>=0;i--){
        if(a[i]<start){
            total+=abs(head-a[i]);
            head=a[i];
            printf(" ->%d",head);
        }
    }
    printf("Total Movements:%d\n",total);

}

void C_LOOK(){
    int head=start,total=0;

    printf("C-LOOK %d\n",head);

    for(int i=0;i<n;i++){
        if(a[i]>start){
            total+=abs(head-a[i]);
            head=a[i];
            printf(" ->%d",head);
        }
    }
    for(int i=0;i<n;i++){
        if(a[i]<start){
            total+=abs(head-a[i]);
            head=a[i];
            printf(" ->%d",head);
        }
    }
    printf("Total Movements:%d\n",total);

}

int main(){

    printf("Enter number of requests:");
    scanf("%d",&n);
    
    printf("Enter the requests:");
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    
    printf("Enter initail head postion:");
    scanf("%d",&start);

    sort();
    
    FCFS();
    SSTF();
    Scan();
    CSCAN();
    look();
    C_LOOK();
    return 0;
}