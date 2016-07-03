#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#define NUM_THREAD 100
void* thread_inc(void *arg);
void* thread_des(void *arg);
long long num=0;
pthread_mutex_t mutex;
int main()
{
	pthread_t thread[NUM_THREAD];
	pthread_mutex_init(&mutex,NULL);
	int i;
	printf("sizeof long long :%d\n",sizeof(long long));
	for(i=0;i<NUM_THREAD;i++)
	{
		if(i%2)
		pthread_create(&(thread[i]),NULL,thread_inc,NULL);
		else
		pthread_create(&(thread[i]),NULL,thread_des,NULL);
	}
	for(i=0;i<NUM_THREAD;i++)
	{
		pthread_join(thread[i],NULL);
	}
	printf("result is %d\n",num);
	pthread_mutex_destroy(&mutex);
	return 0;
 } 
 void * thread_inc(void * arg)
 {
 	int i;
	//pthread_mutex_lock(&mutex);
 	for(i=0;i<50000;i++)
	 {
	 	pthread_mutex_lock(&mutex);
	 	num+=1;
	 	pthread_mutex_unlock(&mutex);
	  } 
	//pthread_mutex_unlock(&mutex);
	return NULL;
 }
 void * thread_des(void *arg)
 {
 	int i;
 	//pthread_mutex_lock(&mutex);
 	for(i=0;i<50000;i++)
 	{
 		pthread_mutex_lock(&mutex);
 		num-=1;
 		pthread_mutex_unlock(&mutex);
	 }
	//pthread_mutex_unlock(&mutex);
	 return NULL;
  } 
