PROJECT(CThreadQueueExample)

INCLUDE_DIRECTORIES(..)

ADD_EXECUTABLE(cthreadqueue CThreadQueue.cpp ../BACThread.cpp)

TARGET_LINK_LIBRARIES(cthreadqueue)
