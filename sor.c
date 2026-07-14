#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct Scene Scene;
typedef struct Line Line;

typedef enum
{
    SCENE_UNIVERSITY
} SceneID;

typedef struct
{
    const char *text;
    SceneID next_scene;
    int next_line;
} Choice;

typedef struct
{
    const char *persona_name;
    bool is_persona;
    bool is_thoughts;
    const char *text;
    SceneID next_scene;
    int next_line;
} Line;

typedef struct
{
    const char *description;
    Line line[50];
    int line_count;
    Choice choice[10];
    int choice_count;
} Scene;

void clear_screen()
{
    printf("\033[H\033[J");
    fflush(stdout);
}

void type_text(const char *text, unsigned int delay_us)
{
    while (*text)
    {
        putchar(*text++);
        fflush(stdout);
        usleep(delay_us);
    }
    printf("\n");
}

int main()
{
    clear_screen();
    type_text("welcome to simple interactive novel", 4000);
}