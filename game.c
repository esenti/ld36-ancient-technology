#include <stdlib.h>
#include <ncurses.h>

struct Thing {
    float x;
    float y;
    int dirX;
    int dirY;
    bool active;
};

struct Thing bullets[10];
struct Thing enemies[10];

int main()
{
    initscr();
    timeout(0);
    raw();
    noecho();
    curs_set(0);

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    attron(COLOR_PAIR(1));


    float playerX = COLS / 2;
    float playerY = LINES / 2;
    char ch;
    int score = 0;
    bool playing = true;

    while(playing)
    {
        ch = getch();

        if(ch == 'a')
        {
            playerX -= 1;
        }
        else if(ch == 'd')
        {
            playerX += 1;
        }
        else if(ch == 'w')
        {
            playerY -= 1;
        }
        else if(ch == 's')
        {
            playerY += 1;
        }
        else if(ch == 'j')
        {
            for(int i = 0; i < 10; i++)
            {
                if(!bullets[i].active)
                {
                    bullets[i].x = playerX;
                    bullets[i].y = playerY;
                    bullets[i].dirX = -1;
                    bullets[i].dirY = 0;
                    bullets[i].active = true;
                    break;
                }
            }
        }
        else if(ch == 'l')
        {
            for(int i = 0; i < 10; i++)
            {
                if(!bullets[i].active)
                {
                    bullets[i].x = playerX;
                    bullets[i].y = playerY;
                    bullets[i].dirX = 1;
                    bullets[i].dirY = 0;
                    bullets[i].active = true;
                    break;
                }
            }
        }
        else if(ch == 'i')
        {
            for(int i = 0; i < 10; i++)
            {
                if(!bullets[i].active)
                {
                    bullets[i].x = playerX;
                    bullets[i].y = playerY;
                    bullets[i].dirX = 0;
                    bullets[i].dirY = -1;
                    bullets[i].active = true;
                    break;
                }
            }
        }
        else if(ch == 'k')
        {
            for(int i = 0; i < 10; i++)
            {
                if(!bullets[i].active)
                {
                    bullets[i].x = playerX;
                    bullets[i].y = playerY;
                    bullets[i].dirX = 0;
                    bullets[i].dirY = 1;
                    bullets[i].active = true;
                    break;
                }
            }
        }
        else if(ch == 27)
        {
            playing = false;
        }

        if(!(rand() % 200))
        {
            for(int i = 0; i < 10; i++)
            {
                if(!enemies[i].active)
                {
                    if(rand() % 2)
                    {
                        enemies[i].dirY = 0;
                        enemies[i].y = rand() % LINES;

                        if(rand() % 2)
                        {
                            enemies[i].x = 0;
                            enemies[i].dirX = 1;
                        }
                        else
                        {
                            enemies[i].x = COLS;
                            enemies[i].dirX = -1;
                        }
                    }
                    else
                    {
                        enemies[i].dirX = 0;
                        enemies[i].x = rand() % COLS;

                        if(rand() % 2)
                        {
                            enemies[i].y = 0;
                            enemies[i].dirY = 1;
                        }
                        else
                        {
                            enemies[i].y = LINES;
                            enemies[i].dirY = -1;
                        }
                    }

                    enemies[i].active = true;
                    break;
                }
            }
        }

        erase();

        for(int i = 0; i < 10; i++)
        {
            if(bullets[i].active)
            {
                bullets[i].x += bullets[i].dirX * 0.0005;
                bullets[i].y += bullets[i].dirY * 0.0005;

                char c;

                if(bullets[i].dirX)
                {
                    c = '-';
                }
                else
                {
                    c = '|';
                }

                mvaddch(bullets[i].y, bullets[i].x, c);

                if(bullets[i].x < 0 || bullets[i].x > COLS || bullets[i].y < 0 || bullets[i].y > LINES)
                {
                    bullets[i].active = false;
                }

                for(int j = 0; j < 10; j++)
                {
                    if(enemies[j].active)
                    {
                        if((int)bullets[i].x == (int)enemies[j].x && (int)bullets[i].y == (int)enemies[j].y)
                        {
                            score += 1;
                            enemies[j].active = false;
                        }
                    }
                }
            }
        }

        for(int i = 0; i < 10; i++)
        {
            if(enemies[i].active)
            {
                enemies[i].x += enemies[i].dirX * 0.0002;
                enemies[i].y += enemies[i].dirY * 0.0002;

                char c;

                if(enemies[i].dirX)
                {
                    c = 'o';
                }
                else
                {
                    c = 'o';
                }

                mvaddch(enemies[i].y, enemies[i].x, c);

                if(enemies[i].x < 0 || enemies[i].x > COLS || enemies[i].y < 0 || enemies[i].y > LINES)
                {
                    enemies[i].active = false;
                }

                if((int)enemies[i].x == playerX && (int)enemies[i].y == playerY)
                {
                    playing = false;
                }
            }
        }

        mvaddch(playerY, playerX, '@');
        mvprintw(0, 0, "%d", score);
        refresh();
    }

    endwin();

    return 0;
}
