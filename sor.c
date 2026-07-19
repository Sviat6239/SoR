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
            .next_line = 1},
            {.persona_name = " ",
            .text = "Легкий ветерок огибал меня со всех сторон, так же как и время. Мысль простая, но осознание этого меня будто бы вводило в транс.",
            .next_line = 2},
            {.persona_name = "???",
            .text = "~Нужно будет изменить алгоритм компиляции кода... Скорость есть, но ведь можно быстрее?~",
            .next_line = 3},
            {.persona_name = "???",
            .text = "~А, что это такое \"быстрее\"?~",
            .next_line = 4},
            {.persona_name = " ",
            .text = "Мысли пролетали быстро как неудержимый поток. А где-то на периферии памяти всплыли образы из прошлых лет.",
            .next_line = 5},
            {.persona_name = " ",
            .text = "Тогда я тоже мог часами неподвижно стоять, всматриваясь в серую линию горизонта. Привычка, от которой так и не удалось избавиться.",
            .next_line = 6},
            {.persona_name = "???",
            .text = "~На часах без пяти шесть. Пять минут форы. Лучше выйти с запасом, чтобы контролировать маршрут.~",
            .next_line = 7},
            {.persona_name = " ",
            .text = "Я вернулся в комнату, бесшумно притянув за собой балконную дверь.",
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
        .title = "Коридор",
        .line ={
            {.persona_name = " ",
            .text = "Обулся моментально. Практически не задерживаясь в коридоре.",
            .next_line = 1},
            {.persona_name = " ",
            .text = "Машинально я проверил все ли выключил и вышел из квартиры.",
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
            .next_line = 1},
            {.persona_name = " ",
            .text = "Не отвратительный, но приятным тоже назвать нельзя. Никак привыкнуть не могу к нему.",
            .next_line = 2},
            {.persona_name = "???",
            .text = "~Почему я переехал именно сюда?~",
            .next_line = 3},
            {.persona_name = " ",
            .text = "Снова меня встретила мимолетная мысль.",
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
            .next_line = 1},
            {.persona_name = "???",
            .text = "~Так знакомо, как и тогда~",
            .next_line = 2},
            {.persona_name = " ",
            .text = "Я шел быстрым уверенным шагом. Не спешил, не бежал, шел быстрым темпом.",
            .next_line = 3},
            {.persona_name = " ",
            .text = "Люди шли не спеша.",
            .next_line = 4},
            {.persona_name = "???",
            .text = "~У каждого наверное есть цели, планы... Каждый выбрал свой вектор.~",
            .next_line = 5},
            {.persona_name = "???",
            .text = "~У меня тоже есть цель?~",
            .next_line = 6},
            {.persona_name = "???",
            .text = "~не знаю~",
            .next_line = 7},
            {.persona_name = " ",
            .text = "Тротуар был покрыт пожелтевшими листьями. Время давало о себе знать. Очередная осень...",
            .next_line = 8},
            {.persona_name = " ",
            .text = "Проходя мимо некоторых деревьев, было слышно приятный запах, который всегда ассоциировался с осенью.",
            .next_line = 9},
            {.persona_name = " ",
            .text = "Небо было серым. В нем проплывали птицы, были видны вдалеке высоко линии инверсионного следа.",
            .next_line = 10},
            {.persona_name = " ",
            .text = "Уже подходя к зданию университета я отчетливо видел Виктора чего-то ждущего.",
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
            .next_line = 1},
            {.persona_name = " ",
            .text = "Среди них я видел некоторые знакомые лица - своих одногруппников.",
            .next_line = 2},
            {.persona_name = " ",
            .text = "Виктор повернулся, встал и направился в мою сторону. В руке у него была его сумка, другую же он протянул мне здороваясь.",
            .next_line = 3},
            {.persona_name = "Виктор",
            .text = "Ганс, привет! Что нового у тебя?",
            .next_line = 4},
            {.persona_name = "Ганс",
            .text = "Привет Вик, в общем нормально. Сам как, готов к тесту по алгоритмам?",
            .next_line = 5},
            {.persona_name = " ",
            .text = "Лицо Вика стало хмурым как небо. Явно было видно что он не готов или по крайней мере учился но совсем забыл о нем.",
            .next_line = 6},
            {.persona_name = "Ганс",
            .text = "Ты забыл?",
            .next_line = 7},
            {.persona_name = "Виктор",
            .text = "Я... Две недели назад, как нам объявили о нем, я готовился, но в какой-то момент забыл совсем.",
            .next_line = 8},
            {.persona_name = " ",
            .text = "Парень практически полностью вернулся к обычному выражению лица.",
            .next_line = 9},
            {.persona_name = "Виктор",
            .text = "А что там может быть? Ну на тесте этом.",
            .next_line = 10},
            {.persona_name = " ",
            .text = "~Сам бы хотел знать...~",
            .next_line = 11},
            {.persona_name = "Ганс",
            .text = "К сожалению не могу точно ответить.",
            .next_line = 12},
            {.persona_name = "Ганс",
            .text = "По идее то, что мы проходили.",
            .next_line = 13},
            {.persona_name = " ",
            .text = "Я пытался успокоить Вика давая ему надежду.",
            .next_line = 14},
            {.persona_name = " ",
            .text = "Он по правде говоря не был лучшим в области информатики или алгоритмов, в отличие от компьютерной техники, компьютерных сетей или баз данных.",
            .next_line = 15},
            {.persona_name = " ",
            .text = "Я взглянул на руку. Часы показывали шесть часов сорок восемь минут.",
            .next_line = 16},
            {.persona_name = "Ганс",
            .text = "Почему ты пришел так рано? До пары ведь еще двадцать одна минута.",
            .next_line = 17},
            {.persona_name = "Виктор",
            .text = "Решил прогуляться, но немного время не рассчитал. Вышел раньше, а пришел буквально на пять минут позже, чем обычно.",
            .next_line = 18},
            {.persona_name = "Виктор",
            .text = "Вообще, ты спишь ночью?",
            .next_line = 19},
            {.persona_name = "Ганс",
            .text = "С чего такой вопрос?",
            .next_line = 20},
            {.persona_name = "Виктор",
            .text = "Ну просто ты всегда приходишь в одно и то же время, вернее всегда рано приходишь.",
            .next_line = 21},
            {.persona_name = " ",
            .text = "~Действительно, почему?~",
            .next_line = 22},
            {.persona_name = "Ганс",
            .text = "Привычка.",
            .next_line = 23},
            {.persona_name = "Ганс",
            .text = "Привычка со школы.",
            .next_line = 24},
            {.persona_name = " ",
            .text = "Я соврал.",
            .next_line = 25},
            {.persona_name = "Виктор",
            .text = "Ганс, кстати, а ты слышал о новой хакерской атаке на сеть United Corp. четыре дня назад?",
            .next_line = 26},
            {.persona_name = " ",
            .text = "Я вспомнил то, что говорил мне Ленокс.",
            .next_line = 27},
            {.persona_name = "Ганс",
            .text = "Да, слышал.",
            .next_line = 28},
            {.persona_name = "Ганс",
            .text = "Что-то стало известно о мотивах?",
            .next_line = 29},
            {.persona_name = " ",
            .text = "Неумело я попытался сделать вид, что ничего не знаю.",
            .next_line = 30},
            {.persona_name = "Виктор",
            .text = "Нет, расследование ведется дальше, но ничего нет.",
            .next_line = 31},
            {.persona_name = "Виктор",
            .text = "Буквально ничего, ну или федералы просто не там ищут.",
            .next_line = 32},
            {.persona_name = " ",
            .text = "Я молча склонился ко второму варианту.",
            .next_line = 33},
            {.persona_name = " ",
            .text = "Медленно, но солнце начало пробиваться из-за облаков. На коже и темной форме начало чувствоваться тепло.",
            .next_line = 34},
            {.persona_name = " ",
            .text = "Вдруг меня снова окликнул Вик.",
            .next_line = 35},
            {.persona_name = "Виктор",
            .text = "У тебя с алгоритмами куда лучше, так ведь?",
            .next_line = 36},
            {.persona_name = "Ганс",
            .text = "Да, тебе помочь или проверить твои знания?",
            .next_line = 37},
            {.persona_name = " ",
            .text = "Спокойно спросил его понимая что к этому и клонится дело.",
            .next_line = 38},
            {.persona_name = "Виктор",
            .text = "Буду тебе очень признателен.",
            .next_line = 39},
            {.persona_name = "Ганс",
            .text = "Да, конечно...",
            .next_line = 40},
            {.persona_name = " ",
            .text = "Я оборванно ответил ему.",
            .next_line = 41},
            {.persona_name = " ",
            .text = "Повторно посмотрев на руку, часы показывали уже пятьдесят четыре минуты.",
            .next_line = 42},
            {.persona_name = " ",
            .text = "~Пора бы уже идти к аудитории~",
            .next_line = 43},
            {.persona_name = " ",
            .text = "Я начал направляться к дверям университета, Виктор молча пошел за мной, как бы говоря \"я тебя понял\".",
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
            .next_line = 1},
            {.persona_name = " ",
            .text = "Вик что-то рассказывал по пути, пока мы вошли в здание. Но мыслями я был совсем не в школе.",
            .next_line = 2},
            {.persona_name = " ",
            .text = "А ведь и вправду, почему нет ни одного следа проникновения в систему, должны же быть логи какие-то.",
            .next_line = 3},
            {.persona_name = " ",
            .text = "~Ленокс...~",
            .next_line = 4},
            {.persona_name = " ",
            .text = "В голове крутилось несколько версий: либо сотрудники или само руководство не хотят давать огласки произошедшему, что странно. Либо этот \"хакер\" или группа очень сильно постаралась не оставлять следы.",
            .next_line = 5},
            {.persona_name = " ",
            .text = "~В любом случае... Произошедшее вообще не складывается воедино.~",
            .next_line = 6},
            {.persona_name = " ",
            .text = "Подойдя к аудитории, я снял сумку с плеча и положил на лавочку рядом со входом.",
            .next_line = 7},
            {.persona_name = " ",
            .text = "Виктор поступил точно также, предварительно достав тетрадку по алгоритмам.",
            .next_line = 8},
            {.persona_name = "Ганс",
            .text = "Стоит отметить то, что я удивлен тому, что кто-то еще делает записи от руки в этой стране.",
            .next_line = 9},
            {.persona_name = " ",
            .text = "Виктор вопросительно посмотрел на меня.",
            .next_line = 10},
            {.persona_name = "Виктор",
            .text = "Ну это ведь помогает лучше запоминать, разве нет?",
            .next_line = 11},
            {.persona_name = "Ганс",
            .text = "Про то я и говорю.",
            .next_line = 12},
            {.persona_name = " ",
            .text = "Я собрал вещи и кивком головы указал Вику, что собираюсь внутрь аудитории. Вик, не медля, пошел за мной.",
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
            .next_line = 1},
            {.persona_name = "На моем курсе большая часть людей не знает... Прктически всего не знают! Ноль подготовки, ноль практики, ноль мысли о том что нужно чуть больше времени посвятить на учебу.\nТем не менее Виктор всегда был рядом со мной, что бы он не знал всегда ко мне подходил, спрашивал советывался.",
            .text = "",
            .next_line = 2},
            {.persona_name = " ",
            .text = "Веб не самое чистое место в плане кода или архитектуры. По правде мне всегда нравилась системная разработка, но так или иначе я всегда возвращаюсь сюда...",
            .next_line = 3},
            {.persona_name = " ",
            .text = "В системном программировании никто не простит ошибок, а если твоя программа работает меджленно то единствиная причина сидит перед монитором.",
            .next_line = 4},
            {.persona_name = " ",
            .text = "Я отвлекся на минуту.",
            .next_line = 5},
            {.persona_name = "Ганс",
            .text = "Новое лицо...",
            .next_line = 6},
            {.persona_name = " ",
            .text = "Я прошепта настолько тихо насколько это было возможно.",
            .next_line = 7},
            {.persona_name = "Виктор",
            .text = "Ты, что-то сказал?",
            .next_line = 8},
            {.persona_name = "Ганс",
            .text = "У нас есть новенькие?",
            .next_line = 9},
            {.persona_name = "Виктор",
            .text = "Всмысле?",
            .next_line = 10},
            {.persona_name = "Ганс",
            .text = "Я просто удивлен, что кто то может на третем курсе перейти в другой университет.",
            .next_line = 11},
            {.persona_name = "Виктор",
            .text = "О чем ты?",
            .next_line = 12},
            {.persona_name = "Ганс",
            .text = "Тут новое лицо в аудитории которое я раньше не видел.",
            .next_line = 13},
            {.persona_name = "Виктор",
            .text = "Кажется вспомнил!",
            .next_line = 14},
            {.persona_name = " ",
            .text = "Виткор в пол голоса проговорил.",
            .next_line = 15},
            {.persona_name = "Юджин Ву",
            .text = "Август Виктор и, что же вы вспомнили, не хотите поделится со всеми?",
            .next_line = 16},
            {.persona_name = " ",
            .text = "Виктор встал и извинился перед преподавателем за свое поведение. Я же в тот момент доделывал третье и последние задание.",
            .next_line = 17},
            {.persona_name = "Ганс",
            .text = "На воейне нужно быть тихо. Слышал такое?",
            .next_line = 18},
            {.persona_name = "Виктор",
            .text = "Вот ведь! Почему нам достаются постоянно такие строгие учителя?",
            .next_line = 19},
            {.persona_name = " ",
            .text = "Я лишь молчал, пытаясь понять как эфективно генерировать машинные инструкции.",
            .next_line = 20},
            {.persona_name = " ",
            .text = "",
            .next_line = 21},
            {.persona_name = " ",
            .text = "",
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