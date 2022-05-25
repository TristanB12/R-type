/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-julien.pause
** File description:
** collisionSystem
*/

#ifndef COLLISIONSYSTEM_HPP_
#define COLLISIONSYSTEM_HPP_

#include "Hitbox.hpp"
#include "ecs/generic/Entity/EntitiesFlyWeight.hpp"
#include "ecs/generic/System/System.hpp"
#include <SFML/Window/Event.hpp>

class CollisionSystem : public System {
    public:
        void init(Coordinator &coordinator)
        {
            Signature signature;

            signature.set(coordinator.getComponentType<Position>());
            signature.set(coordinator.getComponentType<Hitbox>());
            signature.set(coordinator.getComponentType<Drawable>());
            coordinator.setSystemSignature<CollisionSystem>(signature);
        }

        void update(Coordinator &coordinator, EntitiesFlyWeight &ennemies)
        {
            for (auto &entity: m_entities) {
                Drawable &draw = coordinator.getComponent<Drawable>(entity);
                if (!draw.image.isVisible)
                    continue;
                collided(const_cast<Entity &>(entity), coordinator, ennemies);
            }
        }
    private:
        void collided(Entity &entity, Coordinator &coordinator, EntitiesFlyWeight &ennemies)
        {
            for (auto const &entity2: m_entities) {
                if (entity != entity2) {
                    Drawable &draw2 = coordinator.getComponent<Drawable>(entity2);
                    if (!draw2.image.isVisible)
                        continue;
                    Hitbox &hitbox = coordinator.getComponent<Hitbox>(entity);
                    Drawable &draw = coordinator.getComponent<Drawable>(entity);
                    Hitbox &hitbox2 = coordinator.getComponent<Hitbox>(entity2);
                    if (draw.image.sprite.getGlobalBounds().intersects(draw2.image.sprite.getGlobalBounds())) {
                        if (hitbox.getCollisionType() == 1 && hitbox2.getCollisionType() == 1 &&
                            hitbox.isFriendly() != hitbox2.isFriendly()) {
                                draw2.image.isVisible = false;
                                draw.image.isVisible = false;
                                reset(entity, entity2, ennemies, coordinator);
                            }
                    }
                }
            }
        }

        void reset(Entity e1, Entity e2, EntitiesFlyWeight &ennemies, Coordinator &coordinator)
        {
            Hitbox box1 = coordinator.getComponent<Hitbox>(e1);
            Hitbox box2 = coordinator.getComponent<Hitbox>(e2);
            Position &pos1 = coordinator.getComponent<Position>(e1);
            Position &pos2 = coordinator.getComponent<Position>(e2);

            pos1.x = -100;
            pos1.y = -100;
            pos2.x = -100;
            pos2.y = -100;
            if (box1.isFriendly() == 0) {
                ennemies.setEntityAvailability(e1, true);
            }
            if (box2.isFriendly() == 0) {
                ennemies.setEntityAvailability(e2, true);
            }
        }
};

#endif /* !COLLISIONSYSTEM_HPP_ */
