#include <Creature.h>
#include <raylib.h>
#include <raymath.h>

void Creature::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    // update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (isIdle)
            if (frame > maxFramesIdle)
                frame = 0;
        if (isEating)
            if (frame > maxFramesEating)
                frame = 0;
        if (isMoving)
            if (frame > maxFramesMoving)
                frame = 0;
    }

    // draw the character
    Rectangle source{frame * width, 0.f, rightLeft * width, height};
    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}