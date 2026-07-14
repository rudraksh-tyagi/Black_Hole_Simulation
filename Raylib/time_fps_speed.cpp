#include <raylib.h>

int main() {
    const int height = 600;
    const int width = 800;

    InitWindow(width, height, "Time Test Experiment");
    
    int currentFps = 60;
    
    // Fixed: Both now use 'height' for their vertical placement rows
    Vector2 delta_time = {0, (float)height / 3.0f};
    Vector2 frame_time = {0, (float)height * 2.0f / 3.0f};

    // Adjusted speeds so they match closely at 60 FPS for comparison
    const float speed = 200.0f; 
    const float radius = 30.0f;

    SetTargetFPS(currentFps);

    // --- THE GAME LOOP ---
    while (!WindowShouldClose()) {
        
        // 1. INPUT HANDLING (Moved inside the loop)
        float mouseWheel = GetMouseWheelMove();
        if (mouseWheel != 0) {
            currentFps += (int)mouseWheel * 5; // Multiplied by 5 so scrolling is faster
            if (currentFps < 0) currentFps = 0;
            SetTargetFPS(currentFps);
        }

        if (IsKeyPressed(KEY_R)) {
            delta_time.x = 0;
            frame_time.x = 0;
        }

        // 2. PHYSICS & MOVEMENT LOGIC (Moved inside the loop)
        // Delta Time uses a real pixel-per-second speed
        delta_time.x += speed * GetFrameTime();
        
        // Frame Time moves a fixed amount of pixels per frame (Frame-rate dependent)
        frame_time.x += 3.33f; 

        // Boundary Resetting
        if (delta_time.x > width) delta_time.x = 0;
        if (frame_time.x > width) frame_time.x = 0;

        // 3. RENDERING FRAME
        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            // Rendering the objects
            DrawCircleV(delta_time, radius, BLUE);
            DrawCircleV(frame_time, radius, RED);
            
            // Diagnostic Text
            const char *fpsText = 0;
            if (currentFps <= 0) fpsText = TextFormat("FPS: unlimited (%i)", GetFPS());
            else fpsText = TextFormat("FPS: %i (target: %i)", GetFPS(), currentFps);
            
            DrawText(fpsText, 10, 10, 20, DARKGRAY);
            // Multiplied by 1000 to show milliseconds clearly
            DrawText(TextFormat("Frame time: %02.02f ms", GetFrameTime() * 1000.0f), 10, 30, 20, DARKGRAY);
            DrawText("Use scroll wheel to change FPS, 'R' to reset cores", 10, 50, 20, DARKGRAY);

            // Fixed Text Labels & Colors to match the circles accurately
            DrawText("BLUE (Delta Time): x += speed * GetFrameTime()", 10, (int)delta_time.y - 50, 20, BLUE);
            DrawText("RED (Frame Time): x += fixed_pixels", 10, (int)frame_time.y - 50, 20, RED);
            
        EndDrawing();
    }

    CloseWindow();
    return 0;
}