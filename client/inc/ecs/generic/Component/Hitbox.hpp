/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-julien.pause
** File description:
** Hitbox
*/

#ifndef HITBOX_HPP_
#define HITBOX_HPP_

#include <utility>

class Hitbox {
    public:
        // Type is here to assert what kind of collision will take place (either an ennemy crashing in us or our ship being blocked by a wall)
        Hitbox(int friendly = 1, bool type = false)
        {
            _collisionType = type;
            _friendly = friendly;
        }

        ~Hitbox() {};
        inline bool getCollisionType() const {return _collisionType;}
        inline int isFriendly() const {return _friendly;}

    protected:
    private:
        bool _collisionType;
        int _friendly;
};

#endif /* !HITBOX_HPP_ */
