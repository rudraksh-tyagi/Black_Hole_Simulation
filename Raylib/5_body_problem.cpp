#include<raylib.h>
#include<cmath>
#include<vector>
#include<iostream>
using namespace std;
class planet{
    public:
    float mass;
    float radius;

    Vector2 position;
    Vector2 velocity;
    
    Vector2 acceleration;

    Color color;
    
    vector<Vector2> trail; 
    planet(float m , float r , Vector2 pos ,Vector2 vel , Vector2 acc  ,Color c)
    :
    mass(m),
    radius(r),
    position(pos),
    velocity(vel),
        acceleration(acc),
        color(c) {}
        
    };
    
    void Calculate_gravity(planet &a, planet &b)
{
    float m1 = a.mass;
    float m2 = b.mass;
    
    float x1 = b.position.x - a.position.x;
    float y1 = b.position.y - a.position.y;

    float r = sqrt(x1*x1 + y1*y1);
    if(r == 0)
    return;
    const double G = 100.0;
    
    float g_force = G * m1 * m2 / (r * r);

    float unitX = x1 / r;
    float unitY = y1 / r;

    float g_forceX = unitX * g_force;
    float g_forceY = unitY * g_force;
    
    // Acceleration of planet A
    a.acceleration.x += g_forceX / m1;
    a.acceleration.y += g_forceY / m1;
    // Acceleration o+ planet B
    b.acceleration.x += -g_forceX / m2;
    b.acceleration.y += -g_forceY / m2;
}

void DrawTrail(planet &a)

{   
    if(a.trail.size() < 2){
        return;
    }
    for(int i = 0; i < a.trail.size() - 1; i++)
    {
        DrawLineV(a.trail[i], a.trail[i + 1], WHITE);
    }
    if(a.trail.size() > 15000)
    a.trail.erase(a.trail.begin());
}

void update_position(planet &a , float &x){
    a.velocity.x += a.acceleration.x * x;
    a.velocity.y += a.acceleration.y * x;
    a.position.x += a.velocity.x * x;
    a.position.y += a.velocity.y * x;
}

int main(){
    float const width = 1920;
    float const height = 1080;
    
    InitWindow(width , height , "5 body simulation");
    vector<Vector2> grah;
    planet sun  (100000.0, 40.0, {960,540}, {0,0}, {0,0}, YELLOW);
    planet exo  (1.0, 10.0, {960,390}, {236,0},  {0,0}, BLUE);
    planet neo  (1.0, 10.0, {700,540}, {0,-196}, {0,0}, RED);
    planet erid (1.0, 10.0, {1360,540},{0,158},  {0,0}, ORANGE);
    planet ren  (1.0, 10.0, {960,1040},{141,0},  {0,0}, GREEN);
    int frameCounter = 0;
    // for(int )
while(!WindowShouldClose()){
        frameCounter++;
        
    float dt= GetFrameTime();
    sun.acceleration = {0,0};
    exo.acceleration = {0,0};
        neo.acceleration = {0,0};
        ren.acceleration = {0,0};
        erid.acceleration = {0,0};

       // Sun interactions
        Calculate_gravity(sun, exo);
        Calculate_gravity(sun, neo);
        Calculate_gravity(sun, ren);
        Calculate_gravity(sun, erid);
        
        // Exo interactions
        Calculate_gravity(exo, neo);
        Calculate_gravity(exo, ren);
        Calculate_gravity(exo, erid);
        
        // Neo interactions
        Calculate_gravity(neo, ren);
        Calculate_gravity(neo, erid);
        
        // Ren interactions
        Calculate_gravity(ren, erid);
        
        if (dt > 0.0f && dt < 0.1f) {
         update_position(exo,dt);
         update_position(erid,dt);
         update_position(neo,dt);
         update_position(ren,dt);
        
        // exo.trail.push_back(exo.position);
        // neo.trail.push_back(neo.position);
        // ren.trail.push_back(ren.position);
        // erid.trail.push_back(erid.position);


         
    }  
    BeginDrawing();
    ClearBackground(BLACK);
        // DrawTrail(exo);
        // DrawTrail(ren);
        // DrawTrail(neo);
        // DrawTrail(erid);
        DrawCircleV(exo.position , exo.radius , exo.color);
        DrawCircleV(neo.position , neo.radius , neo.color);
        DrawCircleV(ren.position , ren.radius , ren.color);
        DrawCircleV(erid.position , erid.radius , erid.color);
        DrawCircleV(sun.position , sun.radius , sun.color);
        DrawFPS(10,10);

        EndDrawing();
    }
    return 0;
}