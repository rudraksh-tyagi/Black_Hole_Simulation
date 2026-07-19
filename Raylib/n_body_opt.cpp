#include <raylib.h>
#include <vector>
#include <cmath>

using namespace std;

class planet
{
public:
    float mass;
    float radius;
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    Color color;

    planet(float m, float r, Vector2 pos, Vector2 vel, Vector2 acc, Color c)
        : mass(m), radius(r), position(pos), velocity(vel), acceleration(acc), color(c)
    {
    }
};

float RandomFloat(float min, float max)
{
    return min + ((float)GetRandomValue(0, 10000) / 10000.0f) * (max - min);
}

void make_planet(int n, vector<planet> &planets)
{
    planets.reserve(n);

    for (int i = 0; i < n; i++)
    {
        planets.emplace_back(
            RandomFloat(5.0f, 50.0f),
            RandomFloat(1.0f, 3.0f),
            Vector2{RandomFloat(0, 1920), RandomFloat(0, 1080)},
            Vector2{RandomFloat(-10, 10), RandomFloat(-10, 10)},
            Vector2{0, 0},
            WHITE);
    }
}

void Calculate_gravity(vector<planet> &planets)
{
    constexpr float G = 100.0f;
    constexpr float softening = 0.1f;

    size_t n = planets.size();

    for (size_t i = 0; i < n; i++)
        planets[i].acceleration = {0, 0};

    for (size_t i = 0; i < n; i++)
    {
        planet &a = planets[i];

        for (size_t j = i + 1; j < n; j++)
        {
            planet &b = planets[j];

            float dx = b.position.x - a.position.x;
            float dy = b.position.y - a.position.y;

            float r2 = dx * dx + dy * dy + softening;

            float invR = 1.0f / sqrtf(r2);
            float invR3 = invR * invR * invR;

            float ax = G * b.mass * dx * invR3;
            float ay = G * b.mass * dy * invR3;

            float bx = G * a.mass * dx * invR3;
            float by = G * a.mass * dy * invR3;

            a.acceleration.x += ax;
            a.acceleration.y += ay;

            b.acceleration.x -= bx;
            b.acceleration.y -= by;
        }
    }
}

void update_position(vector<planet> &planets, float dt)
{
    for (planet &p : planets)
    {
        p.velocity.x += p.acceleration.x * dt;
        p.velocity.y += p.acceleration.y * dt;

        p.position.x += p.velocity.x * dt;
        p.position.y += p.velocity.y * dt;
    }
}

int main()
{
    vector<planet> planets;

    make_planet(1000, planets);
    planets.emplace_back(
    50000.0f,              // Mass
    50.0f,                 // Radius
    Vector2{160, 940},     // Center of screen
    Vector2{0, 0},         // Velocity
    Vector2{0, 0},         // Acceleration
    BLUE
    );
    planets.emplace_back(
    50000.0f,              // Mass
    50.0f,                 // Radius
    Vector2{160, 140},     // Center of screen
    Vector2{0, 0},         // Velocity
    Vector2{0, 0},         // Acceleration
    BLUE
);


    InitWindow(1920, 1080, "Optimized N-Body");

    SetTargetFPS(0);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        Calculate_gravity(planets);

        update_position(planets, dt);

        BeginDrawing();

        ClearBackground(BLACK);

        for (const planet &p : planets)
            DrawCircleV(p.position, p.radius, p.color);

        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
}