#include <raylib.h>
#include <math.h>

Color Green = Color{38,185,154,255};
Color DarkGreen = Color{20,160,133,255};
Color Light_Grey = Color{38,185,154,255};
Color Yellow = Color{243,213,91,255};

#include <raylib.h>

class Ammo {
public:
    float x, y;

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
        Vector2 position = GenerateRandomPos();
        // DrawTexture(texture, position.x, position.y,WHITE);
        DrawRectangle(position.x,position.y,50, 50, RED);
    }

    Vector2 GenerateRandomPos() {
        x = GetRandomValue(200, 1000);
        y = GetRandomValue(100, 700);
        return Vector2{x, y};
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

    void Draw() {
        DrawCircle(pos_x, pos_y, radius, RED);
    }

    void Update(Vector2 mousePosition) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            // Calculate the direction vector from the ball to the mouse
            float dir_x = mousePosition.x - pos_x;
            float dir_y = mousePosition.y - pos_y;

            // Normalize the direction vector
            float length = sqrt(dir_x * dir_x + dir_y * dir_y);
            dir_x /= length;
            dir_y /= length;

            // Move the ball in the opposite direction of the mouse
            speed_x = -dir_x * bounce_strength;
            speed_y = -dir_y * bounce_strength;
            pos_x += speed_x;
            pos_y += speed_y;
            bullets -= 1;
        } else {
            // Apply gravitational force to the left and right
            if (pos_x < GetScreenWidth() / 2) {
                speed_x += accel_x;  // Gravity pulls to the right
            } else {
                speed_x -= accel_x;  // Gravity pulls to the left
            }

            // Apply vertical gravity
            speed_y += accel_y;

            // Update position
            pos_x += speed_x;
            pos_y += speed_y;
        }
}
};

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
    player.bullets = 10;

    while (WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(DarkGreen);

        Vector2 mousePosition = GetMousePosition();
        DrawCircle(screen_width/2, screen_height/2, 150, Light_Grey);
        DrawText(TextFormat("%i", player.bullets), screen_width/2 -30, screen_height/2 -50, 100, DARKGRAY);
        player.Update(mousePosition);
        player.Draw();
        DrawLine(player.pos_x, player.pos_y, mousePosition.x, mousePosition.y, Yellow);
        ammo.draw();


        EndDrawing();
    }

    CloseWindow();
    return 0;
}
