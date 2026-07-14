#include<raylib.h>
using namespace std;
int main(){
    const int height = 600;
    const int width = 800;

    InitWindow(width , height ,"movement_test");

    SetTargetFPS(60);
    Vector2 ball_pos = {(float) width/2.0f , (float)height/2.0f};
    

    while(!WindowShouldClose()){
        if(IsKeyDown(KEY_UP)) ball_pos.y -= 4.0f;
        if(IsKeyDown(KEY_RIGHT)) ball_pos.x += 4.0f;
        if(IsKeyDown(KEY_LEFT))ball_pos.x -= 4.0f;
        if(IsKeyDown(KEY_DOWN)) ball_pos.y += 4.0f;
    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircleV(ball_pos , 50.0f , BLUE);
        EndDrawing();
    }
    CloseWindow();

    return 0;


}