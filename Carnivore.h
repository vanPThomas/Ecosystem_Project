#ifndef CARNIVORE_H
#define CARNIVORE_H
#include <Creature.h>
#include <raylib.h>
#include <Herbivore.h>
#include <list>

class Carnivore : public Creature
{
public:
    Carnivore(Vector2 pos, Texture2D idle_texture, Texture2D run_texture, Texture2D eating_texture, int max_frames_idle, int max_frames_run, int max_frames_eating);
    virtual Vector2 getScreenPos() override;
    void tick(float deltaTime, std::list<Herbivore *> &herbivores);
    Herbivore *getClosestHerbivore(std::list<Herbivore *> &herbivores);
    void setHerbivoreTarget(Herbivore *herbivore) { herbivoreTarget = herbivore; }
    float getDuplicationValue() { return duplicationValue; }
    void resetDuplicationValue() { duplicationValue = 20.f; }

private:
    Herbivore *herbivoreTarget;
    float eatingDamage{0.5f};
    float eatingPace{0.5f};
    float duplicationValue{20.f};
    float foodSearchRange{300.f};

    void changeWorldPos();
    void eatTargetedHerbivore(float deltaTime);
};
#endif