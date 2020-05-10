//
// Created by Nwolf on 4/21/2020.
//

#ifndef WOLFNATHANHW6_SAFEQUEUE_H
#define WOLFNATHANHW6_SAFEQUEUE_H


#include <semaphore.h>
#include <queue>


using namespace std;



template <class T>
class SafeQueue {

private:
    sem_t semaphore{};
    pthread_mutex_t mutex{};
    queue<T> q;


public:
    SafeQueue();

    void enqueue(T t);

    T dequeue();
};



template<class T>
SafeQueue<T>::SafeQueue() {
    pthread_mutex_unlock(&this->mutex);
    sem_init(&this->semaphore, 0, 0);
}

template<class T>
void SafeQueue<T>::enqueue(T t) {
    pthread_mutex_lock(&this->mutex);
    this->q.push(t);
    pthread_mutex_unlock(&this->mutex);
    sem_post(&this->semaphore);
}

template<class T>
T SafeQueue<T>::dequeue() {
    sem_wait(&this->semaphore);
    pthread_mutex_lock(&this->mutex);
    T receivedAttack = {};
    receivedAttack = this->q.front();
    q.pop();
    pthread_mutex_unlock(&this->mutex);
    return receivedAttack;
}




#endif //WOLFNATHANHW6_SAFEQUEUE_H
