#include <Herbivore.h>
#include <raylib.h>
#include <list>
#include <raymath.h>
#include <random>

Herbivore::Herbivore(Vector2 pos, Texture2D idle_texture, Texture2D run_texture, Texture2D eating_texture, int max_frames_idle, int max_frames_run, int max_frames_eating)
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
    speed = 0.5f;
}

void Herbivore::tick(float deltaTime)
{
    if (!getAlive())
        return;
    // herbivore run target
    runAwayChangeWorldPos();

    // herbivore is filling up
    eatingOrLookingForFood(deltaTime);

    velocity = {};

    Creature::tick(deltaTime);
    targetedByVector = {};
}
Vector2 Herbivore::getScreenPos()
{
    return worldPos;
}

void Herbivore::runAwayChangeWorldPos()
{
    if (targetedByVector.x != 0 && targetedByVector.y != 0)
    {
        velocity = Vector2Subtract(getScreenPos(), targetedByVector);
        worldPosLastFrame = worldPos;

        if (Vector2Length(velocity) < collisionRadius)
            velocity = {};

        if (Vector2Length(velocity) > 0.0)
        {
            // set worldPos = worldPos + velocity
            worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));

            if (worldPos.x < 75.f)
                worldPos.x = 75.f;
            if (worldPos.x > 855.f)
                worldPos.x = 855.f;
            if (worldPos.y < 75.f)
                worldPos.y = 75.f;
            if (worldPos.y > 800.f)
                worldPos.y = 800.f;

            velocity.x < 0.f ? rightLeft = 1.f : rightLeft = -1.f; // if else statement
            texture = run;
            isMoving = true;
            isIdle = false;
            isEating = false;
            isSearchingGrass = false;
        }
        else
        {
            texture = idle;
            isIdle = true;
            isEating = false;
            isMoving = false;
            isSearchingGrass = false;
        }
    }
    if (!isBeingTargeted)
        texture = idle;
}

void Herbivore::eatingGrassAndDuplicating(float deltaTime)
{
    if (!isBeingEaten && !isBeingTargeted)
    {
        texture = eat;
        duplicationValue -= eatingPace * deltaTime;
        isEating = true;
        isMoving = false;
        isIdle = false;
    }
}
void Herbivore::lookForFeedingGround()
{
    std::random_device rd;                                                      // obtain a random number from hardware
    std::mt19937 gen(rd());                                                     // seed the generator
    std::uniform_int_distribution<> distr(-grassSearchRange, grassSearchRange); // define the range
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

void Herbivore::eatingOrLookingForFood(float deltaTime)
{
    if (isSearchingGrass)
    {
        velocity = Vector2Subtract(feedingLocation, getScreenPos());

        if (Vector2Length(velocity) < collisionRadius)
        {
            velocity = {};
            isEating = true;
            isSearchingGrass = false;
        }

        worldPosLastFrame = worldPos;
        if (Vector2Length(velocity) != 0.0)
        {
            // set worldPos = worldPos + velocity
            worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
            velocity.x < 0.f ? rightLeft = 1.f : rightLeft = -1.f; // if else statement
            texture = run;
        }
    }
    else if (!isEating)
    {
        isSearchingGrass = true;
        lookForFeedingGround();
    }
    else
    {
        eatingGrassAndDuplicating(deltaTime);
    }
}