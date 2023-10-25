#ifndef HERBIVORE_H
#define HERBIVORE_H
#include <Creature.h>
#include <raylib.h>

class Herbivore : public Creature
{
public:
    Herbivore(Vector2 pos, Texture2D idle_texture, Texture2D run_texture, Texture2D eating_texture, int max_frames_idle, int max_frames_run, int max_frames_eating);
    virtual Vector2 getScreenPos() override;
    void tick(float deltaTime);
    bool getIsBeingTargeted() { return isBeingTargeted; }
    void setIsBeingTargeted(bool isTargeted) { isBeingTargeted = isTargeted; }
    void setTargetedBy(Vector2 targetByCreature) { targetedByVector = targetByCreature; }
    bool getIsBeingEaten() { return isBeingEaten; }
    void setIsBeingEaten(bool isEaten) { isBeingEaten = isEaten; }
    float getHealth() { return health; }
    void setHealth(float newHealth) { health = newHealth; }
    float getDuplicationValue() { return duplicationValue; }
    void resetDuplicationValue() { duplicationValue = 10.f; }
    void setIsEating(bool isEatingIn) { isEating = isEatingIn; }

private:
    float health{10};
    bool isBeingTargeted{false};
    bool isBeingEaten{false};
    Vector2 targetedByVector = {};
    float duplicationValue{10.f};
    float eatingPace{0.5f};
    bool isSearchingGrass = false;
    float grassSearchRange{200.f};
    float hungerLevel{30.f};

    void runAwayChangeWorldPos();
    void eatingGrassAndDuplicating(float deltaTime);
    void lookForFeedingGround();
    void eatingOrLookingForFood(float deltaTime);
};
#endif