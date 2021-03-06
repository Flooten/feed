/*
 * FILNAMN:       messagequeue.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Herman Ekwall
 *                Marcus Eriksson
 *                Mattias Fransson
 * DATUM:         2012-12-12
 *
 */

#include "messagequeue.h"
#include "object.h"

namespace feed
{
    ////////////////////
    // Message

    MessageQueue::Message::Message(int type, int value, Object* sender)
        : type(type)
        , value(value)
        , sender(sender)
    {}

    ////////////////////
    // MessageQueue

    MessageQueue& MessageQueue::instance()
    {
        static MessageQueue instance_;
        return instance_;
    }

    void MessageQueue::pushMessage(const Message& msg)
    {
        queue_.push(msg);
    }

    bool MessageQueue::pullMessage(Message& msg)
    {
        if (queue_.empty())
            return false;

        msg = queue_.front();
        queue_.pop();

        return true;
    }
}
