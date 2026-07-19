#include<raylib.h>
#include<vector>
#include<vector>
#include<cmath>
using namespace std;

class planet{
    public:
    float mass;
    float radius;
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    Color color;
    planet(float m ,float r , Vector2 pos ,Vector2 vel, Vector2 acc , Color c)
    :
    mass(m),
    radius(r),
    position(pos),
    velocity(vel),
    acceleration(acc),
    color(c){}
};

            void Calculate_gravity(vector<planet> &a){
            for(int i = 0 ; i < a.size() ;i++){
            a[i].acceleration = {0,0};
            for(int z = 0 ; z<a.size() ; z++){
            if(i == z){
                continue;
            }
            float m1 = a[i].mass;
            float m2 = a[z].mass;
            
            float x1 = a[z].position.x - a[i].position.x;
            float y1 = a[z].position.y - a[i].position.y;
            
            float r = sqrt(x1*x1 + y1*y1);
            if(r == 0)
            continue;
            const float G = 100.0;
            
            float g_force = G * m1 * m2 / (r * r);

            float unitX = x1 / r;
            float unitY = y1 / r;

            float g_forceX = unitX * g_force;
            float g_forceY = unitY * g_force;
    
        // Acceleration of planet A
             a[i].acceleration.x += g_forceX / m1;
             a[i].acceleration.y += g_forceY / m1;
             // Acceleration o+ planet B
    }
}
}


void update_position(vector<planet>&a, float x){
    for(int i = 0 ; i < a.size() ; i++){
    a[i].velocity.x += a[i].acceleration.x * x;
    a[i].velocity.y += a[i].acceleration.y * x;
    a[i].position.x += a[i].velocity.x * x;
    a[i].position.y += a[i].velocity.y * x;
        }
    }

    float RandomFloat(float min, float max)
    {
        return min + ((float)GetRandomValue(0, 10000) / 10000.0f) * (max - min);
    }

void make_planet(int n, vector<planet> &a){
    for(int i = 0 ; i < n ; i++){
        float mass = RandomFloat(5.0f , 50.0f);
        float radius = RandomFloat(1.0f , 3.0f);
        Vector2 position = { RandomFloat(0.0f, 1920.0f),RandomFloat(0.0f, 1080.0f)};
        Vector2 acc = {0,0};
        Vector2 velocity =   {RandomFloat(-10.0f,50.0f),RandomFloat(-10.0f,50.0f)};
        Color c = WHITE;
        planet p(mass , radius , position, velocity ,acc, c );
        a.push_back(p);
        a.reserve(n);
    }
}

int main(){

    vector<planet> planets;
    make_planet(2500 , planets);
    float const width = 1920;
    float const height = 1080;
    InitWindow(width,  height, "nbody");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        Calculate_gravity(planets);
        float dt = GetFrameTime();
        update_position(planets , dt);
       for(int  i =0 ; i < planets.size() ; i++){
        DrawCircleV(planets[i].position , planets[i].radius , WHITE);
       }
       DrawFPS(10,10);
        EndDrawing();
    }
    CloseWindow();
    return 0;

}