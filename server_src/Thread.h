//
// Created by leogm99 on 22/5/21.
//

#ifndef TP3_SERVER_THREAD_H
#define TP3_SERVER_THREAD_H

#include <thread>

class Thread {
private:
    std::thread handler;
protected:
    virtual void run() = 0;
public:
    Thread() = default;

    // no copy i said
    Thread(const Thread& other) = delete;
    Thread& operator= (const Thread& other) = delete;

    Thread(Thread&& other) noexcept;
    Thread& operator= (Thread&& other) noexcept;

    void start();
    void join();

    virtual ~Thread() = default;
};


#endif //TP3_SERVER_THREAD_H
