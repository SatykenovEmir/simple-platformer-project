#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "globals.h"

/*
   Отрисовка текста по центру относительно text.position (0..1).
   text.size умножается на screen_scale для визуальной корректности (необязательно).
*/
void draw_text(Text &text) {
    float scaledSize = text.size * screen_scale;
    Vector2 dimensions = MeasureTextEx(*text.font, text.str.c_str(), scaledSize, text.spacing);
    Vector2 pos = {
        (screen_size.x * text.position.x) - (0.5f * dimensions.x),
        (screen_size.y * text.position.y) - (0.5f * dimensions.y)
    };
    DrawTextEx(*text.font, text.str.c_str(), pos, scaledSize, text.spacing, text.color);
}

/*
   Определяем размеры клетки (cell_size) и screen_scale
   на основе размеров окна и кол-ва колонок/строк уровня
*/
void derive_graphics_metrics_from_loaded_level() {
    screen_size.x = (float)GetScreenWidth();
    screen_size.y = (float)GetScreenHeight();

    cell_size = std::min(
        screen_size.x / (float)current_level.columns,
        screen_size.y / (float)current_level.rows
    ) * CELL_SCALE;

    screen_scale = std::min(screen_size.x, screen_size.y) / SCREEN_SCALE_DIVISOR;

    float level_width  = (float)current_level.columns * cell_size;
    float level_height = (float)current_level.rows    * cell_size;
    shift_to_center.x = (screen_size.x - level_width)  * 0.5f;
    shift_to_center.y = (screen_size.y - level_height) * 0.5f;
}

/* ---------------------------
   1) Title Screen (draw_menu)
   --------------------------- */
void draw_menu() {
    draw_text(game_title);
    draw_text(game_subtitle);
}

/* ---------------------------
   2) HUD — показываем счёт и жизни
   --------------------------- */
void draw_game_overlay() {
    // Тень
    Text hud_shadow = {
        "Point: " + std::to_string(player_score) +
        " | HP: " + std::to_string(player_health),
        { 0.505f, 0.05f },
        36.0f,
        DARKGRAY
    };
    draw_text(hud_shadow);

    // Текст
    Text hud = {
        "Point: " + std::to_string(player_score) +
        " | HP: " + std::to_string(player_health),
        { 0.50f, 0.05f },
        36.0f,
        WHITE
    };
    draw_text(hud);
}

/* ---------------------------
   3) Отрисовка уровня и игрока
   --------------------------- */
void draw_level() {
    for (size_t row = 0; row < current_level.rows; ++row) {
        for (size_t column = 0; column < current_level.columns; ++column) {
            Vector2 pos = {
                shift_to_center.x + (float)column * cell_size,
                shift_to_center.y + (float)row    * cell_size
            };
            char cell = current_level.data[row * current_level.columns + column];

            // "Фон" клетки
            switch (cell) {
                case AIR:
                case PLAYER:
                case COIN:
                case EXIT:
                    draw_image(air_image, pos, cell_size);
                    break;
                case WALL:
                    draw_image(wall_image, pos, cell_size);
                    break;
            }

            // Дополнительная отрисовка поверх фона
            switch (cell) {
                case COIN:
                    draw_sprite(coin_sprite, pos, cell_size);
                    break;
                case EXIT:
                    draw_image(exit_image, pos, cell_size);
                    break;
                default:
                    break;
            }
        }
    }

    // В самом конце — игрок
    draw_player();
}

/*
   Отрисовка спрайта игрока
*/
void draw_player() {
    Vector2 pos = {
        shift_to_center.x + player_pos.x * cell_size,
        shift_to_center.y + player_pos.y * cell_size
    };
    draw_sprite(player_sprite, pos, cell_size);
}

/* -----------------------------
   4) Экран паузы
   ----------------------------- */
void draw_pause_menu() {
    draw_text(game_paused);
}

/* -----------------------------
   5) Экран победы
   ----------------------------- */
void create_victory_menu_background() {
    // Инициализируем шарики
    for (auto &ball : victory_balls) {
        ball.x  = rand_up_to(screen_size.x);
        ball.y  = rand_up_to(screen_size.y);
        ball.dx = rand_from_to(-VICTORY_BALL_MAX_SPEED, VICTORY_BALL_MAX_SPEED) * screen_scale;
        if (fabs(ball.dx) < 0.01f) ball.dx = 1.0f;
        ball.dy = rand_from_to(-VICTORY_BALL_MAX_SPEED, VICTORY_BALL_MAX_SPEED) * screen_scale;
        if (fabs(ball.dy) < 0.01f) ball.dy = 1.0f;
        ball.radius = rand_from_to(VICTORY_BALL_MIN_RADIUS, VICTORY_BALL_MAX_RADIUS) * screen_scale;
    }

    // Сгладим кадры: очистим задний/передний буфер
    ClearBackground(BLACK);
    EndDrawing();
    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();
    BeginDrawing();
}

void animate_victory_menu_background() {
    for (auto &ball : victory_balls) {
        ball.x += ball.dx;
        if (ball.x - ball.radius < 0 || ball.x + ball.radius >= screen_size.x) {
            ball.dx = -ball.dx;
        }
        ball.y += ball.dy;
        if (ball.y - ball.radius < 0 || ball.y + ball.radius >= screen_size.y) {
            ball.dy = -ball.dy;
        }
    }
}

void draw_victory_menu_background() {
    for (auto &ball : victory_balls) {
        DrawCircleV({ ball.x, ball.y }, ball.radius, VICTORY_BALL_COLOR);
    }
}

void draw_victory_menu() {
    // Полупрозрачный чёрный фон, чтобы шлейф оставался
    DrawRectangle(
        0, 0,
        (int)screen_size.x, (int)screen_size.y,
        { 0, 0, 0, VICTORY_BALL_TRAIL_TRANSPARENCY }
    );
    animate_victory_menu_background();
    draw_victory_menu_background();

    draw_text(victory_title);
    draw_text(victory_subtitle);
}

/* -----------------------------
   6) Экран Game Over
   ----------------------------- */
void draw_game_over_menu() {
    ClearBackground(BLACK);
    draw_text(game_over_title);
    draw_text(game_over_subtitle);
}

#endif // GRAPHICS_H
