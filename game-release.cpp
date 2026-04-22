#include "util.h"      // Muhammad Saif Murtaza, 23i-2588, DS-C                  
#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <sstream>
#include <cmath>

using namespace std;

void SetCanvasSize(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
int current_highscore = 200;
int width = 650, height = 650;
int startx = 320, starty = 400;
const int fixed_size = 500;
int x_direction = 0;
int y_direction = 0;
int x_body[fixed_size];
int y_body[fixed_size];
int n_body = 20;
const int n_fruits = 5;
int x_fruit[n_fruits];
int y_fruit[n_fruits];
int score = 0;

int x_special, y_special;
bool special_exists = false;
const int specialFruitSpawnInterval = 60 * FPS;  // for 60 seconds
const int specialFruitDuration = 15 * FPS;        
int specialFruitTimer = 0;

const int n_hurdles = 10;
int x_hurdles[n_hurdles];
int y_hurdles[n_hurdles];
int hurdle_length[n_hurdles];
int hurdle_timer[n_hurdles];


void draw_snake()      // draws snake with circle as head and square as body
{
    
    for (int i = 1; i < n_body; i++) 
	{
        DrawSquare(x_body[i], y_body[i], 15, colors[GRAY]);
    }

    DrawCircle(x_body[0] + 7.5, y_body[0] + 7.5, 9, colors[CYAN]);
}

bool validity_fruit(int index, int x, int y) // checks for fruits being spawned in same row, column or same diagonal
{
    for (int j = 0; j < index; j++) 
	{
        if ((x == x_fruit[j]) || (y == y_fruit[j]) || (std::abs(x - x_fruit[j]) == std::abs(y - y_fruit[j])))
		{
            return true; 
        }
    }
    return false;
}

void spawn_fruit() // spawns fruit on random locations
{
    for (int i = 0; i < n_fruits; i++) 
	{
        do {
            x_fruit[i] = (rand() % (width / 16)) * 16;
            y_fruit[i] = (rand() % (height / 16)) * 16;
        } while (validity_fruit(i, x_fruit[i], y_fruit[i]));
    }
}

void draw_fruit() // draws fruit at aboved spawned coordinates
{
    for (int i = 0; i < n_fruits; i++) 
	{
        DrawCircle(x_fruit[i], y_fruit[i], 8, colors[RED]);
    }
}
void spawnSpecial(int timer, int& specialFruitSpawnedAt, int& specialFruitCooldown) // gives coordinates to draw special fruit
{
    if (special_exists || specialFruitCooldown > 0) 
	{
        return;
    } else 
	{
        specialFruitCooldown = 60;
        special_exists = true;
        x_special = (rand() % (width / 16)) * 16;
        y_special = (rand() % (height / 16)) * 16;
        specialFruitCooldown = 60;  
    }
}

void drawSpecial() // draws special fruit
{
    if (!special_exists) // exit funtion if special fruit doesnt exist
	{
        return;  
    } else 
	{
        DrawCircle(x_special, y_special, 8, colors[YELLOW]);
    }
}


bool collision_with_special() // checks for collision with special fruit
{
    
    if (abs(x_special - x_body[0]) < 8 && abs(y_special - y_body[0] < 8) && special_exists)
	{
        return true;
    }
    return false;
}

void draw_hurdle() // draws hurdle at random location in the beginning of the program
{
    for (int i = 0; i < n_hurdles; i++) 
	{
        DrawSquare(x_hurdles[i], y_hurdles[i], 16, colors[ORANGE]);
    }
	
}

bool collision_with_hurdle()  // checks for collision of head with the hurdle
{
    for (int i = 0; i < n_hurdles; i++) 
	{
        if ((abs(x_hurdles[i] - x_body[0]) < 8) && (abs(y_hurdles[i] - y_body[0]) < 8))
		{
            return true;
        }
    }
    return false;
}

void spawn_hurdle() // gives coordinates for spawning hurdle at random location
{
    do 
	{
        int startX = 0, startY = 0;
        startX = rand() % ((width / 16) - n_hurdles) * 16;
        startY = rand() % ((height / 16) - n_hurdles) * 16;

        int type = rand() % 2;
        if (type)
		{
            for (int i = 0; i < n_hurdles; i++)
			{
                x_hurdles[i] = startX + i*16;
                y_hurdles[i] = startY;
            }
        }
        else 
		{
            for (int i = 0; i < n_hurdles; i++)
			{
                x_hurdles[i] = startX;
                y_hurdles[i] = startY + i*16;
            }
        }
    }while (collision_with_hurdle());
}




bool collision_with_body() // checks if body collides with head
{
    
    for (int i = 0; i < n_body; i++) 
	{
        if (i > 20 && startx == x_body[i] && starty == y_body[i]) 
		{
            return true;
        }
    }
    return false;
}


bool visibility_fruits = false;


void Timer(int m) 
{
    startx += x_direction * 2;
    starty += y_direction * 2;

    // Check if snake has gone out of the screen horizontally and wraps it around the opposite side
    if (startx < 0) 
	{
        startx = width - 1; 
    } else if (startx >= width) 
	{
        startx = 0; 
    }

    // Check if snake has gone out of the screen vertically and wraps it around the opposite side
    if (starty < 0) 
	{
        starty = height - 1; 
    } else if (starty >= height) 
	{
        starty = 0; 
    }

    int i = n_body - 1;         // this part give typical snake effect to the snake and prevents it form hovering
    while (i > 0) 
	{
        x_body[i] = x_body[i - 1];
        y_body[i] = y_body[i - 1];
        --i;
    }

    x_body[0] = startx;
    y_body[0] = starty;

    static int timer = 0;
    static int last_spawn_time = 0;
    static int specialFruitSpawnedAt = 0;
    static int specialFruitCooldown = 0;

    for (int i = 0; i < n_fruits; i++)  // checks for collision with fruit and if collision is detected, it increases score,length and respawns fruit at random location
	{
        if (abs(x_body[0] - x_fruit[i]) < 13 && abs(y_body[0] - y_fruit[i]) < 13) 
		{ 
            n_body += 5;
            score += 10;
            do 
			{
                x_fruit[i] = rand() % (width / 16) * 16;
                y_fruit[i] = rand() % (height / 16) * 16;
				
            } while (validity_fruit(i, x_fruit[i], y_fruit[i]));
        }
    }

    if (!visibility_fruits)         // spawns fruit if fruit not visible
	{
        visibility_fruits = true;
        spawn_fruit();
        last_spawn_time = timer;
    }
	if ( collision_with_special() ) 
	{
		 special_exists = false;
		 score += 20;
	}

    timer++;
	if (timer % 5 == 0)              // this part is responsible for calculating time intervals for special fruit and spawning it accordingly
	{
        specialFruitCooldown--;
    }
    if (specialFruitCooldown <= 0)
	{
        specialFruitSpawnedAt = timer;
        special_exists = false;
        spawnSpecial(timer, specialFruitSpawnedAt, specialFruitCooldown);
		specialFruitCooldown = 60;
    }
    if (timer - specialFruitSpawnedAt >= 15*1000)
	{
        special_exists = false;
    }
     
	if (timer % specialFruitSpawnInterval == 0 && specialFruitTimer == 0) 
	{
        spawnSpecial(timer, specialFruitSpawnedAt, specialFruitCooldown);
        specialFruitTimer = specialFruitDuration;
    }

    
    if (specialFruitTimer > 0) 
	{
        specialFruitTimer--;
    }

    glClear(GL_COLOR_BUFFER_BIT);

    if (visibility_fruits) 
	{
        draw_fruit();
    }

    if (collision_with_body() || collision_with_hurdle() ) // detects collision with body or hurdle 
	{
        cout << "Game Over! Your Score: " << score << endl;
        exit(0);
    }

    glutPostRedisplay();
    glutTimerFunc(100.0 / FPS, Timer, 0);
}

void Display() {
    glClearColor(0, 0.0, 0.0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    draw_snake();
    if (visibility_fruits) 
	{
        draw_fruit();
    }
	draw_hurdle();
	drawSpecial();

    DrawString(50, 600, "Progress Bar: ", colors[AQUA]);
    DrawString(400, 600, "Score: " + std::to_string(score), colors[AQUA]);
	DrawString(400, 580, "Current Highscore: " + std::to_string(current_highscore), colors[AQUA]);
	if ( score>current_highscore)
	{
		current_highscore = score;
		cout<<" New highscore achieved :"<< score;
	}
	


    int progressBarHeight = 10;
    int progressBarX = 50;
    int progressBarY = 570;

    
    int cyanBarWidth = n_body * 1.5;  
    float cyanColor[] = {0.0, 1.0, 1.0};  

    for (int i = 0; i < cyanBarWidth; i += 2) {
        DrawLine(progressBarX + i, progressBarY, progressBarX + i + 1, progressBarY + progressBarHeight, 3, cyanColor);
    }

    glutSwapBuffers();
}

void NonPrintableKeys(int key, int x, int y) {
    if (key == GLUT_KEY_UP && y_direction == 0) {
        x_direction = 0;
        y_direction = 1;
    } else if (key == GLUT_KEY_DOWN && y_direction == 0) {
        x_direction = 0;
        y_direction = -1;
    } else if (key == GLUT_KEY_LEFT && x_direction == 0) {
        x_direction = -1;
        y_direction = 0;
    } else if (key == GLUT_KEY_RIGHT && x_direction == 0) {
        x_direction = 1;
        y_direction = 0;
    }

    glutPostRedisplay();
}

void PrintableKeys(unsigned char key, int x, int y) {
    if (key == KEY_ESC) {
        exit(1);
    }

    glutPostRedisplay();
}

int main(int argc, char* argv[]) {
    width = 650;
    height = 650;
    InitRandomizer();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(width, height);
    glutCreateWindow("Snake Game");
    SetCanvasSize(width, height);

    glutDisplayFunc(Display);
    glutSpecialFunc(NonPrintableKeys);
    glutKeyboardFunc(PrintableKeys);

    spawn_hurdle();

    glutTimerFunc(5.0 / FPS, Timer, 0);

    glutMainLoop();
    return 0;
}
