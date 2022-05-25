/*
** EPITECH PROJECT, 2021
** babel
** File description:
** TSafeQueue
*/

#ifndef TSAFEQUEUE_HPP_
#define TSAFEQUEUE_HPP_

#include <mutex>
#include <queue>
#include <condition_variable>

template <typename T>
class TSafeQueue {
public:
    TSafeQueue(void) {};
    TSafeQueue(const TSafeQueue &other) = delete;
    ~TSafeQueue(void) { this->clear(); };

    const T &front(void) {
        std::lock_guard<std::mutex> lock(m_mutex);

        return m_queue.front();
    }

    bool isEmpty(void) {
        std::lock_guard<std::mutex> lock(m_mutex);

        return m_queue.empty();
    }

    size_t size(void) {
        std::lock_guard<std::mutex> lock(m_mutex);

        return m_queue.size();
    }

    T pop(void) {
        std::lock_guard<std::mutex> lock(m_mutex);

        auto elem = std::move(m_queue.front());
        m_queue.pop();
        return elem;
    }

    void clear(void) {
        std::lock_guard<std::mutex> lock(m_mutex);

        while (!m_queue.empty()) {
            m_queue.pop();
        }
    }

    void push(const T &data) {
        std::lock_guard<std::mutex> lock(m_mutex);

        m_queue.push(std::move(data));

        std::unique_lock<std::mutex> waitLock(m_mutexBlocking);
        m_blocking.notify_one();
    }

    void wait(void) {
        while (this->isEmpty()) {
            std::unique_lock<std::mutex> waitLock(m_mutexBlocking);
            m_blocking.wait(waitLock);
        }
    }

private:
    std::mutex m_mutex;
    std::queue<T> m_queue;
    std::condition_variable m_blocking;
    std::mutex m_mutexBlocking;
};

#endif /* !TSAFEQUEUE_HPP_ */
