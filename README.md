# What is this?

An implementation of **Handler Thread** java-like in C++. 

# Usecases?

Running heavy task one-by-one whithout blocking your running task.

# How to use?
Include header:
    
    #include "BACThread.h"

Create new Handler Thread object:

    mHandlerThread = new BACThread("My Thread");
Start it:

    result = mHandlerThread->Start();
    if (result != 0)
    {
        LOGE("mHandlerThread->Start() failed ret = %d", result);
    }

Create a function pointer of heavy-task job you want to schedule:

    //Function pointer with input is a void pointer object that use want to use inside thread.
    FuncPtr f = [](void* arg) {
        //Your heavy task
         int n = *((int*)arg);
        for(int i = 0; i < n; i++) 
        {
            LOGD("Task running i = %d", i)
        }
    };
Post it!

    //Post the function pointer that created earlier and object that you want to use inside thread.
    int loop_count = 100000;
    mHandlerThread->Post(f, &loop_count);

# Test with example:
Build:

    cd examples/
    mkdir build
    cd build/
    cmake ..
    make
Run:
    
    ./cthreadqueue
