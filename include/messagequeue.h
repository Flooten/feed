/*
 * FILNAMN:       messagequeue.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Herman Ekwall
 *                Marcus Eriksson
 *                Mattias Fransson
 * DATUM:         2012-11-16
 *
 * BESKRIVNING: Meddelandekö. Tar emot meddelanden från alla object, GameWorld läser kön
 *              och utför instruktionerna.
 *
 */

#ifndef FEED_MESSAGE_QUEUE_H
#define FEED_MESSAGE_QUEUE_H

#include <queue>

namespace feed
{
    class Object;

    class MessageQueue
    {
    public:
        struct Message
        {
            enum
            {
                FIRE,
                ADD_HEALTH,
                ADD_ARMOR,
                ADD_WEAPON,
                CHECKPOINT
            };

            Message(int type = 0, int value = 0, Object* sender = nullptr);

            int type = 0;
            int value = 0;
            Object* sender = nullptr;
        };

        void pushMessage(const Message& msg);
        bool pullMessage(Message& msg);

    private:
        std::queue<Message> queue_;
    };
}

#endif
