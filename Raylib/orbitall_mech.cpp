#include<raylib.h>
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
    const double G = 100000.0;

    float g_force = G * m1 * m2 / (r * r);

    float unitX = x1 / r;
    float unitY = y1 / r;

    float g_forceX = unitX * g_force;
    float g_forceY = unitY * g_force;

    // Acceleration of planet A
    a.acceleration.x = g_forceX / m1;
    a.acceleration.y = g_forceY / m1;

    // Acceleration of planet B
    b.acceleration.x = -g_forceX / m2;
    b.acceleration.y = -g_forceY / m2;
}



int main(){
 const float height = 1080;
 const float width = 1920;
 InitWindow(width , height , "orbital_mechanics");

 planet exo(1000.0, 15.0 , {600, 450} , {-150,150} ,{0,0}, BLUE);
 planet neo(1000.0, 15.0 , {1200, 450} , {150,-150} ,{0,0}, BLUE);
//  planet zeta(1000.0 ,15.0 , {})
 
 
 while(!WindowShouldClose()){
     float dt = GetFrameTime();
     ClearBackground(BLACK);
     Calculate_gravity(exo , neo);
     if (dt > 0.0f && dt < 0.1f) {
         exo.velocity.x += exo.acceleration.x * dt;
         exo.velocity.y += exo.acceleration.y * dt;
         exo.position.x += exo.velocity.x *dt;
         exo.position.y += exo.velocity.y *dt;
         //  -------------------------------------------
         neo.velocity.x += neo.acceleration.x * dt;
         neo.velocity.y += neo.acceleration.y * dt;
         neo.position.x += neo.velocity.x * dt;
         neo.position.y += neo.velocity.y * dt;
}
    BeginDrawing();
    DrawCircleV(exo.position , exo.radius , exo.color);
    DrawCircleV(neo.position, neo.radius , neo.color);
    EndDrawing();

}
return 0;
}