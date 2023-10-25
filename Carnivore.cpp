#include <Carnivore.h>
#include <raylib.h>
#include <list>
#include <MethodLibrary.h>
#include <Creature.h>
#include <raymath.h>

Carnivore::Carnivore(Vector2 pos, Texture2D idle_texture, Texture2D run_texture, Texture2D eating_texture, int max_frames_idle, int max_frames_run, int max_frames_eating)
{
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    eat = eating_texture;
    maxFramesEating = max_frames_eating;
    maxFramesIdle = max_frames_idle;
    maxFramesMoving = max_frames_run;
    width = texture.width / maxFramesIdle;
    height = texture.height;
    speed = 1.f;
}

Vector2 Carnivore::getScreenPos()
{
    return worldPos;
}
Herbivore *Carnivore::getClosestHerbivore(std::list<Herbivore *> &herbivores)
{
    Vector2 carnPos{getScreenPos()};
    float radius{getRadius()};
    Herbivore *closeHerbivore{NULL};
    for (auto herbivore : herbivores)
    {
        Vector2 herbPos = herbivore->getScreenPos();
        float distance = getDistanceBetweenVectors(carnPos, herbPos);
        if (!herbivore->getIsBeingTargeted() && !herbivore->getIsBeingEaten())
            if (distance <= radius && distance >= -radius)
                if (closeHerbivore != NULL && distance < getDistanceBetweenVectors(carnPos, closeHerbivore->getScreenPos()))
                    closeHerbivore = herbivore;
                else if (closeHerbivore == NULL)
                    closeHerbivore = herbivore;
    }
    if (closeHerbivore != NULL)
    {
        closeHerbivore->setIsBeingTargeted(true);
        closeHerbivore->setTargetedBy(worldPos);
    }
    return closeHerbivore;
}
void Carnivore::tick(float deltaTime, std::list<Herbivore *> &herbivores)
{
    herbivoreTarget = getClosestHerbivore(herbivores);

    if (!getAlive())
        return;
    // carnivore run target
    changeWorldPos();
    // carnivore eat target
    eatTargetedHerbivore(deltaTime);

    velocity = {};

    Creature::tick(deltaTime);
}

void Carnivore::changeWorldPos()
{
    if (herbivoreTarget != NULL)
    {
        // get closer to targeted herbivore
        velocity = Vector2Subtract(herbivoreTarget->getScreenPos(), getScreenPos());
        feedingLocation = {};
    }
    else
    {
        // wander off to new potential feeding location
        if (Vector2Length(Vector2Subtract(feedingLocation, getScreenPos())) <= collisionRadius || feedingLocation.x <= 1.f)
        {
            std::random_device rd;                                                    // obtain a random number from hardware
            std::mt19937 gen(rd());                                                   // seed the generator
            std::uniform_int_distribution<> distr(-foodSearchRange, foodSearchRange); // define the range
            Vector2 newLocation = {distr(gen), distr(gen)};

            feedingLocation = Vector2Add(getScreenPos(), newLocation);

            if (feedingLocation.x < 75.f)
                feedingLocation.x = 75.f;
            if (feedingLocation.x > 855.f)
                feedingLocation.x = 855.f;
            if (feedingLocation.y < 75.f)
                feedingLocation.y = 75.f;
            if (feedingLocation.y > 800.f)
                feedingLocation.y = 800.f;
        }
        velocity = Vector2Subtract(feedingLocation, getScreenPos());
    }
    if (Vector2Length(velocity) < collisionRadius)
        velocity = {};

    worldPosLastFrame = worldPos;
    if (Vector2Length(velocity) != 0.0)
    {
        // set worldPos = worldPos + velocity
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.f ? rightLeft = 1.f : rightLeft = -1.f; // if else statement
        texture = run;
    }
    else
    {
        texture = idle;
    }
}

void Carnivore::eatTargetedHerbivore(float deltaTime)
{
    if (herbivoreTarget != NULL)
    {
        if (Vector2Length(velocity) <= 0.f)
        {
            texture = eat;
            float herbHealth = herbivoreTarget->getHealth();
            herbHealth -= eatingDamage * deltaTime;
            herbivoreTarget->setHealth(herbHealth);
            duplicationValue -= eatingPace * deltaTime;
        }
        if (herbivoreTarget->getHealth() <= 0.f)
        {
            herbivoreTarget->setAlive(false);
            herbivoreTarget = NULL;
            texture = idle;
        }
    }
}