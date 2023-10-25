#include <raylib.h>
#include <random>
#include <cmath>

static Vector2 getRandomMapVector()
{
    std::random_device rd;                          // obtain a random number from hardware
    std::mt19937 gen(rd());                         // seed the generator
    std::uniform_int_distribution<> distr(64, 800); // define the range
    int x{distr(gen)};
    int y{distr(gen)};
    Vector2 pos{static_cast<float>(x), static_cast<float>(y)};

    return pos;
}

static float getDistanceBetweenVectors(Vector2 a, Vector2 b)
{
    float powX = pow((a.x - b.x), 2);
    float powY = pow((a.y - b.y), 2);

    float distance = sqrt(powX+powY);

    return distance;

}