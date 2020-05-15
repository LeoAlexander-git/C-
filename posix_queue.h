#ifndef __POSIX_QUEUE_H
#define __POSIX_QUEUE_H

#include "thread_object.h"

class user_thread : public thread_object
{

      private:
	 
    	 posix_queue *PosixQueue;

      protected:

         virtual void do_somthing(void);
	
      public:
	
	 user_thread(void);
	 ~user_thread(void);
};

#endif
