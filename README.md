# What is this?

An implement of **Handler Thread** java-like in C++. 

# Usecases?

Running heavy task whithout blocking your running task.

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
    FuncPtr f = [](void* This) {
        HWController* pController = ((HWController*) This);
        if (!pController)
        {
            LOGE("pController nullptr");
            return;
        }
        pController->WaitZoomDoneTimeout(TIME_OUT_MOVE_LENS);
        
        MoveZoom(pController->m_requestZoomSpeed, pController->m_requestZoomStep);
        LOGD("MoveZoom(): speed = %d, step = %d", pController->m_requestZoomSpeed, pController->m_requestZoomStep);
        
        pController->MoveFocusToCalibPosition();
    };
Post it!

    //Post the function pointer that created earlier and object that you want to use inside thread.
    mHandlerThread->Post(f, pHWController);

# Test with example:
Build:

    cd examples/
    mkdir build
    cd build/
    cmake ..
    make
Run:
    
    ./cthreadqueue
