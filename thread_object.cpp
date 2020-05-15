#include "thread_object.h"

pthread_mutex_t thread_object::mutex;
sem_t thread_object::sem_var;
pthread_cond_t thread_object::cond_var1;
pthread_cond_t thread_object::cond_var2;
int thread_object::count = 0;

thread_object::thread_object(void)
{

}

thread_object::~thread_object(void)
{
      pthread_join(Tid, NULL);
      cout<<"---- ~thread_object ----"<<endl;
}

void thread_object::run(void)
{
     static bool val = false;

     if(val == false)
     {
          thread_object::InitMutex();
          thread_object::InitCond();
          pthread_create(&Tid, NULL, thread_first, this);
          val = true;
     }
     else
     {
          pthread_create(&Tid, NULL, thread_second, this);
     }
}

void thread_object::join(void)
{
     pthread_join(Tid, NULL);
}

void thread_object::name(string x)
{
     Name = x;
}

string thread_object::name(void)
{
       return Name;
}

// Mutex intialization

int thread_object::InitMutex() 
{
       if(pthread_mutex_init(&thread_object::mutex, NULL) < 0) 
       {
           cout<< "Error while initializing mutex" << endl;
           return -1;
       }
       else 
       {
           //cout << "Mutex initialized." << endl;
           return 0;
       }
}

int thread_object::DestroyMutex()
{
       if(pthread_mutex_destroy(&thread_object::mutex) < 0)
       {
            cout<< "Error while destroying mutex" << endl;
            return -1;
       }
       else
       {
           //cout << "Mutex destroyed." << endl;
           return 0;
       }
 }

/*

LockMutex():
Blocks until mutex becomes available

*/

int thread_object::LockMutex(string &identifier) 
{
       //cout << identifier << " is trying to acquire the lock..." << endl;

       if(pthread_mutex_lock(&thread_object::mutex) == 0) 
       {
             //cout << identifier << " acquired the lock!" << endl;
             return 0;
       }
       else 
       {
            //cerr << "Error while " << identifier << " was trying to acquire the lock" << endl;
             return -1;
       }
}

int thread_object::UnlockMutex(string &identifier) 
{
      //cout << identifier << " is trying to release the lock..." << endl;

      if(pthread_mutex_unlock(&thread_object::mutex) == 0) 
      {
            //cout << identifier << " released the lock!" << endl;
            return 0;
      }
      else 
      {
            //cerr << "Error while " << identifier << " was trying to release the lock" << endl;
            return -1;
      }
}

int thread_object::InitSem()
{
       if(sem_init(&thread_object::sem_var, 0, 1) < 0)
       {
           cout<< "Error while initializing Sem" << endl;
           return -1;
       }
       else
       {
           cout << "Sem initialized." << endl;
           return 0;
       }
}
 
int thread_object::DestroySem()
{
      if(sem_destroy(&thread_object::sem_var) < 0)
      {
           cout<< "Error while destroying Sem" << endl;
           return -1;
      }
      else
     {
           cout << "Sem destroyed." << endl;
           return 0;
     }
}
 
int thread_object::LockSem(string &identifier)
{
       cout << identifier << " is trying to acquire the Sem..." << endl;

       if(sem_wait(&thread_object::sem_var) == 0)
       {
             cout << identifier << " acquired the Sem!" << endl;
             return 0;
       }
       else
       {
             cerr << "Error while " << identifier << " was trying to acquire the Sem" << endl;
             return -1;
       }
}
 
int thread_object::UnlockSem(string &identifier)
{
      cout << identifier << " is trying to release the Sem..." << endl;
 
      if(sem_post(&thread_object::sem_var) == 0)
      {
            cout << identifier << " released the Sem!" << endl;
            return 0;
      }
      else
      {
            cerr << "Error while " << identifier << " was trying to release the Sem" << endl;
            return -1;
      }
}

// Condition variable

int thread_object::InitCond()
{
       if((pthread_cond_init(&thread_object::cond_var1, NULL) < 0) && (pthread_cond_init(&thread_object::cond_var2, NULL) < 0))
       {
           //cout<< "Error while initializing condition" << endl;
           return -1;
       }
       else
       {
           //cout << "condition initialized." << endl;
           return 0;
       }
}
 
int thread_object::DestroyCond()
{
       if((pthread_cond_destroy(&thread_object::cond_var1) < 0) && (pthread_cond_destroy(&thread_object::cond_var2) < 0))
       {
            //cout<< "Error while destroying condition" << endl;
            return -1;
       }
       else
       {
            //cout << "condition destroyed." << endl;
            return 0;
       }
}

int thread_object::LockCond_1(string &identifier)
{
       //cout << identifier << " is trying to acquire the condition..." << endl;

       if(pthread_cond_wait(&thread_object::cond_var1, &thread_object::mutex) == 0)
       {
             //cout << identifier << " acquired the condition!" << endl;
             return 0;
       }
       else
       {
             //cerr << "Error while " << identifier << " was trying to acquire the condition" << endl;
             return -1;
       }
}
 
int thread_object::UnlockCond_1(string &identifier)
{
       //cout << identifier << " is trying to release the condition..." << endl;
 
       if(pthread_cond_signal(&thread_object::cond_var1) == 0)
       {
            //cout << identifier << " released the condition!" << endl;
            return 0;
       }
       else
       {
            //cerr << "Error while " << identifier << " was trying to release the condition" << endl;
            return -1;
      }
}

int thread_object::LockCond_2(string &identifier)
{
       //cout << identifier << " is trying to acquire the condition..." << endl;

       if(pthread_cond_wait(&thread_object::cond_var2, &thread_object::mutex) == 0)
       {  
             //cout << identifier << " acquired the condition!" << endl;
             return 0;
       }
       else  
       {
             //cerr << "Error while " << identifier << " was trying to acquire the condition" << endl;
             return -1;
       }
}

int thread_object::UnlockCond_2(string &identifier)
{
       //cout << identifier << " is trying to release the condition..." << endl;

       if(pthread_cond_signal(&thread_object::cond_var2) == 0)
       {
            //cout << identifier << " released the condition!" << endl;
            return 0;
       }
       else
       {
            //cerr << "Error while " << identifier << " was trying to release the condition" << endl;
            return -1;
       }
}

void *thread_first(void *x)
{
      int count_max = 50;

      thread_object *Thread;
      Thread = static_cast<thread_object *>(x);
      cout<<"thread friend fun: "<<pthread_self()<<" Name : "<<Thread->Name<<endl;
      thread_object::LockMutex(Thread->Name);

      while(1/*thread_object::count <= 51*/)
      { 
         if(thread_object::count > count_max )
         {
             thread_object::LockCond_1(Thread->Name);
             cout<<endl<<"----------------------"<<endl;
         }

         cout<<"Increment : "<<thread_object::count<<endl;
         thread_object::count++;
         thread_object::UnlockMutex(Thread->Name);
         thread_object::UnlockCond_2(Thread->Name);
      }

      //thread_object::UnlockCond(Thread->Name);
      //thread_object::UnlockMutex(Thread->Name);
      return NULL;
}

void *thread_second(void *x)
{
      // sleep(1);
      thread_object *Thread;
      Thread = static_cast<thread_object *>(x);
      cout<<"thread friend fun: "<<pthread_self()<<" Name : "<<Thread->Name<<endl;
      thread_object::LockMutex(Thread->Name);

      while(1/*thread_object::count >= 0*/)
      {
          if(thread_object::count == 0)
          {
             thread_object::LockCond_2(Thread->Name);
             cout<<endl<<"--------------------"<<endl;
          }
          cout<<"Decrement : "<<thread_object::count<<endl;
          thread_object::count--;
          thread_object::UnlockMutex(Thread->Name);
          thread_object::UnlockCond_1(Thread->Name);
      }
      //thread_object::UnlockCond(Thread->Name);
      //thread_object::UnlockMutex(Thread->Name);
      //thread_object::DestroyMutex();
      //thread_object::DestroyCond();
      return NULL;
}

