/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** AudioManager
*/

#pragma once

#include <SFML/Audio.hpp>
#include "RessourceManager.hpp"

class AudioManager {
public:
    AudioManager(RessourceManager &ressources) :
        m_ressources(ressources)
    {}
    virtual ~AudioManager(void) = default;

    void playMusic(const std::string &musicName, bool loop = true)
    {
        if (!m_ressources.musicExists(musicName)) {
            std::cerr << "Music " << musicName << " not found" << std::endl;
            return;
        }
        std::string musicPath = m_ressources.getMusicPath(musicName);
        if (!m_music.openFromFile(musicPath)) {
            std::cerr << "Couldn't load " << musicPath << std::endl;
            return;
        }
        if (this->isMusicPlaying()) {
            this->stopMusic();
        }
        m_music.setLoop(loop);
        m_music.play();
    }

    bool isMusicPlaying(void)
    {
        return m_music.getStatus() == sf::SoundSource::Status::Playing;
    }

    void stopMusic(void)
    {
        m_music.stop();
    }

    void playSound(const std::string &soundName)
    {
        if (!m_ressources.soundExists(soundName)) {
            std::cerr << "Sound " << soundName << "not found" << std::endl;
            return;
        }
        sf::Sound sound(m_ressources.getSound(soundName));
        sound.play();
    }

private:
    RessourceManager &m_ressources;
    sf::Music m_music;
};
