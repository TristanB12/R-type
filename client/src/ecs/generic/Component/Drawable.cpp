/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-julien.pause
** File description:
** Drawable
*/

#include "ecs/generic/Component/Drawable.hpp"

Drawable::Drawable(const std::string textureName, bool visible)
{
    this->image.textureName = textureName;
    this->image.isVisible = visible;
    this->isAnimated = false;
    this->currentAnimation = "";
}

animationFrames &Drawable::getCurrentAnimation(void)
{
    return this->animations[this->currentAnimation];
}

animationFrames &Drawable::getAnimation(const std::string &name)
{
    return this->animations[name];
}