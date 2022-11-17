#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<math.h>
#include<time.h>

void sub_timespec(struct timespec t1, struct timespec t2, struct timespec *td){
    td->tv_nsec=t2.tv_nsec-t1.tv_nsec;
    td->tv_sec=t2.tv_sec-t1.tv_sec;
    if((td->tv_sec>0) && (td->tv_nsec<0)){
        td->tv_nsec+=1000000000;
        td->tv_sec--;
    }
    else if((td->tv_sec<0) && (td->tv_nsec>0)){
        td->tv_nsec-=1000000000;
        td->tv_sec++;
    }
}

//-----------------------------------------------------------------------------------------

void *countA(){
    struct timespec start, finish, delta;
    clock_gettime(CLOCK_REALTIME, &start);
    long long limit=(long long int)pow(2,32);
    long long int i=1;
    while(i!=limit){
        i++;
    }
    clock_gettime(CLOCK_REALTIME, &finish);
    sub_timespec(start, finish, &delta);
    printf("countA() finished in %d.%.9ld seconds.\n",(int)delta.tv_sec,delta.tv_nsec);
}

void *countB(){
    struct timespec start, finish, delta;
    clock_gettime(CLOCK_REALTIME, &start);
    long long limit=(long long int)pow(2,32);
    long long int i=1;
    while(i!=limit){
        i++;
    }
    clock_gettime(CLOCK_REALTIME, &finish);
    sub_timespec(start, finish, &delta);
    printf("countB() finished in %d.%.9ld seconds.\n",(int)delta.tv_sec,delta.tv_nsec);
}

void *countC(){
    struct timespec start, finish, delta;
    clock_gettime(CLOCK_REALTIME, &start);
    long long limit=(long long int)pow(2,32);
    long long int i=1;
    while(i!=limit){
        i++;
    }
    clock_gettime(CLOCK_REALTIME, &finish);
    sub_timespec(start, finish, &delta);
    printf("countC() finished in %d.%.9ld seconds.\n",(int)delta.tv_sec,delta.tv_nsec);
}

//-----------------------------------------------------------------------------------------

int main(){
    for(int i=0;i<10;i++){
        pthread_t Thr_A, Thr_B, Thr_C;
        int retA, retB, retC;

        struct sched_param paramA;
        pthread_create(&Thr_A,NULL,countA,NULL);
        paramA.sched_priority = 1;
        retA = pthread_setschedparam(Thr_A,SCHED_OTHER,&paramA);
        pthread_join(Thr_A,NULL);

        struct sched_param paramB;
        pthread_create(&Thr_B,NULL,countB,NULL);
        paramB.sched_priority = 1;
        retB = pthread_setschedparam(Thr_B,SCHED_RR,&paramB);
        pthread_join(Thr_B,NULL);

        struct sched_param paramC;
        pthread_create(&Thr_C,NULL,countC,NULL);
        paramC.sched_priority = 1;
        retC = pthread_setschedparam(Thr_C,SCHED_FIFO,&paramC);
        pthread_join(Thr_C,NULL);
    }
    return 0;
}