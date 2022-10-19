#include "BACThread.h"

BACThread::BACThread(const char* threadName)
    : m_destroyThread(false)
{
    THREAD_NAME = threadName;
}

BACThread::~BACThread() {
    Quit();
}

/**
 * Create thread
 * @param   void
 * */
int32_t BACThread::Start() {
    m_thread = std::thread(&BACThread::Process, this);
    m_thread.detach();
    m_threadID = m_thread.get_id();
    return 1;
}

/**
 * Post runnable vào looper để thực thi.
 * @param   funcPtr:    con trỏ hàm muốn thực thi
 * @param   data:       data cần thiết cho funcPtr
 * */
void BACThread::Post(FuncPtr funcPtr, void* data)
{
    Runnable runnable(funcPtr, data);

    m_queue.push(runnable);
    m_numJobRemaining++;
    m_cv.notify_all();
}

/**
 * Looper thực hiện xử lý runnable post bởi BACThread::Post
 * @param   This    BACThread Pointer
 * */
void* BACThread::Process(void *This) {
    BACThread* pBACThread = (BACThread*) This;
    while (!pBACThread->m_destroyThread)
    {
        while (pBACThread->m_queue.empty()) {
            std::unique_lock<std::mutex> lk(pBACThread->m_mutex);
            pBACThread->m_cv.wait(lk);
        }

        Runnable runnable = pBACThread->m_queue.front();
        pBACThread->m_queue.pop();

        if (runnable.funcPtr && runnable.data)
        {
            runnable.funcPtr(runnable.data);
        }
        pBACThread->m_numJobRemaining--;
    }
    return This;
}

/**
 * Abort thread ngay lập tức
 * @param   void
 * */
void BACThread::Quit() {
    m_destroyThread = true;
}

/**
 * Thực thi các Runnable chưa chạy xong rồi mới abort thread
 * @param   void
 * */
void BACThread::QuitSafely() {

    FuncPtr f = [](void* This){
        BACThread* pBACThread = (BACThread*) This;
        pBACThread->m_destroyThread = true;
    };

    Runnable runnable(f, this);
    m_queue.push(runnable);
}

