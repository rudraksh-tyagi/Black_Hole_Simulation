#include<raylib.h>
#include<iostream>
#include<cmath>
using namespace std;

int main(){
    const int height = 800;
    const int width = 800;

    // The screen position of our ball
    Vector2 ball_screen_pos = {(float)width / 2.0f, 0.0f};
    
    InitWindow(width, height, "Earth Surface Gravity Test");
    SetTargetFPS(60); 

    // Earth's standard surface conditions
    const float acc = 9.81f; // 9.81 m/s^2
    const float radi = 20.0f; // A nice visible size on screen
    
    
   // NEW SCALE: 1 Pixel = 0.009 Meters (100 Pixels = 0.9m)
        const float METERS_PER_PIXEL = 0.009f; 

        // Start the ball 7 meters up so it fits nicely at the top of the screen
        float ball_pos_meters_y = 7.0f;
        float ball_pos_meters_x = 4.0f ;
        const float e = .80f;
        float velocity_y = 0.0f;
        float velocity_x = (float)GetRandomValue(-50,50)/10.0f;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        // Standard real-time physics update
        if (dt > 0.0f && dt < 0.1f) 
        {
            velocity_y += acc * dt;
            ball_pos_meters_y -= velocity_y * dt; // Dropping down toward 0
            ball_pos_meters_x-= velocity_x*dt;
        }

        if (ball_pos_meters_y > (height * METERS_PER_PIXEL) - (radi * METERS_PER_PIXEL)) {
            ball_pos_meters_y = (height * METERS_PER_PIXEL) - (radi * METERS_PER_PIXEL);
            velocity_y = -velocity_y * e;
        }
        if (ball_pos_meters_y < (radi * METERS_PER_PIXEL)) {
            ball_pos_meters_y = (radi * METERS_PER_PIXEL); // Snap to floor
            velocity_y = -velocity_y * e;                 // Bounce back UP
        }
        // --- 3. LEFT WALL COLLISION ---
        if (ball_pos_meters_x < (radi * METERS_PER_PIXEL)){
            ball_pos_meters_x = (radi * METERS_PER_PIXEL); // Anti-penetration
            velocity_x = -velocity_x * e;          // Flip horizontal direction
        }

        // --- 4. RIGHT WALL COLLISION ---
        float max_width_meters = width * METERS_PER_PIXEL;
        if (ball_pos_meters_x > max_width_meters - (radi * METERS_PER_PIXEL)) {
            ball_pos_meters_x = max_width_meters - (radi * METERS_PER_PIXEL); 
            velocity_x = -velocity_x * e; // Reverse horizontal direction
        }
        float display_velocity = -velocity_y;
        // Map meters directly to screen pixels
        // When ball_pos_meters_y is 700, screen Y is 100 (near top)
        // When ball_pos_meters_y is 0, screen Y is 800 (bottom ground)
        ball_screen_pos.x = ball_pos_meters_x / METERS_PER_PIXEL; // Dynamically track X
        ball_screen_pos.y = (float)height - (ball_pos_meters_y / METERS_PER_PIXEL);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // Draw the ground line at the very bottom of the screen (0 meters altitude)
        DrawLine(0, height - 1, width, height - 1, BLUE);
        DrawText(TextFormat("Velocity: %.2f m/s" , display_velocity) , 10 , 10 , 20 , BLACK);
        DrawText(TextFormat("frametime: %.2f s" , dt) , 10, 30 , 20 , BLACK);
        // Draw the ball falling under Earth conditions
        DrawCircleV(ball_screen_pos, radi, RED);
        
        
        EndDrawing();
    }
    CloseWindow();
    return 0;
}