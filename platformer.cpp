#include "raylib.h"

#include "globals.h"
#include "level.h"
#include "player.h"
#include "graphics.h"
#include "assets.h"
#include "utilities.h"
#include <ctime>

void update_enemies() {
    for (int i = 0; i < enemyCount; i++) {
        if (!enemies[i].alive) continue;

        // Пробуем сдвинуть врага
        float next_x = enemies[i].pos.x + enemies[i].dx;

        // Если там стена -> враг разворачивается
        if (is_colliding({next_x, enemies[i].pos.y}, WALL)) {
            enemies[i].dx = -enemies[i].dx; // меняем направление
        } else {
            enemies[i].pos.x = next_x;
        }

        // Проверим столкновение с игроком
        Rectangle enemyRect = { enemies[i].pos.x, enemies[i].pos.y, 1.0f, 1.0f };
        Rectangle playerRect= { player_pos.x, player_pos.y, 1.0f, 1.0f };

        if (CheckCollisionRecs(enemyRect, playerRect)) {
            // Например, отнимаем здоровье
            player_health--;
            if (player_health <= 0) {
                current_state = STATE_GAME_OVER;
            } else {
                // Возвращаем игрока на старт уровня
                spawn_player();
            }
        }
    }
}

void draw_enemies() {
    for (int i = 0; i < enemyCount; i++) {
        if (!enemies[i].alive) continue;

        // Перевод координат врага в экранные
        Vector2 screenPos = {
            shift_to_center.x + enemies[i].pos.x * cell_size,
            shift_to_center.y + enemies[i].pos.y * cell_size
        };

        // Простейшая отрисовка — красный прямоугольник
        DrawRectangle(
            (int)screenPos.x,
            (int)screenPos.y,
            (int)cell_size,
            (int)cell_size,
            RED
        );
    }
}

void update_game() {
    game_frame++;

    // TODO

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        move_player_horizontally(MOVEMENT_SPEED);
    }

    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        move_player_horizontally(-MOVEMENT_SPEED);
    }

    // Calculating collisions to decide whether the player is allowed to jump: don't want them to suction cup to the ceiling or jump midair
    is_player_on_ground = is_colliding({player_pos.x, player_pos.y + 0.1f}, WALL);
    if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W) || IsKeyDown(KEY_SPACE)) && is_player_on_ground) {
        player_y_velocity = -JUMP_STRENGTH;
    }

    update_player();

    update_enemies();

    // Нажатие ESC переводит в паузу
    if (IsKeyPressed(KEY_DELETE)) {
        current_state = STATE_PAUSE;
    }
}

void draw_game() {
    // TODO

    ClearBackground(BLACK);
    draw_level();
    draw_enemies();
    draw_game_overlay();
}

Enemy enemies[MAX_ENEMIES];
int enemyCount = 0;

int main() {
    InitWindow(1024, 480, "Platformer");
    SetTargetFPS(60);
    std::srand((unsigned)time(nullptr));


    load_fonts();
    load_images();
    load_sounds();
    load_level();
    load_music();

    PlayMusicStream(bgMusic);

    current_state = STATE_TITLE;

    while (!WindowShouldClose()) {
        UpdateMusicStream(bgMusic);
        BeginDrawing();

        switch (current_state) {
            /* -------------------
               1) Титульный экран
               ------------------- */
            case STATE_TITLE:
                ClearBackground(BLACK);
            draw_menu();
            if (IsKeyPressed(KEY_ENTER)) {
                // Сбросим счёт/здоровье
                player_score  = 0;
                player_health = 3;
                level_index   = 0;

                // Загрузим 1-й уровень
                unload_level();
                load_level(0);

                // Переходим к игре
                current_state = STATE_GAME;
            }
            break;

            /* -----------
               2) Игровой
               ----------- */
            case STATE_GAME:
                update_game();
            draw_game();
            break;

            /* -----------------
               3) Пауза
               ----------------- */
            case STATE_PAUSE:
                ClearBackground(DARKGRAY);
            draw_pause_menu();
            // Если снова ESC → вернуться в игру
            if (IsKeyPressed(KEY_ESCAPE)) {
                current_state = STATE_GAME;
            }
            break;

            /* -----------------
               4) Экран победы
               ----------------- */
            case STATE_VICTORY:
                draw_victory_menu();
            // Если Enter → вернуться в меню
            if (IsKeyPressed(KEY_ENTER)) {
                current_state = STATE_TITLE;
            }
            break;

            /* -----------------
               5) Экран проигрыша
               ----------------- */
            case STATE_GAME_OVER:
                draw_game_over_menu();
            if (IsKeyPressed(KEY_ENTER)) {
                current_state = STATE_TITLE;
            }
            break;
        }

        EndDrawing();
    }

    unload_music();
    unload_level();
    unload_sounds();
    unload_images();
    unload_fonts();

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
