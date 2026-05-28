#include <raylib.h>
#include <iostream>
#include <deque>
#include <raymath.h>

using namespace std;

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;

double lastUpdatedTime = 0;

bool eventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdatedTime >= interval)
    {
        lastUpdatedTime = currentTime;
        return true;
    }
    return false;
}

class Snake
{
public:
    deque<Vector2> body{Vector2{5, 6}, Vector2{6, 6}, Vector2{7, 6}};
    Texture2D headtexture;
    Texture2D bodytexture;

    Vector2 direction = {1, 0};

    Snake()
    {
        Image snakeHead = LoadImage("res/graphics/snake.png");
        ImageResize(&snakeHead, cellSize, cellSize);
        ImageRotate(&snakeHead, 270); // 270 - right , 0 - down , 90 - left , 180 - top
        headtexture = LoadTextureFromImage(snakeHead);
        UnloadImage(snakeHead);

        Image bodyImage = LoadImage("res/graphics/body.png");
        ImageResize(&bodyImage, cellSize, cellSize);
        Image mask = GenImageColor(cellSize, cellSize, BLANK);
        ImageDrawCircle(&mask, cellSize / 2, cellSize / 2, cellSize / 1.7, WHITE);
        ImageAlphaMask(&bodyImage, mask);
        bodytexture = LoadTextureFromImage(bodyImage);

        UnloadImage(bodyImage);
        UnloadImage(mask);
    }

    ~Snake()
    {
        UnloadTexture(headtexture);
        UnloadTexture(bodytexture);
    }

    void draw()
    {
        for (unsigned i = 0; i < body.size(); i++)
        {
            float x = body[i].x;
            float y = body[i].y;
            if (i == body.size() - 1)
            {
                DrawTexture(headtexture, x * cellSize, y * cellSize, WHITE);
            }
            else
            {
                DrawTexture(bodytexture, x * cellSize, y * cellSize, WHITE);
            }
        }
    }

    void update()
    {
        body.pop_front();
        body.push_back(Vector2Add(body[body.size() - 1], direction));
    }
};

class Food
{
public:
    Vector2 position;
    Texture2D texture;

    Food()
    {
        Image image = LoadImage("res/graphics/food.png");
        ImageResize(&image, cellSize, cellSize);
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
        DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE);
    }

    Vector2 genRandomPos()
    {
        float x = GetRandomValue(0, cellCount - 1);
        float y = GetRandomValue(0, cellCount - 1);
        return Vector2{x, y};
    }
};

int main()
{
    cout << "Starting the game..." << endl;

    InitWindow(cellSize * cellCount, cellSize * cellCount, "Retro Snake");
    SetTargetFPS(60);

    Food food = Food();
    Snake snake = Snake();

    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        if (eventTriggered(0.3))
        {
            snake.update();
        }

        if(IsKeyPressed(KEY_UP) && snake.direction.y !=1)
        {
            snake.direction = {0,-1};
        }
        if(IsKeyPressed(KEY_DOWN) && snake.direction.y !=-1)
        {
            snake.direction = {0,1};
        }
        if(IsKeyPressed(KEY_LEFT) && snake.direction.x !=1)
        {
            snake.direction = {-1,0};
        }
        if(IsKeyPressed(KEY_RIGHT) && snake.direction.x !=-1)
        {
            snake.direction = {1,0};
        }

        ClearBackground(green);
        food.draw();
        snake.draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}