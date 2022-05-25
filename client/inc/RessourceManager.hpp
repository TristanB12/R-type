/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** RessourceManager
*/

#pragma once

#include <iostream>
#include <unordered_map>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class RessourceManager {
public:
    RessourceManager(const std::string &defaultFontName)
    {
        this->loadRessources<sf::Texture>(TEXTURES_DIR_PATH);
        this->loadRessources<sf::Font>(FONTS_DIR_PATH);
        this->loadRessources<sf::SoundBuffer>(SOUND_DIR_PATH);
        this->loadMusicsPath(MUSIC_DIR_PATH);
        this->setDefaultFont(defaultFontName);
    }
    virtual ~RessourceManager(void) = default;

    sf::Texture &getTexture(const std::string &textureName)
    {
        return m_textures[textureName];
    }

    sf::Font &getFont(const std::string &fontName)
    {
        return m_fonts[fontName];
    }

    sf::Font &getDefaultFont(void)
    {
        return m_fonts[m_defaultFontName];
    }

    void setDefaultFont(const std::string &defaultFontName)
    {
        m_defaultFontName = defaultFontName;
    }

    bool soundExists(const std::string &soundName)
    {
        return m_sounds.find(soundName) != m_sounds.end();
    }

    sf::SoundBuffer &getSound(const std::string &soundName)
    {
        return m_sounds[soundName];
    }

    bool musicExists(const std::string &musicName)
    {
        return m_musicPathMap.find(musicName) != m_musicPathMap.end();
    }

    std::string getMusicPath(const std::string &musicName)
    {
        return m_musicPathMap[musicName];
    }

private:
    template <typename T_Ressource>
    void loadRessources(const std::string &dirPath) {
        for (auto const &file : std::filesystem::directory_iterator(dirPath)) {
            if (!file.is_regular_file()) {
                continue;
            }
            T_Ressource ressource;
            if (!ressource.loadFromFile(file.path().string())) {
                std::cerr << "Couldn't load ressource : \""
                        << file.path().filename() << "\"" << std::endl;
                continue;
            }
            this->insertRessource(file.path().stem().string(), std::move(ressource));
        }
    }

    void loadMusicsPath(const std::string &dirPath)
    {
        for (auto const &file : std::filesystem::directory_iterator(dirPath)) {
            if (file.is_regular_file()) {
                m_musicPathMap[file.path().stem().string()] = file.path().string();
            }
        }
    }

    void insertRessource(const std::string &stem, sf::Texture texture)
    {
        m_textures[stem] = texture;
    }

    void insertRessource(const std::string &stem, sf::Font font)
    {
        m_fonts[stem] = font;
    }

    void insertRessource(const std::string &stem, sf::SoundBuffer sound)
    {
        m_sounds[stem] = sound;
    }

    const std::string TEXTURES_DIR_PATH = "./assets/textures/";
    const std::string FONTS_DIR_PATH = "./assets/fonts/";
    const std::string SOUND_DIR_PATH = "./assets/sounds/";
    const std::string MUSIC_DIR_PATH = "./assets/musics/";
    std::unordered_map<std::string, sf::Texture> m_textures;
    std::unordered_map<std::string, sf::Font> m_fonts;
    std::unordered_map<std::string, sf::SoundBuffer> m_sounds;
    std::unordered_map<std::string, std::string> m_musicPathMap;
    std::string m_defaultFontName;
};