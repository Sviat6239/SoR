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
    SCENE_UNIVERSITY_ROOM_102,
    SCENE_UNIVERSITY_ROOM_103,
    SCENE_UNIVERSITY_ROOM_104,
    SCENE_UNIVERSITY_ROOM_105,
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
    SCENE_HOME_APPARTMENT_ENTRANCE,
    
    SCENE_OUTSIDE_NERBY_HOME,

    SCENE_GAME_OVER
} SceneID;

typedef enum
{
    ENDING_GOOD,
    ENDING_BAD,
} EndingsID;

typedef enum {
    NEXT_LINE,
    NEXT_SCENE,
    SHOW_CHOICES
} TransitionType;

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
    TransitionType transition;
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

int get_choice_input(int max_choices)
{
    int selection = -1;
    char input[64];
    
    while (1)
    {
        printf("\033[1;32mВыберите вариант (1-%d): \033[0m", max_choices);
        if (fgets(input, sizeof(input), stdin))
        {
            if (sscanf(input, "%d", &selection) == 1 && selection >= 1 && selection <= max_choices)
            {
                return selection - 1;
            }
        }
        printf("\033[1;31mНеверный ввод. Попробуйте снова.\033[0m\n");
    }
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
            .transition = NEXT_LINE,
            .next_line = 1},
            {.persona_name = " ",
            .text = "Легкий ветерок огибал меня со всех сторон, так же как и время. Мысль простая, но осознание этого меня будто бы вводило в транс.",
            .transition = NEXT_LINE,
            .next_line = 2},
            {.persona_name = "???",
            .text = "~Нужно будет изменить алгоритм компиляции кода... Скорость есть, но ведь можно быстрее?~",
            .transition = NEXT_LINE,
            .next_line = 3},
            {.persona_name = "???",
            .text = "~А, что это такое \"быстрее\"?~",
            .transition = NEXT_LINE,
            .next_line = 4},
            {.persona_name = " ",
            .text = "Мысли пролетали быстро как неудержимый поток. А где-то на периферии памяти всплыли образы из прошлых лет.",
            .transition = NEXT_LINE,
            .next_line = 5},
            {.persona_name = " ",
            .text = "Тогда я тоже мог часами неподвижно стоять, всматриваясь в серую линию горизонта. Привычка, от которой так и не удалось избавиться.",
            .transition = NEXT_LINE,
            .next_line = 6},
            {.persona_name = "???",
            .text = "~На часах без пяти шесть. Пять минут форы. Лучше выйти с запасом, чтобы контролировать маршрут.~",
            .transition = NEXT_LINE,
            .next_line = 7},
            {.persona_name = " ",
            .text = "Я вернулся в комнату, бесшумно притянув за собой балконную дверь.",
            .transition = NEXT_SCENE,
            .next_scene = SCENE_HOME_BEDROOM,
            .next_line = -1}
        },
        .line_count = 8,
        .choice = {},
        .choice_count = 0
    },
    [SCENE_HOME_BEDROOM] = {
        .title = "Спальня",
        .line = {
            {.persona_name = " ",
             .text = "Моя комната была практически пуста. Никакого лишнего хлама, только самый минимум. Скромная, функциональная обитель.",
             .transition = NEXT_LINE,
             .next_line = 1},
            {.persona_name = " ",
             .text = "Инструмент должен выполнять одну задачу, но выполнять её безупречно. Хорошее правило, которое никогда меня не подводило.",
             .transition = NEXT_LINE,
             .next_line = 2},
            {.persona_name = " ",
             .text = "Я бросил быстрый взгляд на рабочий стол. Простой офисный пластик, имитирующий текстуру кедра. Ничего лишнего.",
             .transition = NEXT_LINE,
             .next_line = 3},
            {.persona_name = " ",
             .text = "На краю стола стоял системный блок. Его некогда белый корпус уже заметно пожелтел от времени. Рядом — такой же немолодой монитор. Мой первый настоящий рабочий инструмент, который я когда-то буквально собрал по частям.",
             .transition = NEXT_LINE,
             .next_line = 4},
            {.persona_name = "???",
             .text = "~Неужели я чувствую что-то вроде привязанности к куску железа? Глупо.~",
             .transition = NEXT_LINE,
             .next_line = 5},
            {.persona_name = "???",
             .text = "~Просто секундная расфокусировка. Нужно собраться.~",
             .transition = NEXT_LINE,
             .next_line = 6},
            {.persona_name = "???",
             .text = "~Впрочем, неважно. Прошлого не вернуть, а у меня сегодня первая пара в восемь тридцать.~",
             .transition = NEXT_LINE,
             .next_line = 7},
            {.persona_name = " ",
             .text = "Привычным, доведенным до автоматизма движением я закинул лямку сумки на плечо и направился к выходу.",
             .transition = NEXT_SCENE,
             .next_scene = SCENE_HOME_CORRIDOR,
             .next_line = -1},
        },
        .line_count = 8,
        .choice = {},
        .choice_count = 0 
    },
    [SCENE_HOME_CORRIDOR] = {
        .title = "Коридор",
        .line ={
            {.persona_name = " ",
            .text = "Обулся моментально. Практически не задерживаясь в коридоре.",
            .transition = NEXT_LINE,
            .next_line = 1},
            {.persona_name = " ",
            .text = "Машинально я проверил все ли выключил и вышел из квартиры.",
            .transition = NEXT_SCENE,
            .next_scene = SCENE_HOME_APPARTMENT_ENTRANCE,
            .next_line = -1},
        },
        .line_count = 2,
        .choice = {},
        .choice_count = 0 
    },
    [SCENE_HOME_APPARTMENT_ENTRANCE] = {
        .title = "Подъезд",
        .line ={
            {.persona_name = " ",
            .text = "Подъезд дома в котором я жил имел характерный запах.",
            .transition = NEXT_LINE,
            .next_line = 1},
            {.persona_name = " ",
            .text = "Не отвратительный, но приятным тоже назвать нельзя. Никак привыкнуть не могу к нему.",
            .transition = NEXT_LINE,
            .next_line = 2},
            {.persona_name = "???",
            .text = "~Почему я переехал именно сюда?~",
            .transition = NEXT_LINE,
            .next_line = 3},
            {.persona_name = " ",
            .text = "Снова меня встретила мимолетная мысль.",
            .transition = NEXT_SCENE,
            .next_scene = SCENE_OUTSIDE_NERBY_HOME,
            .next_line = -1},
        },
        .line_count = 4,
        .choice = {},
        .choice_count = 0 
    },
    [SCENE_OUTSIDE_NERBY_HOME] = {
        .title = "Улица",
        .line ={
            {.persona_name = " ",
            .text = "На улице было все так же прохладно.",
            .transition = NEXT_LINE,
            .next_line = 1},
            {.persona_name = "???",
            .text = "~Так знакомо, как и тогда~",
            .transition = NEXT_LINE,
            .next_line = 2},
            {.persona_name = " ",
            .text = "Я шел быстрым уверенным шагом. Не спешил, не бежал, шел быстрым темпом.",
            .transition = NEXT_LINE,
            .next_line = 3},
            {.persona_name = " ",
            .text = "Люди шли не спеша.",
            .transition = NEXT_LINE,
            .next_line = 4},
            {.persona_name = "???",
            .text = "~У каждого наверное есть цели, планы... Каждый выбрал свой вектор.~",
            .transition = NEXT_LINE,
            .next_line = 5},
            {.persona_name = "???",
            .text = "~У меня тоже есть цель?~",
            .transition = NEXT_LINE,
            .next_line = 6},
            {.persona_name = "???",
            .text = "~не знаю~",
            .transition = NEXT_LINE,
            .next_line = 7},
            {.persona_name = " ",
            .text = "Тротуар был покрыт пожелтевшими листьями. Время давало о себе знать. Очередная осень...",
            .transition = NEXT_LINE,
            .next_line = 8},
            {.persona_name = " ",
            .text = "Проходя мимо некоторых деревьев, было слышно приятный запах, который всегда ассоциировался с осенью.",
            .transition = NEXT_LINE,
            .next_line = 9},
            {.persona_name = " ",
            .text = "Небо было серым. В нем проплывали птицы, были видны вдалеке высоко линии инверсионного следа.",
            .transition = NEXT_LINE,
            .next_line = 10},
            {.persona_name = " ",
            .text = "Уже подходя к зданию университета я отчетливо видел Виктора чего-то ждущего.",
            .transition = NEXT_SCENE,
            .next_scene = SCENE_UNIVERSITY_GATES,
            .next_line = -1},
        },
        .line_count = 11,
        .choice = {},
        .choice_count = 0 
    },
        [SCENE_UNIVERSITY_GATES] = {
        .title = "Ворота университета",
        .line ={
            {.persona_name = " ",
            .text = "Я подошел к воротам. Вблизи было много студентов.",
            .transition = NEXT_LINE,
            .next_line = 1},
            {.persona_name = " ",
            .text = "Среди них я видел некоторые знакомые лица - своих одногруппников.",
            .transition = NEXT_LINE,
            .next_line = 2},
            {.persona_name = " ",
            .text = "Виктор повернулся, встал и направился в мою сторону. В руке у него была его сумка, другую же он протянул мне здороваясь.",
            .transition = NEXT_LINE,
            .next_line = 3},
            {.persona_name = "Виктор",
            .text = "Ганс, привет! Что нового у тебя?",
            .transition = NEXT_LINE,
            .next_line = 4},
            {.persona_name = "Ганс",
            .text = "Привет Вик, в общем нормально. Сам как, готов к тесту по алгоритмам?",
            .transition = NEXT_LINE,
            .next_line = 5},
            {.persona_name = " ",
            .text = "Лицо Вика стало хмурым как небо. Явно было видно что он не готов или по крайней мере учился но совсем забыл о нем.",
            .transition = NEXT_LINE,
            .next_line = 6},
            {.persona_name = "Ганс",
            .text = "Ты забыл?",
            .transition = NEXT_LINE,
            .next_line = 7},
            {.persona_name = "Виктор",
            .text = "Я... Две недели назад, как нам объявили о нем, я готовился, но в какой-то момент забыл совсем.",
            .transition = NEXT_LINE,
            .next_line = 8},
            {.persona_name = " ",
            .text = "Парень практически полностью вернулся к обычному выражению лица.",
            .transition = NEXT_LINE,
            .next_line = 9},
            {.persona_name = "Виктор",
            .text = "А что там может быть? Ну на тесте этом.",
            .transition = NEXT_LINE,
            .next_line = 10},
            {.persona_name = " ",
            .text = "~Сам бы хотел знать...~",
            .transition = NEXT_LINE,
            .next_line = 11},
            {.persona_name = "Ганс",
            .text = "К сожалению не могу точно ответить.",
            .transition = NEXT_LINE,
            .next_line = 12},
            {.persona_name = "Ганс",
            .text = "По идее то, что мы проходили.",
            .transition = NEXT_LINE,
            .next_line = 13},
            {.persona_name = " ",
            .text = "Я пытался успокоить Вика давая ему надежду.",
            .transition = NEXT_LINE,
            .next_line = 14},
            {.persona_name = " ",
            .text = "Он по правде говоря не был лучшим в области информатики или алгоритмов, в отличие от компьютерной техники, компьютерных сетей или баз данных.",
            .transition = NEXT_LINE,
            .next_line = 15},
            {.persona_name = " ",
            .text = "Я взглянул на руку. Часы показывали шесть часов сорок восемь минут.",
            .transition = NEXT_LINE,
            .next_line = 16},
            {.persona_name = "Ганс",
            .text = "Почему ты пришел так рано? До пары ведь еще двадцать одна минута.",
            .transition = NEXT_LINE,
            .next_line = 17},
            {.persona_name = "Виктор",
            .text = "Решил прогуляться, но немного время не рассчитал. Вышел раньше, а пришел буквально на пять минут позже, чем обычно.",
            .transition = NEXT_LINE,
            .next_line = 18},
            {.persona_name = "Виктор",
            .text = "Вообще, ты спишь ночью?",
            .transition = NEXT_LINE,
            .next_line = 19},
            {.persona_name = "Ганс",
            .text = "С чего такой вопрос?",
            .transition = NEXT_LINE,
            .next_line = 20},
            {.persona_name = "Виктор",
            .text = "Ну просто ты всегда приходишь в одно и то же время, вернее всегда рано приходишь.",
            .transition = NEXT_LINE,
            .next_line = 21},
            {.persona_name = " ",
            .text = "~Действительно, почему?~",
            .transition = NEXT_LINE,
            .next_line = 22},
            {.persona_name = "Ганс",
            .text = "Привычка.",
            .transition = NEXT_LINE,
            .next_line = 23},
            {.persona_name = "Ганс",
            .text = "Привычка со школы.",
            .transition = NEXT_LINE,
            .next_line = 24},
            {.persona_name = " ",
            .text = "Я соврал.",
            .transition = NEXT_LINE,
            .next_line = 25},
            {.persona_name = "Виктор",
            .text = "Ганс, кстати, а ты слышал о новой хакерской атаке на сеть United Corp. четыре дня назад?",
            .transition = NEXT_LINE,
            .next_line = 26},
            {.persona_name = " ",
            .text = "Я вспомнил то, что говорил мне Ленокс.",
            .transition = NEXT_LINE,
            .next_line = 27},
            {.persona_name = "Ганс",
            .text = "Да, слышал.",
            .transition = NEXT_LINE,
            .next_line = 28},
            {.persona_name = "Ганс",
            .text = "Что-то стало известно о мотивах?",
            .transition = NEXT_LINE,
            .next_line = 29},
            {.persona_name = " ",
            .text = "Неумело я попытался сделать вид, что ничего не знаю.",
            .transition = NEXT_LINE,
            .next_line = 30},
            {.persona_name = "Виктор",
            .text = "Нет, расследование ведется дальше, но ничего нет.",
            .transition = NEXT_LINE,
            .next_line = 31},
            {.persona_name = "Виктор",
            .text = "Буквально ничего, ну или федералы просто не там ищут.",
            .transition = NEXT_LINE,
            .next_line = 32},
            {.persona_name = " ",
            .text = "Я молча склонился ко второму варианту.",
            .transition = NEXT_LINE,
            .next_line = 33},
            {.persona_name = " ",
            .text = "Медленно, но солнце начало пробиваться из-за облаков. На коже и темной форме начало чувствоваться тепло.",
            .transition = NEXT_LINE,
            .next_line = 34},
            {.persona_name = " ",
            .text = "Вдруг меня снова окликнул Вик.",
            .transition = NEXT_LINE,
            .next_line = 35},
            {.persona_name = "Виктор",
            .text = "У тебя с алгоритмами куда лучше, так ведь?",
            .transition = NEXT_LINE,
            .next_line = 36},
            {.persona_name = "Ганс",
            .text = "Да, тебе помочь или проверить твои знания?",
            .transition = NEXT_LINE,
            .next_line = 37},
            {.persona_name = " ",
            .text = "Спокойно спросил его понимая что к этому и клонится дело.",
            .transition = NEXT_LINE,
            .next_line = 38},
            {.persona_name = "Виктор",
            .text = "Буду тебе очень признателен.",
            .transition = NEXT_LINE,
            .next_line = 39},
            {.persona_name = "Ганс",
            .text = "Да, конечно...",
            .transition = NEXT_LINE,
            .next_line = 40},
            {.persona_name = " ",
            .text = "Я оборванно ответил ему.",
            .transition = NEXT_LINE,
            .next_line = 41},
            {.persona_name = " ",
            .text = "Повторно посмотрев на руку, часы показывали уже пятьдесят четыре минуты.",
            .transition = NEXT_LINE,
            .next_line = 42},
            {.persona_name = " ",
            .text = "~Пора бы уже идти к аудитории~",
            .transition = NEXT_LINE,
            .next_line = 43},
            {.persona_name = " ",
            .text = "Я начал направляться к дверям университета, Виктор молча пошел за мной, как бы говоря \"я тебя понял\".",
            .transition = NEXT_SCENE,
            .next_scene = SCENE_UNIVERSITY_ENTRANCE_HALL,
            .next_line = -1},
        },
        .line_count = 44,
        .choice = {},
        .choice_count = 0 
    },
    [SCENE_UNIVERSITY_ENTRANCE_HALL] = {
        .title = "Коридор",
        .line = {
            {.persona_name = " ",
            .text = "Коридор был забит народом. Складывалось ощущение, будто бы даже яблоко не сможет упасть там.",
            .transition = NEXT_LINE,
            .next_line = 1},
            {.persona_name = " ",
            .text = "Вик что-то рассказывал по пути, пока мы вошли в здание. Но мыслями я был совсем не в школе.",
            .transition = NEXT_LINE,
            .next_line = 2},
            {.persona_name = " ",
            .text = "А ведь и вправду, почему нет ни одного следа проникновения в систему, должны же быть логи какие-то.",
            .transition = NEXT_LINE,
            .next_line = 3},
            {.persona_name = " ",
            .text = "~Ленокс...~",
            .transition = NEXT_LINE,
            .next_line = 4},
            {.persona_name = " ",
            .text = "В голове крутилось несколько версий: либо сотрудники или само руководство не хотят давать огласки произошедшему, что странно. Либо этот \"хакер\" или группа очень сильно постаралась не оставлять следы.",
            .transition = NEXT_LINE,
            .next_line = 5},
            {.persona_name = " ",
            .text = "~В любом случае... Произошедшее вообще не складывается воедино.~",
            .transition = NEXT_LINE,
            .next_line = 6},
            {.persona_name = " ",
            .text = "Подойдя к аудитории, я снял сумку с плеча и положил на лавочку рядом со входом.",
            .transition = NEXT_LINE,
            .next_line = 7},
            {.persona_name = " ",
            .text = "Виктор поступил точно также, предварительно достав тетрадку по алгоритмам.",
            .transition = NEXT_LINE,
            .next_line = 8},
            {.persona_name = "Ганс",
            .text = "Стоит отметить то, что я удивлен тому, что кто-то еще делает записи от руки в этой стране.",
            .transition = NEXT_LINE,
            .next_line = 9},
            {.persona_name = " ",
            .text = "Виктор вопросительно посмотрел на меня.",
            .transition = NEXT_LINE,
            .next_line = 10},
            {.persona_name = "Виктор",
            .text = "Ну это ведь помогает лучше запоминать, разве нет?",
            .transition = NEXT_LINE,
            .next_line = 11},
            {.persona_name = "Ганс",
            .text = "Про то я и говорю.",
            .transition = NEXT_LINE,
            .next_line = 12},
            {.persona_name = " ",
            .text = "Я собрал вещи и кивком головы указал Вику, что собираюсь внутрь аудитории. Вик, не медля, пошел за мной.",
            .transition = NEXT_SCENE,
            .next_scene = SCENE_UNIVERSITY_ROOM_101,
            .next_line = -1},
        },
        .line_count = 13,
        .choice = {},
        .choice_count = 0 
    },
    [SCENE_UNIVERSITY_ROOM_101] = {
        .title = "Аудитория 101",
        .line = {
            {.persona_name = " ",
            .text = "Три пары по созданию витрин и веб приложений. День должен быть скучным. \nПо правде я никогда не ненавидел веб-разработку и считаю ее хорошим способом заработать вторую-третью сотню долларов в короткие сроки. \nУчить студентов PHP в месте подобном этому, как по мне глупость хоть 75% всего Интернета написаны на нем.",
            .transition = NEXT_LINE,
            .next_line = 1},
            {.persona_name = " ",
            .text = "На моем курсе большая часть людей не знает... Прктически всего не знают! Ноль подготовки, ноль практики, ноль мысли о том что нужно чуть больше времени посвятить на учебу.\nТем не менее Виктор всегда был рядом со мной, что бы он не знал всегда ко мне подходил, спрашивал советывался.",
            .transition = NEXT_LINE,
            .next_line = 2},
            {.persona_name = " ",
            .text = "Веб не самое чистое место в плане кода или архитектуры. По правде мне всегда нравилась системная разработка, но так или иначе я всегда возвращаюсь сюда...",
            .transition = NEXT_LINE,
            .next_line = 3},
            {.persona_name = " ",
            .text = "В системном программировании никто не простит ошибок, а если твоя программа работает меджленно то единствиная причина сидит перед монитором.",
            .transition = NEXT_LINE,
            .next_line = 4},
            {.persona_name = " ",
            .text = "Я отвлекся на минуту.",
            .transition = NEXT_LINE,
            .next_line = 5},
            {.persona_name = "Ганс",
            .text = "Новое лицо...",
            .transition = NEXT_LINE,
            .next_line = 6},
            {.persona_name = " ",
            .text = "Я прошепта настолько тихо насколько это было возможно.",
            .transition = NEXT_LINE,
            .next_line = 7},
            {.persona_name = "Виктор",
            .text = "Ты, что-то сказал?",
            .transition = NEXT_LINE,
            .next_line = 8},
            {.persona_name = "Ганс",
            .text = "У нас есть новенькие?",
            .transition = NEXT_LINE,
            .next_line = 9},
            {.persona_name = "Виктор",
            .text = "Всмысле?",
            .transition = NEXT_LINE,
            .next_line = 10},
            {.persona_name = "Ганс",
            .text = "Я просто удивлен, что кто то может на третем курсе перейти в другой университет.",
            .transition = NEXT_LINE,
            .next_line = 11},
            {.persona_name = "Виктор",
            .text = "О чем ты?",
            .transition = NEXT_LINE,
            .next_line = 12},
            {.persona_name = "Ганс",
            .text = "Тут новое лицо в аудитории которое я раньше не видел.",
            .transition = NEXT_LINE,
            .next_line = 13},
            {.persona_name = "Виктор",
            .text = "Кажется вспомнил!",
            .transition = NEXT_LINE,
            .next_line = 14},
            {.persona_name = " ",
            .text = "Виткор в пол голоса проговорил.",
            .transition = NEXT_LINE,
            .next_line = 15},
            {.persona_name = "Юджин Ву",
            .text = "Август Виктор и, что же вы вспомнили, не хотите поделится со всеми?",
            .transition = NEXT_LINE,
            .next_line = 16},
            {.persona_name = " ",
            .text = "Виктор встал и извинился перед преподавателем за свое поведение. Я же в тот момент доделывал третье и последние задание.",
            .transition = NEXT_LINE,
            .next_line = 17},
            {.persona_name = "Ганс",
            .text = "На воейне нужно быть тихо. Слышал такое?",
            .transition = NEXT_LINE,
            .next_line = 18},
            {.persona_name = "Виктор",
            .text = "Вот ведь! Почему нам достаются постоянно такие строгие учителя?",
            .transition = NEXT_LINE,
            .next_line = 19},
            {.persona_name = " ",
            .text = "Я лишь молчал, пытаясь понять как эфективно генерировать машинные инструкции.",
            .transition = NEXT_LINE,
            .next_line = 20},
            {.persona_name = "Виктор",
            .text = "Сегодня новенькая к нам перешла.",
            .next_line = 21},
            {.persona_name = " ",
            .text = "Виктор лишь проконстатировал тот факт, что я уже видел",
            .next_line = 22},
            {.persona_name = " ",
            .text = "",
            .next_line = 23},
            {.persona_name = " ",
            .text = "",
            .next_line = 24},
            {.persona_name = " ",
            .text = "",
            .next_line = 25},
            {.persona_name = " ",
            .text = "",
            .next_line = 26},
            {.persona_name = " ",
            .text = "",
            .next_line = 27},
            {.persona_name = " ",
            .text = "",
            .next_line = 28},
            {.persona_name = " ",
            .text = "",
            .next_line = 29},
            {.persona_name = " ",
            .text = "",
            .next_line = 30},
            {.persona_name = " ",
            .text = "",
            .next_line = 31},
            {.persona_name = " ",
            .text = "",
            .next_line = 32},
            {.persona_name = " ",
            .text = "",
            .next_line = -1},
        },
        .line_count = 21,
        .choice = {},
        .choice_count = 0 
    }
    };
    
    int current_scene = SCENE_HOME_BALCONY;
    int current_line = 0;

    fflush(stdin);

    while (current_scene != SCENE_GAME_OVER)
    {
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

        if (active_line.transition == SHOW_CHOICES && active_scene.choice_count > 0)
        {
            printf("--------------------------------------------------\n");
            for (int i = 0; i < active_scene.choice_count; i++)
            {
                printf("  \033[1;33m%d.\033[0m %s\n", i + 1, active_scene.choice[i].text);
            }
            printf("--------------------------------------------------\n\n");

            int selected_idx = get_choice_input(active_scene.choice_count);
            
            current_scene = active_scene.choice[selected_idx].next_scene;
            current_line = active_scene.choice[selected_idx].next_line;
        }
        else
        {
            printf("\033[90m[ Нажмите ENTER для продолжения... ]\033[0m");
            fflush(stdout);
            wait_for_enter();

            if (active_line.transition == NEXT_SCENE)
            {
                current_scene = active_line.next_scene;
                current_line = active_line.next_line;
            }
            else
            {
                current_line = active_line.next_line;
            }
        }
    }

    clear_screen();
    printf("\033[1;33m[ ИГРА ЗАВЕРШЕНА ]\033[0m\n");
    printf("Вы дошли до конца доступного сюжета.\n");
    
    return 0;
}