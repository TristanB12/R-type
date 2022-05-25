/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** RenderSystem
*/

#pragma once

#include "ecs/generic/System/System.hpp"
#include "ecs/generic/Component/Drawable.hpp"
#include "ecs/generic/Component/Position.hpp"
#include "ecs/generic/Coordinator.hpp"
#include "SharedContext.hpp"

class RenderSystem : public System {
 public:

    void init(Coordinator &coordinator)
    {
        Signature signature;

        signature.set(coordinator.getComponentType<Drawable>());
        signature.set(coordinator.getComponentType<Position>());
        coordinator.setSystemSignature<RenderSystem>(signature);
    }

    void update(Coordinator &coordinator, SharedContext const &context)
    {
        for (auto const &entity: m_entities) {
            auto& pos = coordinator.getComponent<Position>(entity);
            auto& draw = coordinator.getComponent<Drawable>(entity);

            if (!draw.image.isVisible)
                continue;
            draw.image.sprite.setPosition(sf::Vector2f(pos.x, pos.y));
            draw.image.sprite.setTexture(context.ressources.getTexture(draw.image.textureName));
            if (draw.isAnimated) {
                Rect<int> mrect = draw.getCurrentAnimation().getCurrentFrame();
                sf::IntRect rect(mrect.top, mrect.left, mrect.width, mrect.height);
                draw.image.sprite.setTextureRect(rect);
                draw.getCurrentAnimation().nextFrame();
            }
            context.window.draw(draw.image.sprite);
        }
    }
};
