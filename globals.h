#ifndef GLOBALS_H
#define GLOBALS_H

#include "raylib.h"
#include <string>
#include <cstddef>
#include <cmath>

/* ---------------------
   1. Константы символов
   --------------------- */
const char WALL   = '#';
const char AIR    = ' ';
const char PLAYER = '@';
const char COIN   = '*';
const char EXIT   = 'E';

/* ---------------------
   2. Структура уровня
   --------------------- */
struct level {
    size_t rows = 0, columns = 0;
    char *data = nullptr;
};

/* --------------------------------
   3. Данные 5 уровней (Примерные)
   -------------------------------- */
char LEVEL_1_DATA[] = {
    '#','#','#','#','#','#','#','#','#','#','#',
    '#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
    '#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
    '#',' ','M',' ',' ','*',' ',' ',' ',' ','#',
    '#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
    '#',' ','@',' ',' ',' ',' ',' ','E',' ','#',
    '#','#','#','#','#','#','#','#','#','#','#'
};

level LEVEL_1 = {
    7, 11,
    LEVEL_1_DATA
};

char LEVEL_2_DATA[] = {
    '#','#','#','#','#','#','#','#','#','#','#',
    '#',' ',' ',' ',' ','*',' ',' ',' ',' ','#',
    '#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
    '#','*',' ',' ','M',' ',' ',' ',' ',' ','#',
    '#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
    '#',' ',' ',' ',' ',' ','@',' ','E',' ','#',
    '#','#','#','#','#','#','#','#','#','#','#'
};

level LEVEL_2 = {
    7, 11,
    LEVEL_2_DATA
};

char LEVEL_3_DATA[] = {
    '#','#','#','#','#','#','#','#','#','#','#',
    '#',' ',' ',' ','*',' ',' ',' ',' ',' ','#',
    '#',' ','#',' ',' ',' ',' ',' ',' ',' ','#',
    '#',' ','#',' ',' ','@',' ','*',' ',' ','#',
    '#',' ','#',' ',' ',' ',' ',' ',' ',' ','#',
    '#',' ',' ',' ',' ',' ',' ',' ','E',' ','#',
    '#','#','#','#','#','#','#','#','#','#','#'
};

level LEVEL_3 = {
    7, 11,
    LEVEL_3_DATA
};

char LEVEL_4_DATA[] = {
    '#','#','#','#','#','#','#','#','#','#','#',
    '#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
    '#',' ','*',' ',' ',' ','#',' ',' ',' ','#',
    '#',' ',' ',' ',' ',' ','#',' ',' ','*','#',
    '#',' ',' ',' ',' ',' ','#',' ',' ',' ','#',
    '#',' ','@',' ','*',' ','#',' ','E',' ','#',
    '#','#','#','#','#','#','#','#','#','#','#'
};

level LEVEL_4 = {
    7, 11,
    LEVEL_4_DATA
};

char LEVEL_5_DATA[] = {
    '#','#','#','#','#','#','#','#','#','#','#',
    '#',' ','@',' ',' ',' ',' ',' ',' ',' ','#',
    '#',' ','#',' ','*',' ','#',' ',' ',' ','#',
    '#',' ','#',' ',' ',' ','#',' ',' ',' ','#',
    '#',' ','#',' ','*',' ','#',' ',' ',' ','#',
    '#',' ',' ',' ',' ',' ',' ',' ','E',' ','#',
    '#','#','#','#','#','#','#','#','#','#','#'
};

level LEVEL_5 = {
    7, 11,
    LEVEL_5_DATA
};

/* ---------------------------------
   4. Массив уровней и индекс уровней
   --------------------------------- */
int level_index = 0;
const int LEVEL_COUNT = 5;

level LEVELS[LEVEL_COUNT] = {
    LEVEL_1,
    LEVEL_2,
    LEVEL_3,
    LEVEL_4,
    LEVEL_5
};

/* -----------------------------------------
   5. Текущий загруженный уровень и его данные
   ----------------------------------------- */
level current_level;
char *current_level_data = nullptr;

/* -----------------------------------------
   6. Данные игрока (позиция, скорость и т.д.)
   ----------------------------------------- */
const float GRAVITY_FORCE   = 0.01f;
const float JUMP_STRENGTH   = 0.3f;
const float MOVEMENT_SPEED  = 0.1f;

// Позиция игрока в координатах «клеток» уровня
Vector2 player_pos;
float player_y_velocity = 0;
bool is_player_on_ground = false;

// Для примера сделаем счёт очков и небольшое кол-во жизней
int player_score  = 0;
int player_health = 3; // Если хочешь Game Over

/* --------------------------
   7. Параметры масштабирования
   -------------------------- */
const float CELL_SCALE = 0.8f;
const float SCREEN_SCALE_DIVISOR = 700.0f;

Vector2 screen_size;
float screen_scale;
float cell_size;
Vector2 shift_to_center;

/* -----------------------------
   8. Шрифты, тексты, спрайты
   ----------------------------- */
Font menu_font;

struct sprite {
    size_t frame_count    = 0;
    size_t frames_to_skip = 3;
    size_t frames_skipped = 0;
    size_t frame_index    = 0;
    bool loop = true;
    size_t prev_game_frame = 0;
    Texture2D *frames = nullptr;
};

Texture2D wall_image;
Texture2D air_image;
Texture2D exit_image;
extern Texture2D wizard_idle_texture_2d;
sprite coin_sprite;
sprite player_sprite;

/* 9. Звуки */
Sound coin_sound;
Sound exit_sound;
extern Music bgMusic;
/* 10. Victory Screen "шарики" */
struct victory_ball {
    float x, y;
    float dx, dy;
    float radius;
};

const size_t VICTORY_BALL_COUNT     = 2000;
const float  VICTORY_BALL_MAX_SPEED = 2.0f;
const float  VICTORY_BALL_MIN_RADIUS= 2.0f;
const float  VICTORY_BALL_MAX_RADIUS= 3.0f;
const Color  VICTORY_BALL_COLOR     = { 180, 180, 180, 255 };
const unsigned char VICTORY_BALL_TRAIL_TRANSPARENCY = 10;
victory_ball victory_balls[VICTORY_BALL_COUNT];

/* 11. Счётчик кадров */
size_t game_frame = 0;

/* 12. Состояния игры (Title, Game, Pause, ...) */
enum game_state {
    STATE_TITLE,
    STATE_GAME,
    STATE_PAUSE,
    STATE_VICTORY,
    STATE_GAME_OVER
};
game_state current_state = STATE_TITLE;


/* 13. Структура для текста (GUI) */
struct Text {
    std::string str;
    Vector2 position = { 0.50f, 0.50f };
    float size   = 32.0f;
    Color color  = WHITE;
    float spacing= 4.0f;
    Font* font   = &menu_font;
};


// 1) Добавляем символ, который в карте обозначает врага

const char ENEMY_CHAR = 'M';

// 2) Структура, описывающая одного врага

struct Enemy {
    Vector2 pos;  // Позиция в "клетках"
    float dx;     // Скорость по X
    bool alive;
};

// 3) Массив врагов и их текущее количество

const int MAX_ENEMIES = 10;  // Сколько максимум врагов на уровне
extern Enemy enemies[MAX_ENEMIES]; // Объявим в другом .cpp
extern int enemyCount;

/*
   14. Тексты для разных экранов */
Text game_title = {
    "Temple of Treasures",
    { 0.50f, 0.40f },
    50.0f,
    GOLD
};

Text game_subtitle = {
    "Press ENTER to start",
    { 0.50f, 0.55f },
    32.0f
};

Text game_paused = {
    "Press Escape to continue",
    { 0.50f, 0.50f },
    40.0f,
    WHITE
};

Text victory_title = {
    "WIN!",
    { 0.50f, 0.40f },
    100.0f,
    GREEN
};

Text victory_subtitle = {
    "All levels completed!",
    { 0.50f, 0.65f }
};

Text game_over_title = {
    "GAME OVER",
    { 0.50f, 0.40f },
    80.0f,
    RED
};

Text game_over_subtitle = {
        "Press Enter to return to the menu",
    { 0.50f, 0.65f }
};

/* 15. Forward Declarations (прототипы) */
void draw_text(Text &text);
void derive_graphics_metrics_from_loaded_level();
void draw_menu();
void draw_game_overlay();
void draw_level();
void draw_player();
void draw_pause_menu();
void create_victory_menu_background();
void animate_victory_menu_background();
void draw_victory_menu_background();
void draw_victory_menu();
void draw_game_over_menu();

// LEVEL_H
bool is_colliding(Vector2 pos, char look_for = '#', level &level = current_level);
char& get_collider(Vector2 pos, char look_for, level &level = current_level);

void load_level(int offset = 0);
void unload_level();

// PLAYER_H
void spawn_player();
void move_player_horizontally(float delta);
void update_player();

// ASSETS_H
void load_fonts();
void unload_fonts();
void load_images();
void unload_images();
void draw_image(Texture2D image, Vector2 pos, float width, float height);
void draw_image(Texture2D image, Vector2 pos, float size);
sprite load_sprite(const std::string &file_name_prefix,const std::string &file_name_suffix,
                   size_t frame_count = 1,bool loop = true,size_t frames_to_skip = 3);
void unload_sprite(sprite &sprite);
void draw_sprite(sprite &sprite, Vector2 pos, float width, float height);
void draw_sprite(sprite &sprite, Vector2 pos, float size);
void load_sounds();
void unload_sounds();

// UTILITIES_H
float rand_from_to(float from, float to);
float rand_up_to(float to);

#endif // GLOBALS_H
