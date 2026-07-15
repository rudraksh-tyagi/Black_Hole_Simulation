#include <raylib.h>
#include <iostream>
#include <cmath>

using namespace std;

int main() {
    const int height = 800;
    const int width = 800;

    // Vectors to hold the final calculated pixel positions for rendering
    Vector2 ball_screen_pos = {0.0f, 0.0f};
    Vector2 ball2_screen_pos = {0.0f, 0.0f};
    
    InitWindow(width, height, "Earth Surface Gravity Test - Fixed Independent Balls");
    SetTargetFPS(60); 

    // Earth's standard surface conditions
    const float acc = 9.81f;        // 9.81 m/s^2 acceleration due to gravity
    const float radi = 20.0f;       // Physical radius of the balls
    const float METERS_PER_PIXEL = 0.009f; // Scale translation: 1 pixel = 9mm
    const float e = 0.80f;          // Coefficient of restitution (bounciness factor)
    
    // Ball 1 Setup (Red)
    float ball_pos_meters_y = 7.0f;
    float ball_pos_meters_x = 6.0f;
    float velocity_y = 0.0f;
    float velocity_x = (float)GetRandomValue(-50, 50) / 10.0f;

    // Ball 2 Setup (Blue)
    float ball2_pos_meters_y = 7.0f;
    float ball2_pos_meters_x = 2.0f;
    float velocity2_y = 0.0f;
    float velocity2_x = (float)GetRandomValue(-50, 50) / 10.0f;

    // Boundary constraints in simulation meters
    float max_width_meters = width * METERS_PER_PIXEL;
    float boundary_padding = radi * METERS_PER_PIXEL;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        // 1. Independent Real-Time Physics Movement Step
        if (dt > 0.0f && dt < 0.1f) 
        {
            // Ball 1 Physics Step
            velocity_y += acc * dt;
            ball_pos_meters_y -= velocity_y * dt; 
            ball_pos_meters_x -= velocity_x * dt;

            // Ball 2 Physics Step (Now using velocity2 variables correctly!)
            velocity2_y += acc * dt;
            ball2_pos_meters_y -= velocity2_y * dt; 
            ball2_pos_meters_x -= velocity2_x * dt;
        }

        // ================= BALL 1 COLLISIONS =================
        if (ball_pos_meters_y > (height * METERS_PER_PIXEL) - boundary_padding) {
            ball_pos_meters_y = (height * METERS_PER_PIXEL) - boundary_padding;
            velocity_y = -velocity_y * e;
        }
        if (ball_pos_meters_y < boundary_padding) {
            ball_pos_meters_y = boundary_padding; // Snap to ground plane
            velocity_y = -velocity_y * e;          // Bounce upward
        }
        if (ball_pos_meters_x < boundary_padding) {
            ball_pos_meters_x = boundary_padding; // Left wall anti-penetration
            velocity_x = -velocity_x * e;          // Bounce rightward
        }
        if (ball_pos_meters_x > max_width_meters - boundary_padding) {
            ball_pos_meters_x = max_width_meters - boundary_padding; // Right wall anti-penetration
            velocity_x = -velocity_x * e;          // Bounce leftward
        }

        // ================= BALL 2 COLLISIONS =================
        if (ball2_pos_meters_y > (height * METERS_PER_PIXEL) - boundary_padding) {
            ball2_pos_meters_y = (height * METERS_PER_PIXEL) - boundary_padding;
            velocity2_y = -velocity2_y * e;
        }
        if (ball2_pos_meters_y < boundary_padding) {
            ball2_pos_meters_y = boundary_padding; // Snap to ground plane
            velocity2_y = -velocity2_y * e;        // Bounce upward
        }
        if (ball2_pos_meters_x < boundary_padding) {
            ball2_pos_meters_x = boundary_padding; // Left wall anti-penetration
            velocity2_x = -velocity2_x * e;        // Bounce rightward
        }
        if (ball2_pos_meters_x > max_width_meters - boundary_padding) {
            ball2_pos_meters_x = max_width_meters - boundary_padding; // Right wall anti-penetration
            velocity2_x = -velocity2_x * e;        // Bounce leftward
        }

        // Map simulation coordinates back to pixel coordinates dynamically inside the loop
        ball_screen_pos.x = ball_pos_meters_x / METERS_PER_PIXEL;
        ball_screen_pos.y = (float)height - (ball_pos_meters_y / METERS_PER_PIXEL);

        ball2_screen_pos.x = ball2_pos_meters_x / METERS_PER_PIXEL;
        ball2_screen_pos.y = (float)height - (ball2_pos_meters_y / METERS_PER_PIXEL);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // Draw the baseline reference (Ground plane at y = 0 meters)
        DrawLine(0, height - 1, width, height - 1, BLUE);
        
        // On-Screen telemetry debug display
        DrawText(TextFormat("Ball 1 (Red)  Y Vel: %.2f m/s" , -velocity_y) , 10 , 10 , 20 , RED);
        DrawText(TextFormat("Ball 2 (Blue) Y Vel: %.2f m/s" , -velocity2_y) , 10 , 35 , 20 , BLUE);
        DrawText(TextFormat("Frametime: %.4f s" , dt) , 10, 60 , 20 , BLACK);
        
        // Draw both objects on screen
        DrawCircleV(ball_screen_pos, radi, RED);
        DrawCircleV(ball2_screen_pos, radi, BLUE);
        
        EndDrawing();
    }
    CloseWindow();
    return 0;
}