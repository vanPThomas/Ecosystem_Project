#include <ManagerClass.h>
#include <raylib.h>
#include <Herbivore.h>
#include <Carnivore.h>
#include <list>
#include <MethodLibrary.h>
#include <string>

ManagerClass::ManagerClass()
{
    // loading textures and number of frames
    map = LoadTexture("map/map.png");
    herbivoreTexureIdle = LoadTexture("creatures/Creature1_idle_Sheet.png");
    herbivoreTextureRun = LoadTexture("creatures/Creature1_moving_Sheet.png");
    herbivoreTextureEat = LoadTexture("creatures/Creature1_eating_Sheet.png");
    carnivoreTextureIdle = LoadTexture("creatures/Carnivore_idle_Sheet.png");
    carnivoreTextureRun = LoadTexture("creatures/Carnivore_moving_Sheet.png");
    carnivoreTextureEat = LoadTexture("creatures/Carnivore_eating_Sheet.png");

    // filling creature lists
    int numberOfHerbivores = 30;
    int numberOfCarnivores = 10;
    for (int i = 0; i < numberOfHerbivores; i++)
    {
        Herbivore herbivore{getRandomMapVector(), herbivoreTexureIdle, herbivoreTextureRun, herbivoreTextureEat, maxFramesHerbivoreIdle, maxFramesHerbivoreRun, maxFramesHerbivoreEat};
        Herbivore *herbivorePTR = new Herbivore(herbivore);
        herbivores.push_back(herbivorePTR);
    }
    for (int i = 0; i < numberOfCarnivores; i++)
    {
        Carnivore carnivore{getRandomMapVector(), carnivoreTextureIdle, carnivoreTextureRun, carnivoreTextureEat, maxFramesCarnivoreIdle, maxFramesCarnivoreRun, maxFramesCarnivoreEat};
        Carnivore *carnivorePTR = new Carnivore(carnivore);
        carnivores.push_back(carnivorePTR);
    }
}

void ManagerClass::drawCreatureLists(std::list<Carnivore *> &carnivores, std::list<Herbivore *> &herbivores)
{
    std::list<Carnivore *> carnivoresBackup{};

    int carnivoresListSize = carnivores.size();
    if (carnivoresListSize > 0)
        for (auto carnivore : carnivores)
            carnivore->tick(GetFrameTime(), herbivores);

    for (auto &&carnivore : carnivores)
        if (!carnivore->getAlive())
            delete carnivore;
        else
            carnivoresBackup.push_back(carnivore);

    carnivores.clear();
    for (auto &&carnivore : carnivoresBackup)
        carnivores.push_back(carnivore);
    carnivoresBackup.clear();
}
void ManagerClass::drawCreatureLists(std::list<Herbivore *> &herbivores)
{
    std::list<Herbivore *> herbivoresBackup{};
    int HerbivoresListSize = herbivores.size();
    if (HerbivoresListSize > 0)
        for (auto herbivore : herbivores)
            herbivore->tick(GetFrameTime());

    for (auto &&herbivore : herbivores)
        if (!herbivore->getAlive())
        {
            delete herbivore;
            killCount++;
        }
        else
            herbivoresBackup.push_back(herbivore);

    herbivores.clear();
    for (auto &&herbivore : herbivoresBackup)
        herbivores.push_back(herbivore);
    herbivoresBackup.clear();
}

void ManagerClass::addDuplicatedHerbivores()
{
    for (auto herbivore : herbivores)
    {
        if (herbivore->getDuplicationValue() <= 0.f)
        {
            herbivore->resetDuplicationValue();
            herbivore->setIsEating(false);

            std::random_device rd;                          // obtain a random number from hardware
            std::mt19937 gen(rd());                         // seed the generator
            std::uniform_int_distribution<> distr(-80, 80); // define the range
            Vector2 newLocation = {herbivore->getScreenPos().x + distr(gen), herbivore->getScreenPos().y + distr(gen)};

            if (newLocation.x < 75.f)
                newLocation.x = 75.f;
            if (newLocation.x > 855.f)
                newLocation.x = 855.f;
            if (newLocation.y < 75.f)
                newLocation.y = 75.f;
            if (newLocation.y > 800.f)
                newLocation.y = 800.f;

            addHerbivore(newLocation);
        }
    }
}
void ManagerClass::addDuplicatedCarnivores()
{
    for (auto carnivore : carnivores)
    {
        if (carnivore->getDuplicationValue() <= 0.f)
        {
            carnivore->resetDuplicationValue();

            std::random_device rd;                          // obtain a random number from hardware
            std::mt19937 gen(rd());                         // seed the generator
            std::uniform_int_distribution<> distr(-80, 80); // define the range
            Vector2 newLocation = {carnivore->getScreenPos().x + distr(gen), carnivore->getScreenPos().y + distr(gen)};

            if (newLocation.x < 75.f)
                newLocation.x = 75.f;
            if (newLocation.x > 855.f)
                newLocation.x = 855.f;
            if (newLocation.y < 75.f)
                newLocation.y = 75.f;
            if (newLocation.y > 800.f)
                newLocation.y = 800.f;

            addCarnivore(newLocation);
        }
    }
}

void ManagerClass::addCarnivore(Vector2 spawnLocation)
{
    Carnivore carnivore{spawnLocation, carnivoreTextureIdle, carnivoreTextureRun, carnivoreTextureEat, maxFramesCarnivoreIdle, maxFramesCarnivoreRun, maxFramesCarnivoreEat};
    Carnivore *carnivorePTR = new Carnivore(carnivore);
    carnivores.push_back(carnivorePTR);
}
void ManagerClass::addHerbivore(Vector2 spawnLocation)
{
    Herbivore herbivore{spawnLocation, herbivoreTexureIdle, herbivoreTextureRun, herbivoreTextureEat, maxFramesHerbivoreIdle, maxFramesHerbivoreRun, maxFramesHerbivoreEat};
    Herbivore *herbivorePTR = new Herbivore(herbivore);
    herbivores.push_back(herbivorePTR);
}

void ManagerClass::showKills()
{
    std::string killInfo{"Deaths: "};
    killInfo.append(std::to_string(killCount));
    DrawText(killInfo.c_str(), 25.f, 25.f, 40, BLACK);
}
void ManagerClass::showNumberOfCarnivores()
{
    int carnCount{carnivores.size()};
    std::string numberOfCarnivores{"Carnivores: "};
    numberOfCarnivores.append(std::to_string(carnCount));
    DrawText(numberOfCarnivores.c_str(), 295.f, 25.f, 40, RED);
}
void ManagerClass::showNumberOfHerbivores()
{
    int herbCount{herbivores.size()};
    std::string numberOfHerbivores{"Herbivores: "};
    numberOfHerbivores.append(std::to_string(herbCount));
    DrawText(numberOfHerbivores.c_str(), 635.f, 25.f, 40, BLUE);
}

void ManagerClass::showTimer(float deltaTime)
{
    std::string timePassed{};
    if (herbivores.size() > 0)
    {
        timer += deltaTime;
        timePassed.append("Time Passed: ");
    }
    else
    {
        timePassed.append("Simulation over: ");
    }

    int timerInt = static_cast<int>(timer);
    timePassed.append(std::to_string(timerInt));
    DrawText(timePassed.c_str(), 25.f, 900.f, 40, BLACK);
}