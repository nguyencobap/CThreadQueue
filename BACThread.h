#include <stdint.h>
#include <queue>
#include <pthread.h>

typedef void (*FuncPtr)(void*);

class Runnable
{
public:
    FuncPtr funcPtr;
    void* data;
    Runnable(FuncPtr funcPtr, void* data) {
        this->funcPtr = funcPtr;
        this->data = data;
    };
    ~Runnable() {
    };
};

class BACThread
{
public:
    BACThread(const char* threadName);
    ~BACThread();
    /**
     * Create thread
     * @param   void
     * */
    int32_t Start();
    /**
     * Abort thread ngay lập tức
     * @param   void
     * */
    void Quit();
    /**
     * Thực thi các Runnable chưa chạy xong rồi mới abort thread
     * @param   void
     * */
    void QuitSafely();
    /**
     * Post runnable vào looper để thực thi.
     * @param   funcPtr:    con trỏ hàm muốn thực thi
     * @param   data:       data cần thiết cho funcPtr
     * */
    void Post(FuncPtr funcPtr, void* data);
    /**
     * Lấy thread id
     * */
    int32_t GetThreadID() {
        return m_threadID;
    };

    int32_t GetNumJobRemaining() {
        return m_numJobRemaining;
    };
private:
    /**
     * Looper thực hiện xử lý runnable post bởi BACThread::Post
     * @param   This    BACThread Pointer
     * */
    static void* Process(void *This);

    std::queue<Runnable> m_queue;
    const char* THREAD_NAME;
    pthread_t m_threadID;
    bool m_destroyThread = false;
    pthread_cond_t m_cv = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t m_mutex = PTHREAD_MUTEX_INITIALIZER;
    int32_t m_numJobRemaining = 0;
};