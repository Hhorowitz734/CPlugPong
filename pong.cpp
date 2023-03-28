#include "/opt/homebrew/Cellar/raylib/4.5.0/include/raylib.h"
#include <iostream>
#include <unistd.h> 
#include <cstdlib>
#include <ctime>
#include <cmath>


//RUN THIS CODE WITH cd "/Users/bhorowitz/Documents/CPLUSPLUS/Pong/" && g++ pong.cpp -o pong -I/opt/homebrew/Cellar/raylib/4.5.0/include -L/opt/homebrew/lib -lraylib -std=c++11 && "/Users/bhorowitz/Documents/CPLUSPLUS/Pong/pong"

class Paddle{
    public:
        int xpos;
        int ypos = GetScreenHeight() / 2;
        int speed;

        //Draws the paddle
        void draw(){
            DrawRectangle(xpos, ypos, 4, 50, WHITE);
        }

        void erase(){
            DrawRectangle(xpos, ypos - 5, 4, 60, BLACK);
        }


        //Moves the paddle either up or down
        void move(bool up){
            erase();
            if (up){
                ypos -= speed;
            } else {
                ypos += speed;
            }
        }
};

class Ball{
    public:
        double xpos;
        double ypos;
        double direction;
        double speed = 5;
    
        void generateNew(int screenwidth, int screenheight){
            std::srand(std::time(nullptr));
            xpos = screenwidth / 2;
            ypos = std::rand() % screenheight;
            direction = std::rand() % (int)(2 * M_PI * 180.0 / M_PI);
        }

        void draw(){
            DrawCircle(xpos, ypos, 5, WHITE);
        }

        void erase(double oldxpos, double oldypos){
            DrawCircle(oldxpos, oldypos, 13, BLACK);
        }

        void move(int screenwidth, int screenheight){
            erase(xpos, ypos);
            if (ypos >= screenheight || ypos <= 0){
                double distance_to_wall = (abs(screenwidth - xpos) > xpos) ? xpos : abs(screenwidth - xpos);
                direction = ((360.0 - direction) * (1.0 - distance_to_wall / screenwidth) + 180.0) * (distance_to_wall / screenwidth);
            }
            xpos += speed * sin(direction);
            ypos += speed * cos(direction);
        }


};

int main()
{
    // Initialize the window and set the frame rate
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Pong");
    SetTargetFPS(60);
    ClearBackground(BLACK);

    //Initializes the paddles
    Paddle player;
    Paddle computer;
    player.xpos = 10;
    computer.xpos = screenWidth - 10;

    //Initializes the ball
    Ball ball;
    ball.generateNew(screenWidth, screenHeight);


    // Main game loop
    while (!WindowShouldClose())
    {
        ball.move(screenWidth, screenHeight);

        if (IsKeyDown(KEY_UP)){
            player.move(true);
        }
        if (IsKeyDown(KEY_DOWN)){
            player.move(false);
        }


        // Clear the screen and draw a circle in the center
        BeginDrawing();
        player.draw();
        computer.draw();
        ball.draw();
        EndDrawing();
    }

    // Clean up and exit
    CloseWindow();
    return 0;
}
