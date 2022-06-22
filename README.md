# What is this?

An implement of **Handler Thread** java-like to C++. 

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

    mHandlerThread->Post(f, pHWController);
