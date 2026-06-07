#if !defined(__SHARED_QUEUE_H__)
#define __SHARED_QUEUE_H__

#include "CppTemplates/Templates.h"
#include "Mutex.h"
#include "ConditionalVariable.h"
#include <queue>
#include <vector>
#include <cstdio>

namespace Utils
{
    template<class T>
    class SharedQueue
    {
    public:
        SharedQueue( const size_t capacity = DefaultQueueCapacity )    :
            mCapacity(capacity),
            mMutex(new Mutex),
            mCv(new ConditionalVariable)
        {
        }

        ~SharedQueue()
        {
            delete mMutex;
            delete mCv;
        }

        const T& Top() const
        {
            T res= T();

            mMutex->Lock();
            if( mQueueInstance.size() ) res = mQueueInstance.top();
            mMutex->Unlock();

            return res;
        }

        void Pop()
        {
            mMutex->Lock();
            if( mQueueInstance.size() ) mQueueInstance.pop();
            mMutex->Unlock();
        }

        void Clear()
        {
            mMutex->Lock();
            if( mQueueInstance.size() ) mQueueInstance.Clear();
            mMutex->Unlock();
        }

        void Push( const T& item, const bool broadcast = false )
        {
            mMutex->Lock();
            if( mQueueInstance.size() < mCapacity ) mQueueInstance.push( item );
            mMutex->Unlock();

            if(broadcast )
            {
                mCv->Broadcast();
            }
            else
            {
                mCv->Signal();
            }
        }

        void PushAll( const std::vector<T>& items )
        {
            for( const T& item : items )
            {
                this->Push(item);
            }
        }

        void WaitNewElement( )
        {
            mMutex->Lock();

            while( mQueueInstance->empty() == true )
            {
                mCv->Wait( (*mMutex) );
            }

            mMutex->Lock();
        }

        void WaitNewElementTimed( const long seconds, const long nanoseconds )
        {
            mMutex->Lock();

            if( mQueueInstance->empty() == true )
            {
                mCv->TimedWait( (*mMutex), seconds, nanoseconds );
            }

            mMutex->Lock();
        }

        bool IsEmpty() const
        {
            mMutex->Lock();
            bool res = mQueueInstance.empty();
            mMutex->Unlock();

            return res;
        }

        bool IsFull() const
        {
            mMutex->Lock();
            bool res = mQueueInstance.size() == mCapacity;
            mMutex->Unlock();

            return res;
        }

        size_t GetSize() const
        {
            size_t res;

            mMutex->Lock();
            res = mQueueInstance.size();
            mMutex->Unlock();

            return res;
        }

        size_t GetCapacity() const
        {
            size_t res;

            mMutex->Lock();
            res = mCapacity;
            mMutex->Unlock();

            return res;
        }
    private:
        const size_t mCapacity;
        std::queue<T> mQueueInstance;
        Mutex *mMutex;
        ConditionalVariable * mCv;
        static constexpr size_t DefaultQueueCapacity = 1000;
    CLASS_IS_NON_COPYABLE(SharedQueue);
    };
} // namespace Utils


#endif // __SHARED_QUEUE_H__
