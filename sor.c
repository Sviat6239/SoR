#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#ifdef _WIN32
#include <windows.h>
#endif

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
    SCENE_HOME_BALCONY,

    SCENE_HOME_APPARTMENT_ENTRANCE
} SceneID;

typedef enum
{
    ENDING_GOOD,
    ENDING_BAD,
} EndingsID;

typedef struct
{
    const char *text;
    SceneID next_scene;
    int next_line;
} Choice;

typedef struct
{
    const char *persona_name;
    const char *text;
    SceneID next_scene;
    int next_line;
} Line;

typedef struct
{   
    const char *title;
    Line line[180];
    int line_count;
    Choice choice[24];
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

void wait_for_enter()
{
    while (getchar() != '\n');
}


int main()
{

    #ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    #endif

    Scene sor[] = {
    [SCENE_HOME_BALCONY] = {
        .title = "Балкон",
        .line = {
            {.persona_name = " ",
            .text = "Я вышел на балкон. Свежий утренний воздух приятно холодил кожу — идеальная температура, чтобы окончательно проснуться.",
            .next_line = 1},
            {.persona_name = " ",
            .text = "Где-то на периферии памяти всплыли образы из прошлых лет. Тогда я тоже мог часами неподвижно стоять, всматриваясь в серую линию горизонта. Привычка, от которой так и не удалось избавиться.",
            .next_line = 2},
            {.persona_name = "???",
            .text = "~На часах без пяти шесть. Пять минут форы. Лучше выйти с запасом, чтобы контролировать маршрут.~",
            .next_line = 3},
            {.persona_name = " ",
            .text = "Я вернулся в комнату, бесшумно притянув за собой балконную дверь.",
            .next_scene = SCENE_HOME_BEDROOM,
            .next_line = -1}
        },
        .line_count = 4,
        .choice = {},
        .choice_count = 0
    },
    [SCENE_HOME_BEDROOM] = {
        .title = "Спальня",
        .line = {
            {.persona_name = " ",
             .text = "Моя комната была практически пуста. Никакого лишнего хлама, только самый минимум. Скромная, функциональная обитель.",
             .next_line = 1},
            {.persona_name = " ",
             .text = "Инструмент должен выполнять одну задачу, но выполнять её безупречно. Хорошее правило, которое никогда меня не подводило.",
             .next_line = 2},
            {.persona_name = " ",
             .text = "Я бросил быстрый взгляд на рабочий стол. Простой офисный пластик, имитирующий текстуру кедра. Ничего лишнего.",
             .next_line = 3},
            {.persona_name = " ",
             .text = "На краю стола стоял системный блок. Его некогда белый корпус уже заметно пожелтел от времени. Рядом — такой же немолодой монитор. Мой первый настоящий рабочий инструмент, который я когда-то буквально собрал по частям.",
             .next_line = 4},
            {.persona_name = "???",
             .text = "~Неужели я чувствую что-то вроде привязанности к куску железа? Глупо.~",
             .next_line = 5},
            {.persona_name = "???",
             .text = "~Просто секундная расфокусировка. Нужно собраться.~",
             .next_line = 6},
            {.persona_name = "???",
             .text = "~Впрочем, неважно. Прошлого не вернуть, а у меня сегодня первая пара в восемь тридцать.~",
             .next_line = 7},
            {.persona_name = " ",
             .text = "Привычным, доведенным до автоматизма движением я закинул лямку сумки на плечо и направился к выходу.",
             .next_scene = SCENE_HOME_CORRIDOR,
             .next_line = -1},
        },
        .line_count = 8,
        .choice = {},
        .choice_count = 0 
    },
    [SCENE_HOME_CORRIDOR] = {
        .line ={
            {.persona_name = "",
            .text = "Обулся моментально. Практически не задерживаясь в корридоре.",
            .next_line = 1},
            {.persona_name = "",
            .text = "Машинально я проверил все ли выключил и вышел из квартиры.",
            .next_scene = SCENE_HOME_APPARTMENT_ENTRANCE,
            .next_line = -1},
        },
        .line_count = 2,
        .choice = {},
        .choice_count = 0 
    }
    };
    
    int current_scene = SCENE_HOME_BALCONY;
    int current_line = 0;

    fflush(stdin);

    while (current_scene != -1){
        Scene active_scene = sor[current_scene];
        Line active_line = active_scene.line[current_line];

        clear_screen();

        printf("\033[1;36m[ ЛОКАЦИЯ: %s ]\033[0m\n", active_scene.title);
        printf("==================================================\n\n");

        if (active_line.persona_name != NULL && active_line.persona_name[0] != '\0')
        {
            printf("\033[1;32m%s\033[0m\n", active_line.persona_name);
        }
        else
        {
            printf("\033[1;30m[Автор]:\033[0m\n");
        }

        printf("  ");
        type_text(active_line.text, 10000);
        printf("\n\n");

        printf("\033[90m[ Нажмите ENTER для продолжения... ]\033[0m");
        fflush(stdout);

        wait_for_enter();
   
        if (active_line.next_line == -1)
        {
            current_scene = active_line.next_scene; 

            current_line = 0; 

            if (current_scene == -1) 
            {
                clear_screen();
                printf("\033[1;33m[ ИГРА ЗАВЕРШЕНА ]\033[0m\n");
                printf("Вы дошли до конца доступного сюжета.\n");
                break; 
            }
        }
        else
        {
            current_line = active_line.next_line;
        }
    }
}