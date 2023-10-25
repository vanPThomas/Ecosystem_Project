#include <raylib.h>
#include <Herbivore.h>
#include <random>
#include <MethodLibrary.h>
#include <iostream>
#include <string>
#include <Carnivore.h>
#include <raymath.h>
#include <ManagerClass.h>

int main()
{
    int windowWidth{960};
    int windowHeight{960};
    InitWindow(windowWidth, windowHeight, "Ecosystem");

    ManagerClass *managerClass = new ManagerClass();
    Vector2 mapPos{};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // begin drawing
        BeginDrawing();
        ClearBackground(WHITE);
        // draw map
        DrawTextureEx(managerClass->GetMap(), mapPos, 0, 1, WHITE);

        // print all creature
        managerClass->drawCreatureLists();

        managerClass->showKills();
        managerClass->showNumberOfCarnivores();
        managerClass->showNumberOfHerbivores();

        managerClass->showTimer(GetFrameTime());

        for (auto herbivore : managerClass->GetHerbivoreList())
        {
            herbivore->setIsBeingTargeted(false);
        }

        managerClass->addDuplicatedHerbivores();
        managerClass->addDuplicatedCarnivores();
        // end darwing
        EndDrawing();
    }
    UnloadTexture(managerClass->GetMap());
    UnloadTexture(managerClass->GetCarnivoreTextureEat());
    UnloadTexture(managerClass->GetCarnivoreTextureIdle());
    UnloadTexture(managerClass->GetCarnivoreTextureRun());
    UnloadTexture(managerClass->GetHerbivoreTextureEat());
    UnloadTexture(managerClass->GetHerbivoreTextureRun());
    UnloadTexture(managerClass->GetHerbivoreTexureIdle());

    delete managerClass;

    CloseWindow();
}