#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct Scene Scene;
typedef struct Line Line;

typedef enum
{
    SCENE_UNIVERSITY_GATES,
    SCENE_UNIVERSITY_COURTYARD,
    SCENE_UNIVERSITY_FOUNTAIN,
    SCENE_UNIVERSITY_PARKING,
    SCENE_UNIVERSITY_ROOF_TERRACE,
    SCENE_UNIVERSITY_BACK_ALLEY,

    SCENE_UNIVERSITY_ENTRANCE_HALL,
    SCENE_UNIVERSITY_CORRIDOR_WEST,
    SCENE_UNIVERSITY_CORRIDOR_EAST,
    SCENE_UNIVERSITY_AUDITORIUM_A,
    SCENE_UNIVERSITY_ROOM_101,
    SCENE_UNIVERSITY_DEANS_OFFICE,

    SCENE_UNIVERSITY_HARDWARE_LAB,
    SCENE_UNIVERSITY_COMP_CLASS_B,
    SCENE_UNIVERSITY_SERVER_ROOM,
    SCENE_UNIVERSITY_ROBOTICS_BAY,
    SCENE_UNIVERSITY_AI_RESEARCH_CENTER,

    SCENE_UNIVERSITY_LIBRARY_MAIN,
    SCENE_UNIVERSITY_LIBRARY_ARCHIVE,
    SCENE_UNIVERSITY_CAFETERIA,
    SCENE_UNIVERSITY_COWORKING,
    SCENE_UNIVERSITY_GYM,

    SCENE_UNIVERSITY_BASEMENT_UTILITY,
    SCENE_UNIVERSITY_VENT_SHAFT,
    SCENE_UNIVERSITY_POWER_SUBSTATION,
    SCENE_UNIVERSITY_JANITOR_CLOSET,

    SCENE_HOME_CORRIDOR,
    SCENE_HOME_KITCHEN,
    SCENE_HOME_BATHROOM,
    SCENE_HOME_BEDROOM,
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