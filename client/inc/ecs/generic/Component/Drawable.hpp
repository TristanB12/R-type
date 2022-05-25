/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-julien.pause
** File description:
** drawable
*/

#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Rect.hpp"

typedef struct animationFrames_s {
    std::vector<Rect<int> > frames;
    bool                    isLoop;
    bool                    isParallax;
    int                     offset;
    Rect<int>               parallaxOffset;
    float                   time;

    animationFrames_s(bool loop = true)
     :  isLoop(loop), isParallax(false), offset(0), parallaxOffset(Rect<int>(0, 0, 0, 0)), time(0) {}

    Rect<int> getCurrentFrame(void) const
    {
        return frames[offset];
    }

    void nextFrame(void)
    {
        size_t len = frames.size();

        if (isParallax) {
            frames[offset] += parallaxOffset;
            return;
        }
        offset++;
        if (!isLoop && offset >= static_cast<int>(len))
            offset = static_cast<int>(len) - 1;
        if (offset >= static_cast<int>(len))
            offset = 0;
    }

    void prevFrame(void)
    {
        size_t len = frames.size();

        if (isParallax) {
            frames[offset] -= parallaxOffset;
            return;
        }
        offset--;
        if (!isLoop && offset <= 0)
            offset = 0;
        if (offset < 0)
            offset = static_cast<int>(len) - 1;
    }

    void reset(void)
    {
        offset = 0;
    }

} animationFrames;

typedef struct image_s {
    std::string textureName;
    sf::Sprite sprite;
    bool isVisible;

} Image;

class Drawable {
 public:
    Image                                               image;
    bool                                                isAnimated;
    std::unordered_map<std::string, animationFrames>    animations;
    std::string                                         currentAnimation;

    Drawable(const std::string textureName = "", bool visible = false);

    animationFrames &getCurrentAnimation(void);

    animationFrames &getAnimation(const std::string &name);

    friend std::ostream &operator<<(std::ostream &cout, const Drawable &sprite)
    {
        cout << "[IMAGE]: {isVisible: " << sprite.image.isVisible << ", texturePath:" << sprite.image.textureName << "}";
        return cout;
    }
};

#endif /* !DRAWABLE_HPP_ */