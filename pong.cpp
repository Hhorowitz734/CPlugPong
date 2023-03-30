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
        int speed = 5;
        int score = 0;

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
        double dx;
        double dy;
    
        void generateNew(int screenwidth, int screenheight){
            std::srand(std::time(nullptr));
            xpos = screenwidth / 2;
            ypos = std::rand() % screenheight;
            dx = (rand() % 2 == 0) ? -5 : 5;
            dy = (std::rand() % 1) - (std::rand() % 10);
        }

        void draw(){
            DrawCircle(xpos, ypos, 5, WHITE);
        }

        void erase(double oldxpos, double oldypos){
            DrawCircle(oldxpos, oldypos, 17, BLACK);
        }

        void move(int screenwidth, int screenheight){
            erase(xpos, ypos);
            if (ypos >= screenheight || ypos <= 0){
                dy = 0 - dy;
            }
            xpos += dx;
            ypos += dy;
        }

        bool checkScore(Paddle& player, Paddle& computer){ //Take in paddle and handle score n stuff
            if (xpos <= player.xpos){
                if (player.ypos <= ypos && player.ypos + 50 >= ypos){
                    dx = 0 - dx;
                    dy += (std::rand() % 5) - (std::rand() % 5);
                }
                else {
                    ClearBackground(BLACK);
                    erase(xpos, ypos);
                    computer.score += 1;
                    std::cout << "\nCOMPUTER SCORE: " << computer.score;
                    generateNew(GetScreenWidth(), GetScreenHeight());
                }
            }
            if (xpos >= computer.xpos){
                if (computer.ypos <= ypos && computer.ypos + 50 >= ypos){
                    dx = 0 - dx;
                    dy += (std::rand() % 5) - (std::rand() % 5);
                }
                else {
                    ClearBackground(BLACK);
                    //erase(xpos, ypos);
                    //player.score += 1;
                    //std::cout << "\nPLAYER SCORE: " << computer.score;
                    //generateNew(GetScreenWidth(), GetScreenHeight());
                    dx = 0 - dx;
                    dy *= (std::rand() % 2); - (std::rand() % 2);
                }
            }
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
        ball.checkScore(player, computer);

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
