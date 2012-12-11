/*
 * FILNAMN:       messagequeue.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Herman Ekwall
 *                Marcus Eriksson
 *                Mattias Fransson
 * DATUM:         2012-12-12
 *
 * BESKRIVNING: Meddelandekö. Tar emot meddelanden från alla object, GameWorld läser kön
 *              och utför instruktionerna. MessageQueue implementeras som en singleton.
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
                NEW_GAME,
                RESUME_GAME,
                LOAD_GAME,
                QUIT_GAME,
                PAUSE_GAME,
                EXIT_TO_MAIN_MENU,
                CREDITS,
                NEXT_WORLD,
                FIRE,
                ADD_HEALTH,
                ADD_ARMOR,
                ADD_WEAPON,
                CHECKPOINT,
				PLAYER_DEAD,
				ENEMY_DEAD,
                BOSS_DEAD,
                PROJECTILE_DEAD,
                EFFECT_DEAD,
                INTOBJECT_DEAD,
                ENVOBJECT_DEAD,
                SPAWN_WALL,
                SPAWN_ADDS_PHASE_TWO,
                SPAWN_ADDS_PHASE_THREE,
                FIRST_BOSS_DEAD,
                DEAD,
                WAIT_DONE
            };

            Message(int type = 0, int value = 0, Object* sender = nullptr);

            int type = 0;
            int value = 0;
            Object* sender = nullptr;
        };

        static MessageQueue& instance();

        void pushMessage(const Message& msg);
        bool pullMessage(Message& msg);

    private:
        MessageQueue() = default;
        MessageQueue(const MessageQueue&) = delete;
        MessageQueue& operator=(const MessageQueue&) = delete;

        std::queue<Message> queue_;
    };
}

#endif
