#ifndef PLAYER_H
#define PLAYER_H

#include "globals.h"

/*
   Находим в текущем уровне символ PLAYER ('@') и ставим
   player_pos на эту клетку.
*/
void spawn_player() {
    for (size_t row = 0; row < current_level.rows; ++row) {
        for (size_t column = 0; column < current_level.columns; ++column) {
            char cell = current_level.data[row * current_level.columns + column];
            if (cell == PLAYER) {
                player_pos.x = (float)column;
                player_pos.y = (float)row;
                return;
            }
        }
    }
}

/*
   Двигаем игрока по горизонтали, если нет коллизии со стеной ('#').
*/
void move_player_horizontally(float delta) {
    float next_x = player_pos.x + delta;
    if (!is_colliding({ next_x, player_pos.y }, WALL)) {
        player_pos.x = next_x;
    } else {
        // Если упёрлись в стену, поправим позицию на "целое" значение
        player_pos.x = roundf(player_pos.x);
    }
}

/*
   Основная функция обновления игрока:
   - Применяем гравитацию
   - Проверяем коллизии снизу/собираем монеты/выход
   - Проверяем, не "упал" ли игрок ниже уровня -> Game Over
*/
void update_player() {
    // Применяем вертикальное движение
    player_pos.y += player_y_velocity;
    // Гравитация
    player_y_velocity += GRAVITY_FORCE;

    // Проверяем, стоим ли мы на земле (стене/платформе)
    is_player_on_ground = is_colliding({ player_pos.x, player_pos.y + 0.1f }, WALL);
    if (is_player_on_ground) {
        // Если "на земле" — обнуляем скорость и выравниваем по сетке
        player_y_velocity = 0;
        player_pos.y = roundf(player_pos.y);
    }

    // Собираем монету?
    if (is_colliding(player_pos, COIN)) {
        get_collider(player_pos, COIN) = AIR; // Стираем монету
        player_score += 10;
        PlaySound(coin_sound);
    }

    // Достигли выхода?
    if (is_colliding(player_pos, EXIT)) {
        PlaySound(exit_sound);
        unload_level();
        load_level(1); // Загружаем следующий уровень
        return;
    }

    // Пример «Падение за границы»:
    // Если упал ниже уровня (row >= current_level.rows),
    // то считаем, что игрок погиб -> Game Over
    if (player_pos.y >= (float)current_level.rows - 1) {
        player_health--;
        if (player_health <= 0) {
            // Вызываем экран проигрыша
            current_state = STATE_GAME_OVER;
        } else {
            // Переспавнить на начале уровня
            spawn_player();
            player_y_velocity = 0;
        }
    }
}

#endif // PLAYER_H
