/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-julien.pause
** File description:
** Ennemy
*/

#ifndef ENNEMY_HPP_
#define ENNEMY_HPP_

#include <string>
#include <vector>
#include <utility>

class Ennemy {
    public:
        Ennemy(int hp = 0, std::vector<std::pair<int, int>> moveTargets = {})
        {
            _hp = hp;
            _moveTargets = moveTargets;
            _move = 0;
            _currentMove = 0;
        };
        ~Ennemy() {};

        inline void setHp(int hp) {_hp = hp;}

        inline std::vector<std::pair<int, int>> getMoves() const {return _moveTargets;}
        
        inline int getCurrentMove() const {return _currentMove;}

        void setMove() {
            if (_currentMove + 1 < static_cast<int>(_moveTargets.size())) {
                _currentMove++;
            } else
                _currentMove = 0;
        }

    protected:
    private:
        int _hp;
        int _move;
        int _currentMove;
        std::vector<std::pair<int, int>> _moveTargets;
};

#endif /* !ENNEMY_HPP_ */
