#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct
{
    const char *text;
    int next_scene;
    int next_line;
} Choice;

typedef struct
{
    const char persona_name;
    bool is_persona;
    const char *text;
    int next_scene;
    int next_line;
} Line;

typedef struct
{
    const char *description;
    int i;
    Choice choice[i];
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
    printf("Hello world");
}