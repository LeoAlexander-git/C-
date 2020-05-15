#include "thread_object.h"

int main()
{
    thread_object Thread[2];
    Thread[0].name("Thread A");
    Thread[1].name("Thread B");

    for(int N = 0; N < 2; N++)
    {
    	Thread[N].run();
    }

    for(int N = 0; N < 2; N++)
    {
        Thread[N].join();
    }

    return 0;
}
