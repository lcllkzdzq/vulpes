//
//  sync_queue.hpp
//  vulpes
//
//  Created by lcl on 2018/7/11.
//  Copyright © 2018 lcl. All rights reserved.
//

#ifndef sync_queue_hpp
#define sync_queue_hpp

#include "sync_status.hpp"

#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

namespace vuples {
    template<class _Tp>
    class sync_queue {
    private:
        queue<_Tp> _data;
        condition_variable _not_empty;
        mutable mutex _mtx;
        bool _closed;
        
        inline void enqueue(const _Tp& elem, unique_lock<mutex>& lk);
        inline sync_status try_enqueue(const _Tp& elem, unique_lock<mutex>& lk);
        inline sync_status wait_enqueue(const _Tp& elem, unique_lock<mutex>& lk);
        
        inline void dequeue(_Tp& elem, unique_lock<mutex>& lk);
        inline sync_status try_dequeue(_Tp& elem, unique_lock<mutex>& lk);
        inline sync_status wait_dequeue(_Tp& elem, unique_lock<mutex>& lk);
        
        inline bool empty(unique_lock<mutex>& lk) const;
        inline bool empty(lock_guard<mutex>& lk) const;
        
        inline bool closed(unique_lock<mutex>& lk) const;
        inline bool closed(lock_guard<mutex>& lk) const;
        
        inline void notify_not_empty_if_need(unique_lock<mutex>& lk);
        inline bool wait_until_not_empty_or_closed(unique_lock<mutex>& lk);
        
    public:
        inline sync_queue();
        inline ~sync_queue();
        
        inline void enqueue(const _Tp& elem);
        inline sync_status try_enqueue(const _Tp& elem);
        inline sync_status wait_enqueue(const _Tp& elem);
        
        
        inline void dequeue(_Tp& elem);
        inline sync_status try_dequeue(_Tp& elem);
        inline sync_status wait_dequeue(_Tp& elem);
        
        
        inline bool empty() const;
        inline bool closed() const;
        inline void close();
    };
    
    
    template<class _Tp>
    sync_queue<_Tp>::sync_queue() {
        
    }
    
    template<class _Tp>
    sync_queue<_Tp>::~sync_queue() {
        
    }
    
    template<class _Tp>
    void sync_queue<_Tp>::enqueue(const _Tp& elem) {
        unique_lock<mutex> lk(_mtx);
        enqueue(elem, lk);
    }
    
    template<class _Tp>
    void sync_queue<_Tp>::enqueue(const _Tp& elem, unique_lock<mutex>& lk) {
        _data.push(elem);
        notify_not_empty_if_need(lk);
    }
    
    template<class _Tp>
    sync_status sync_queue<_Tp>::try_enqueue(const _Tp& elem) {
        unique_lock<mutex> lk(_mtx);
        return try_enqueue(elem, lk);
    }
    
    template<class _Tp>
    sync_status sync_queue<_Tp>::try_enqueue(const _Tp& elem, unique_lock<mutex>& lk) {
        if (closed()) { return sync_status::closed; }
        enqueue(elem, lk);
        return sync_status::succes;
    }
    
    template<class _Tp>
    sync_status sync_queue<_Tp>::wait_enqueue(const _Tp& elem) {
        unique_lock<mutex> lk(_mtx);
        return wait_enqueue(elem, lk);
    }
    
    template<class _Tp>
    sync_status sync_queue<_Tp>::wait_enqueue(const _Tp& elem, unique_lock<mutex>& lk) {
        if (closed()) { return sync_status::closed; }
        enqueue(elem, lk);
        return sync_status::succes;
    }
    
    
    template<class _Tp>
    void sync_queue<_Tp>::dequeue(_Tp& elem) {
        unique_lock<mutex> lk(_mtx);
        denqueue(elem, lk);
    }
    
    template<class _Tp>
    void sync_queue<_Tp>::dequeue(_Tp& elem, unique_lock<mutex>& lk) {
        elem = move(_data.front());
        _data.pop();
    }
    
    template<class _Tp>
    sync_status sync_queue<_Tp>::try_dequeue(_Tp& elem) {
        unique_lock<mutex> lk(_mtx);
        return try_dequeue(elem, lk);
    }
    
    template<class _Tp>
    sync_status sync_queue<_Tp>::try_dequeue(_Tp& elem, unique_lock<mutex>& lk) {
        if (empty(lk)) {
            if (closed(lk)) { return sync_status::closed; };
            return sync_status::empty;
        }
        dequeue(elem, lk);
        return sync_status::succes;
    }
    
    template<class _Tp>
    sync_status sync_queue<_Tp>::wait_dequeue(_Tp& elem) {
        unique_lock<mutex> lk(_mtx);
        return wait_dequeue(elem, lk);
    }
    
    template<class _Tp>
    sync_status sync_queue<_Tp>::wait_dequeue(_Tp& elem, unique_lock<mutex>& lk) {
        const bool has_been_closed = wait_until_not_empty_or_closed(lk);
        if (has_been_closed) { return sync_status::closed; }
        dequeue(elem, lk);
        return sync_status::succes;
    }
    
    
    template<class _Tp>
    bool sync_queue<_Tp>::empty() const {
        lock_guard<mutex> lk(_mtx);
        return empty(lk);
    }
    
    template<class _Tp>
    bool sync_queue<_Tp>::empty(unique_lock<mutex>& lk) const {
        return _data.empty();
    }
    
    template<class _Tp>
    bool sync_queue<_Tp>::empty(lock_guard<mutex>& lk) const {
        return _data.empty();
    }
    
    
    template<class _Tp>
    bool sync_queue<_Tp>::closed() const {
        lock_guard<mutex> lk(_mtx);
        return closed(lk);
    }
    
    template<class _Tp>
    bool sync_queue<_Tp>::closed(unique_lock<mutex>& lk) const {
        return _closed;
    }
    
    template<class _Tp>
    bool sync_queue<_Tp>::closed(lock_guard<mutex>& lk) const {
        return _closed;
    }

    
    template<class _Tp>
    void sync_queue<_Tp>::notify_not_empty_if_need(unique_lock<mutex>& lk) {
        _not_empty.notify_one();
    }

    template<class _Tp>
    bool sync_queue<_Tp>::wait_until_not_empty_or_closed(unique_lock<mutex>& lk) {
        _not_empty.wait(lk, [this] { return !_data.empty() || _closed; });
        if (!empty(lk)) { return false; }
        return true;
    }
    
    
    template<class _Tp>
    void sync_queue<_Tp>::close() {
        {
            lock_guard<mutex> lk(_mtx);
            _closed = true;
        }
        
        _not_empty.notify_all();
    }
}

#endif /* sync_queue_hpp */
