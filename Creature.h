#ifndef CREATURE_H
#define CREATURE_H
#include <raylib.h>

class Creature
{
public:
    void setAlive(bool isAlive) { alive = isAlive; }
    bool getAlive() { return alive; }
    virtual void tick(float deltaTime);
    virtual Vector2 getScreenPos() = 0;
    float getRadius() { return searchRadius; }

private:
    bool alive{true};

protected:
    Texture2D texture{};
    Texture2D idle{};
    Texture2D run{};
    Texture2D eat{};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    // 1: facing right, -1: facing left
    float rightLeft{1.f};
    // animation variables
    float runningTime{};
    int frame{};
    int maxFramesIdle{5};
    int maxFramesMoving{2};
    int maxFramesEating{4};
    bool isIdle{true};
    bool isMoving{false};
    bool isEating{false};
    float updateTime{1.f / 12.f};
    float speed{1.f};
    float width{};
    float height{};
    float scale{2.f};
    Vector2 velocity{};
    float searchRadius{200.f};
    float collisionRadius{28.f};
    Vector2 feedingLocation = {};
};
#endif