#include <raylib.h>
#include <iostream>
#include <deque>
#include <raymath.h>

using namespace std;

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;
int offset = 75;

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

bool ElementInDeque(Vector2 element, deque<Vector2> snakeBody)
{
    for (int i = 0; i < snakeBody.size(); i++)
    {
        if (Vector2Equals(snakeBody[i], element))
        {
            return true;
        }
    }
    return false;
}

class Snake
{
public:
    deque<Vector2> body{Vector2{5, 6}, Vector2{6, 6}, Vector2{7, 6}};
    Texture2D headtextureUp;
    Texture2D headtextureDown;
    Texture2D headtextureLeft;
    Texture2D headtextureRight;
    Texture2D bodytexture;

    Vector2 direction = {1, 0};

    bool directionChange = true;

    Snake()
    {
        Image snakeHead = LoadImage("res/graphics/snake.png");
        ImageResize(&snakeHead, cellSize, cellSize);

        headtextureDown = LoadTextureFromImage(snakeHead);

        ImageRotate(&snakeHead, 180);
        headtextureUp = LoadTextureFromImage(snakeHead);

        ImageRotate(&snakeHead, 90);
        headtextureRight = LoadTextureFromImage(snakeHead);

        ImageRotate(&snakeHead, 180);
        headtextureLeft = LoadTextureFromImage(snakeHead);

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
        UnloadTexture(headtextureUp);
        UnloadTexture(headtextureDown);
        UnloadTexture(headtextureLeft);
        UnloadTexture(headtextureRight);
        UnloadTexture(bodytexture);
    }

    void draw()
    {
        for (unsigned i = 0; i < body.size(); i++)
        {
            float x = body[i].x;
            float y = body[i].y;

            if (i == body.size() - 1) // head
            {
                if (direction.x == -1)
                    DrawTexture(headtextureLeft, offset + x * cellSize, offset + y * cellSize, WHITE);
                if (direction.x == 1)
                    DrawTexture(headtextureRight, offset + x * cellSize, offset + y * cellSize, WHITE);
                if (direction.y == -1)
                    DrawTexture(headtextureUp, offset + x * cellSize, offset + y * cellSize, WHITE);
                if (direction.y == 1)
                    DrawTexture(headtextureDown, offset + x * cellSize, offset + y * cellSize, WHITE);
            }
            else // body
            {
                DrawTexture(bodytexture, offset + x * cellSize, offset + y * cellSize, WHITE);
            }
        }
    }

    void update()
    {
        body.pop_front();
        body.push_back(Vector2Add(body[body.size() - 1], direction));
        directionChange = true;
    }

    void GameReset()
    {
        body = {Vector2{5, 6}, Vector2{6, 6}, Vector2{7, 6}};
        direction = {1, 0};
    }
};

class Food
{
public:
    Vector2 position;
    Texture2D texture;

    Food(deque<Vector2> snakeBody)
    {
        Image image = LoadImage("res/graphics/food.png");
        ImageResize(&image, cellSize, cellSize);
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = genRandomPos(snakeBody);
    }

    ~Food()
    {
        UnloadTexture(texture);
    }

    void draw()
    {
        DrawTexture(texture, offset + position.x * cellSize, offset + position.y * cellSize, WHITE);
    }

    Vector2 genRandomCells()
    {
        float x = GetRandomValue(0, cellCount - 1);
        float y = GetRandomValue(0, cellCount - 1);
        return Vector2{x, y};
    }

    Vector2 genRandomPos(deque<Vector2> snakeBody)
    {
        Vector2 position = genRandomCells();

        while (ElementInDeque(position, snakeBody))
        {
            position = genRandomCells();
        }

        return position;
    }
};

class Game
{
public:
    Snake snake = Snake();
    Food food = Food(snake.body);

    bool running = true;

    int score = 0;

    Sound biteSound,wallHitSound;

    Game()
    {
        InitAudioDevice();
        biteSound = LoadSound("res/sounds/bite.mp3");
        wallHitSound = LoadSound("res/sounds/wall.mp3");
    }

    ~Game()
    {
        UnloadSound(biteSound);
        UnloadSound(wallHitSound);
        CloseAudioDevice();
    }

    void Draw()
    {
        snake.draw();
        food.draw();
    }

    void Update()
    {
        if (running == true)
        {
            snake.update();
            checkCollition();
            checkSnakeCollitionWithScreen();
            checkCollitionWithTail(snake.body);
        }
    }

    void checkCollition()
    {
        if (Vector2Equals(snake.body[snake.body.size() - 1], food.position))
        {
            PlaySound(biteSound);
            cout << "Eating food.." << endl;
            food.position = food.genRandomPos(snake.body);
            Vector2 bodyAdd = snake.body[0];
            snake.body.push_front(bodyAdd);
            score++;
        }
    }

    void checkCollitionWithTail(deque<Vector2> snakeBody)
    {
        for (int i = 0; i < snakeBody.size() - 1; i++)
        {
            if (Vector2Equals(snakeBody[i], snakeBody[snakeBody.size() - 1]))
            {
                GameOver();
            }
        }
    }

    void checkSnakeCollitionWithScreen()
    {
        if (snake.body[snake.body.size() - 1].x == cellCount || snake.body[snake.body.size() - 1].x == -1)
        {
            GameOver();
        }
        if (snake.body[snake.body.size() - 1].y == cellCount || snake.body[snake.body.size() - 1].y == -1)
        {
            GameOver();
        }
    }

    void GameOver()
    {
        PlaySound(wallHitSound);
        snake.GameReset();
        food.position = food.genRandomPos(snake.body);
        running = false;
        score = 0;        
    }
};

int main()
{
    cout << "Starting the game..." << endl;

    InitWindow(2 * offset + cellSize * cellCount, 2 * offset + cellSize * cellCount, "Retro Snake");
    SetTargetFPS(60);

    Game game = Game();

    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        if (eventTriggered(0.3))
        {
            game.Update();
        }

        if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1 && game.snake.directionChange)
        {
            game.snake.direction = {0, -1};
            game.snake.directionChange = false;
            game.running = true;
        }
        else if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1 && game.snake.directionChange)
        {
            game.snake.direction = {0, 1};
            game.snake.directionChange = false;
            game.running = true;
        }
        else if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1 && game.snake.directionChange)
        {
            game.snake.direction = {-1, 0};
            game.snake.directionChange = false;
            game.running = true;
        }
        else if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1 && game.snake.directionChange)
        {
            game.snake.direction = {1, 0};
            game.snake.directionChange = false;
            game.running = true;
        }

        ClearBackground(green);

        DrawRectangleLinesEx(Rectangle{(float)offset - 5, (float)offset - 5, (float)cellSize * cellCount + 10, (float)cellSize * cellCount + 10}, 5, darkGreen);

        DrawText("Retro Snake", offset - 5, 25, 40, darkGreen);

        DrawText(TextFormat("%i", game.score), offset - 20 + cellSize * cellCount, 25, 40, darkGreen);

        game.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}