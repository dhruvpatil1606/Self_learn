#include <raylib.h>
#include <iostream>

using namespace std;

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;

class Food
{
    public:
        Vector2 position;
        Texture2D texture;

    Food()
    {
        Image image = LoadImage("res/graphics/food.png");
        ImageResize(&image,cellSize,cellSize);
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = genRandomPos();
    }

    ~Food()
    {
        UnloadTexture(texture);
    }
    
    void draw()
    {
        DrawTexture(texture,position.x*cellSize,position.y*cellSize, WHITE);
    }

    Vector2 genRandomPos()
    {
        float x = GetRandomValue(0, cellCount-1);
        float y = GetRandomValue(0, cellCount-1);
        return Vector2{x,y};
    }

};

int main()
{
    cout << "Starting the game..." << endl;

    InitWindow(cellSize * cellCount, cellSize * cellCount, "Retro Snake");
    SetTargetFPS(60);

    Food food = Food();

    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        ClearBackground(green);
        food.draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}