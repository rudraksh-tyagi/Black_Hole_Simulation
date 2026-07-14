#include<raylib.h>
using namespace std;
int main(){
    const int height = 600;
    const int width = 800;

    InitWindow(width , height, "window");

    while(!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("welcome to the window" ,190 , 200 , 20 , BLACK);
            
            EndDrawing();
        }
        
    return 0;

}