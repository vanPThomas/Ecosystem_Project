#include <raylib.h>
#include <Herbivore.h>
#include <Carnivore.h>
#include <list>

class ManagerClass
{
public:
    ManagerClass();
    std::list<Herbivore *> GetHerbivoreList() { return herbivores; }
    std::list<Carnivore *> GetCarnivoreList() { return carnivores; }
    Texture2D GetHerbivoreTexureIdle() { return herbivoreTexureIdle; }
    Texture2D GetHerbivoreTextureRun() { return herbivoreTextureRun; }
    Texture2D GetHerbivoreTextureEat() { return herbivoreTextureEat; }
    Texture2D GetCarnivoreTextureIdle() { return carnivoreTextureIdle; }
    Texture2D GetCarnivoreTextureRun() { return carnivoreTextureRun; }
    Texture2D GetCarnivoreTextureEat() { return carnivoreTextureEat; }
    void addDuplicatedHerbivores();
    void addDuplicatedCarnivores();

    Texture2D GetMap() { return map; }
    void drawCreatureLists()
    {
        drawCreatureLists(carnivores, herbivores);
        drawCreatureLists(herbivores);
    }

    void addHerbivore(Vector2 spawnLocation);
    void addCarnivore(Vector2 spawnLocation);
    void showKills();
    void showNumberOfCarnivores();
    void showNumberOfHerbivores();
    void showTimer(float deltaTime);

private:
    std::list<Herbivore *> herbivores{};
    std::list<Carnivore *> carnivores{};
    Texture2D map;
    Texture2D herbivoreTexureIdle;
    Texture2D herbivoreTextureRun;
    Texture2D herbivoreTextureEat;
    Texture2D carnivoreTextureIdle;
    Texture2D carnivoreTextureRun;
    Texture2D carnivoreTextureEat;
    const int maxFramesHerbivoreIdle = 5;
    const int maxFramesHerbivoreRun = 2;
    const int maxFramesHerbivoreEat = 4;
    const int maxFramesCarnivoreIdle = 3;
    const int maxFramesCarnivoreRun = 4;
    const int maxFramesCarnivoreEat = 2;
    int killCount{0};
    float timer{0};
    void drawCreatureLists(std::list<Carnivore *> &carnivores, std::list<Herbivore *> &herbivores);

    void drawCreatureLists(std::list<Herbivore *> &herbivores);
};
