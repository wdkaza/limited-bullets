#include <raylib.h>
#include <math.h>

Color Green = Color{38,185,154,255};
Color DarkGreen = Color{20,160,133,255};
Color Light_Grey = Color{38,185,154,255};
Color Yellow = Color{243,213,91,255};

class Ammo {
public:
    float x, y;
    float width = 50;
    float height = 50;


    Ammo()
    {
        Vector2 position = GenRanPos();
        x = position.x;
        y = position.y;
    }
    Vector2 GenRanPos()
    {
        Vector2 position = GenerateRandomPos();
        return position;
    }
    // Texture2D texture;
    // Ammo()
    // {
    //     Image image = LoadImage("graphics/food.png");
    //     texture = LoadTextureFromImage(image);
    //     UnloadImage(image);
    // }
    // ~Ammo()
    // {
    //     UnloadTexture(texture);
    // }

    void draw() {
        DrawRectangle(x,y,50, 50, RED);
    }

    Vector2 GenerateRandomPos() {
        x = GetRandomValue(200, 1000);
        y = GetRandomValue(100, 700);
        return Vector2{x, y};
};
    Rectangle GetRect() {
        return Rectangle{x, y, width, height};
    }
    };
class Player {
public:
    float pos_x, pos_y;
    int radius;
    float accel_x, accel_y;
    float speed_x, speed_y;
    float bounce_strength;
    int bullets;
    Rectangle GetRect();
    void drawHitbox(bool isColliding);
    void eat(bool isColliding);
    void UpdateWrap(int screen_width,int screen_height);

    void Draw() {
        DrawCircle(pos_x, pos_y, radius, RED);
    }

    void Update(Vector2 mousePosition) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            float dir_x = mousePosition.x - pos_x;
            float dir_y = mousePosition.y - pos_y;

            float length = sqrt(dir_x * dir_x + dir_y * dir_y);
            dir_x /= length;
            dir_y /= length;

            speed_x = -dir_x * bounce_strength;
            speed_y = -dir_y * bounce_strength;
            pos_x += speed_x;
            pos_y += speed_y;
            bullets -= 1;
        } else {
            if (pos_x < GetScreenWidth() / 2) {
                speed_x += accel_x; 
            } else {
                speed_x -= accel_x; 
            }
            
            speed_y += accel_y;

            pos_x += speed_x;
            pos_y += speed_y;
        }
}
};
bool pause = true;
Player player;
Ammo ammo;

int main() {
    const int screen_width = 1280;
    const int screen_height = 800;
    InitWindow(screen_width, screen_height, "wow");
    SetTargetFPS(60);

    player.pos_x = screen_width / 2;
    player.pos_y = screen_height / 2;
    player.radius = 20;
    player.speed_x = 0;
    player.speed_y = 0;
    player.accel_x = 0.1;
    player.accel_y = 0.3;
    player.bounce_strength = 15;
    player.bullets = 5;
    while (WindowShouldClose() == false && player.bullets >= 0) {

        if(IsKeyPressed(KEY_SPACE))
        pause = !pause;

        BeginDrawing();
        ClearBackground(DarkGreen);
        bool isColliding = CheckCollisionCircleRec(Vector2{player.pos_x, player.pos_y}, player.radius, ammo.GetRect());
        DrawCircle(screen_width/2, screen_height/2, 150, Light_Grey);
        if(!pause)
        {
                Vector2 mousePosition = GetMousePosition();
                player.Update(mousePosition);
                DrawLine(player.pos_x, player.pos_y, mousePosition.x, mousePosition.y, Yellow);
        }
        else
        {
            DrawText("Press space to play", 400, 200, 20, LIGHTGRAY);
        }
        DrawText(TextFormat("%i", player.bullets), screen_width/2 -30, screen_height/2 -50, 100, DARKGRAY);
        player.Draw();
        player.drawHitbox(isColliding);
        player.UpdateWrap(screen_width,screen_height);
        player.eat(isColliding);
        ammo.draw();


        EndDrawing();
    }

    CloseWindow();
    return 0;
}

Rectangle Player::GetRect() {
    return Rectangle{pos_x - radius, pos_y - radius, radius * 2, radius * 2};
}

void Player::drawHitbox(bool isColliding)
{
    Color outlinecolor = isColliding ? RED : BLACK;
    DrawRectangleLinesEx(GetRect(),3,outlinecolor);
}
void Player::eat(bool isCollding)
{
    if (isCollding == true)
    {
        ammo.GenRanPos();
        player.bullets++;
    }
}
void Player::UpdateWrap(int screen_width,int screen_height)
{
    if(pos_x > screen_width + radius)
    {
        pos_x = -radius;
    }
    else if(pos_x < radius)
    {
        pos_x = screen_width + radius;
    }
    if(pos_y > screen_height + radius)
    {
        player.bullets = -1;
    }
}
