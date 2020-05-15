#include "posix_queue.h"
#include <fstream>

bool Found = false;

user_thread::user_thread(void)
{
     PosixQueue = new posix_queue("queue_name");
     PosixQueue->queueFlage(O_RDONLY);
     PosixQueue->messageSize(14);
     PosixQueue->maxMessages(4);
}

user_thread::~user_thread(void)
{
     delete PosixQueue;
}

void user_thread::do_something(void)
{
     ofstream Fout;
     string FileName;
     string Value;

     if(PosixQueue->open())
     {
        PosixQueue->receive(FileName);
        ifstream Fin(FileName.c_str());
        string FileOut(FileName);
        FileOut.append(".out");
        Fout.open(FileOut.c_str());
     
        while(!Fin.eof() && !Fin.fail() && !Found)
        {
             getline(Fin, value);
             if(!Fin.eof() && !Fin.fail() && !Found)
             {
                if(Value == MagicCode)
                {  
                   Found = true;
                }
             }
        }

        Fin.close();
        Fout.close();
    }
}

