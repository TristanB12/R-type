/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** GameState
*/

#include "GameState.hpp"
#include "StateManager.hpp"

GameState::GameState(SharedContext &context) :
    AState(context),m_loader(m_coordinator), m_ennemies(m_coordinator), m_player_projectiles(m_coordinator)
{
    for (int i = 0; i < 20; i++) {
        auto e = m_loader.loadEntityFromFile("patapata.conf", "patapata" + std::to_string(i));
        m_ennemies.addEntity(e);
    }

    for (int i = 0; i < 100; i++) {
        auto e = m_loader.loadEntityFromFile("player_projectile.conf", "player_projectile" + std::to_string(i));
        m_player_projectiles.addEntity(e);
    }

    int i = 1;
    for (const struct Player &player : m_context.room.value().players) {
        m_loader.loadEntityFromFile("player" + std::to_string(i) + ".conf");
        (void)player;
        i++;
    }
    m_eventHandlers = {
        { sf::Event::KeyPressed, &GameState::handleKeyPressedEvent },
        { sf::Event::KeyReleased, &GameState::handleKeyReleasedEvent },
        { sf::Event::JoystickButtonPressed, &GameState::handleJoystickButtonPressedEvent }
    };
    SET_TCP_HANDLER(LEAVE_ROOM, onPlayerLeaveRoom);
    SET_UDP_HANDLER(MOVE, onMove);
    SET_UDP_HANDLER(SHOOT, onShoot);
    m_context.audio.playMusic("turbo_killer");
}

GameState::~GameState(void)
{
    m_context.audio.stopMusic();
    m_context.audio.playMusic("paradise_warfare");
}

bool GameState::handleEvent(const sf::Event &event)
{
    for (const auto &[eventType, handler] : m_eventHandlers) {
        if (event.type == eventType) {
            std::invoke(handler, this, event);
        }
    }
    return true;
}

void GameState::handleKeyPressedEvent(const sf::Event &event)
{
    Move::MovementType type = Move::NONE;
    Vector<float> acceleration;
    unsigned char anim = 'n';

    if (event.key.code == sf::Keyboard::Escape) {
        m_context.stateManager.navigate(States::ID::Pause, false);
    }
    if (m_animation == true)
        return;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        type = Move::ACCELERATION;
        anim = 'u';
        acceleration.y -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        type = Move::ACCELERATION;
        anim = 'd';
        acceleration.y += 1;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        type = Move::ACCELERATION;
        acceleration.x = -1;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        type = Move::ACCELERATION;
        acceleration.x += 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        Packet<rtype::IngameProtocol> packet(rtype::IngameProtocol::SHOOT);
        m_context.network.send(packet);
    }
    if (type != Move::NONE) {
        Packet<rtype::IngameProtocol> packet(rtype::IngameProtocol::MOVE);
        packet << acceleration.x << acceleration.y << anim;
        m_context.network.send(packet);
    }
}

void GameState::handleKeyReleasedEvent(const sf::Event &event)
{
    if (event.key.code == sf::Keyboard::Up) {
        // m_coordinator.getComponent<Drawable>("player1").getCurrentAnimation().reset();
        // m_coordinator.getComponent<Drawable>("player1").currentAnimation = "default";
    }

    if (event.key.code == sf::Keyboard::Down) {
        // m_coordinator.getComponent<Drawable>("player1").getCurrentAnimation().reset();
        // m_coordinator.getComponent<Drawable>("player1").currentAnimation = "default";
    }
}

void GameState::handleJoystickMovedEvent()
{
    Move::MovementType type = Move::NONE;
    Vector<float> acceleration;
    unsigned char anim = 'n';

    if (m_animation == true)
        return;
    if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -90.0f) {
        type = Move::ACCELERATION;
        anim = 'u';
        acceleration.y -= 1;
    }
    else if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 90.0f) {
        type = Move::ACCELERATION;
        anim = 'd';
        acceleration.y += 1;
    }
    if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -90.0f) {
         type = Move::ACCELERATION;
        acceleration.x = -1;
    } else if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 90.0f) {
        type = Move::ACCELERATION;
        acceleration.x += 1;
    }

    if (type != Move::NONE) {
        Packet<rtype::IngameProtocol> packet(rtype::IngameProtocol::MOVE);
        packet << acceleration.x << acceleration.y << anim;
        m_context.network.send(packet);
    }
}

void GameState::handleJoystickButtonPressedEvent(const sf::Event &event)
{
    if (event.joystickButton.button == 9) {
        m_context.stateManager.navigate(States::ID::Pause, false);
    }
    if (event.joystickButton.button == 0) {
        Packet<rtype::IngameProtocol> packet(rtype::IngameProtocol::SHOOT);
        m_context.network.send(packet);
    }
}

bool GameState::update(sf::Time dt)
{
    (void)dt;
    if (isOver()) {
       // m_context.stateManager.navigate(States::ID::GameLost, false);
    }
    beginAnimation();
    handleJoystickMovedEvent();
    m_coordinator.getSystem<SpawnEnnemies>()->update(m_coordinator, m_clock, m_ennemies);
    m_coordinator.getSystem<EnnemyBehavior>()->update(m_coordinator, m_clock, m_ennemies);
    m_coordinator.getSystem<PhysicSystem>()->update(m_coordinator);
    m_coordinator.getSystem<CollisionSystem>()->update(m_coordinator, m_ennemies);
    m_coordinator.getSystem<manageProjectileSystem>()->update(m_coordinator, m_player_projectiles);
    return true;
}

void GameState::draw()
{
    m_coordinator.getSystem<RenderSystem>()->update(m_coordinator, m_context);
}

void GameState::beginAnimation(void)
{
    if (!m_animation)
        return;
    float seconds = m_clock.getElapsedTime().asSeconds();
    if (seconds > 2.0)
        m_animation = false;
    std::vector<Vector<float> > pos;
    pos.push_back(Vector<float>(200, 100));
    pos.push_back(Vector<float>(200, 250));
    pos.push_back(Vector<float>(200, 400));
    pos.push_back(Vector<float>(200, 550));

    int i = 0;
    for (const struct Player &player : m_context.room.value().players) {
        m_coordinator.getComponent<Move>(player.colorToString()).type = Move::TARGET;
        m_coordinator.getComponent<Move>(player.colorToString()).targetPosition = pos[i];
        i++;
    }
}


void GameState::onPlayerLeaveRoom(Packet<rtype::Protocol> &response)
{
    std::string name = "";
    int playerID = 0;

    response >> playerID;
    for (auto &player: m_context.room.value().players) {
        if (player.id == playerID)
            name = player.colorToString();
    }
    m_coordinator.getComponent<Drawable>(name).image.isVisible = false;
}

void GameState::onMove(Packet<rtype::IngameProtocol> &response)
{
    Vector<float> acceleration;
    std::string name = "";
    unsigned char anim = 0;
    int id = 0;

    response >> id;    
    for (auto &player: m_context.room.value().players) {
        if (player.id == id)
            name = player.colorToString();
    }
    response >> anim >> acceleration.y >> acceleration.x;
    if (m_coordinator.getComponent<Drawable>(name).image.isVisible) {
        m_coordinator.getComponent<Move>(name).type = Move::ACCELERATION;
        auto &pos = m_coordinator.getComponent<Position>(name);
        m_coordinator.getComponent<Move>(name).acceleration = acceleration;

        if (pos.x < 0) {
            pos.x = 1;
            m_coordinator.getComponent<Move>(name).type = Move::NONE;
        }
        if (pos.y < 0) {
            pos.y = 1;
            m_coordinator.getComponent<Move>(name).type = Move::NONE;
        }
        if (pos.x > m_context.window.getSize().x) {
            pos.x = m_context.window.getSize().x - 33;
            m_coordinator.getComponent<Move>(name).type = Move::NONE;
        }
        if (pos.y > m_context.window.getSize().y) {
            pos.y = m_context.window.getSize().y - 33;
            m_coordinator.getComponent<Move>(name).type = Move::NONE;
        }
        switch (anim) {
        case 'n':
            m_coordinator.getComponent<Drawable>(name).currentAnimation = "default"; break;
        case 'u':
            m_coordinator.getComponent<Drawable>(name).currentAnimation = "up"; break;
        case 'd':
            m_coordinator.getComponent<Drawable>(name).currentAnimation = "down"; break;
        default: break;
        }
    }
}

void GameState::onShoot(Packet<rtype::IngameProtocol> &response)
{
    int id = 0;
    std::string name;
    response >> id;
    
    for (auto &player: m_context.room.value().players) {
        if (player.id == id)
            name = player.colorToString();
    }
    Drawable &draw = m_coordinator.getComponent<Drawable>(name);
    if (draw.image.isVisible == false)
        return;
    Position &pos_player = m_coordinator.getComponent<Position>(name);

    try {
        Entity e = m_player_projectiles.getAvailableEntity();
        Position &pos_projectile = m_coordinator.getComponent<Position>(e);
        Move &proj_move = m_coordinator.getComponent<Move>(e);
        m_coordinator.getComponent<Drawable>(e).image.isVisible = true;
        pos_projectile.x = pos_player.x + 30;
        pos_projectile.y = pos_player.y;
        proj_move.type = Move::TARGET;
        proj_move.targetPosition.x = 1500;
        proj_move.targetPosition.y = pos_projectile.y;
    } catch (EntitiesFlyWeightError &error) {
        (void)error;
    }
}

bool GameState::isOver(void)
{
    for (const struct Player &player : m_context.room.value().players) {
        if (m_coordinator.getComponent<Drawable>(player.colorToString()).image.isVisible)
            return false;
    }
    return true;
}
