#ifndef __THREAD_OBJECT_H
#define __THREAD_OBJECT_H

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

using namespace std;

void *thread_first(void *x);
void *thread_second(void *x);

class thread_object
{
      
      public:
	
         pthread_t Tid;
	 string Name;
         static pthread_mutex_t mutex;
         static int count;
         static sem_t sem_var;
         static pthread_cond_t cond_var1;
         static pthread_cond_t cond_var2;

      protected:

 	 // virtual void do_something(void) = 0;

      public:
	
	 thread_object(void);
	 ~thread_object(void);
	 void name(string x);
    	 string name(void);
	 void run(void);
	 void join(void);

         // Mutex
         static int InitMutex();
         static int DestroyMutex();
         static int LockMutex(string &identifier);
         static int UnlockMutex(string &identifier);

         // semaphore
         static int InitSem();
         static int DestroySem();
         static int LockSem(string &identifier);
         static int UnlockSem(string &identifier);

         // condition variable
         static int InitCond();
         static int DestroyCond();
         static int LockCond_1(string &identifier);
         static int UnlockCond_1(string &identifier);
         static int LockCond_2(string &identifier);
         static int UnlockCond_2(string &identifier);
	 friend void *thread_first(void *x);
         friend void *thread_second(void *x);
};

#endif
