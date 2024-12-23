#ifndef LEVEL_H
#define LEVEL_H

#include "globals.h"

bool is_colliding(Vector2 pos, char look_for, level &lvl) {
    Rectangle player_hitbox = { pos.x, pos.y, 1.0f, 1.0f };

    for (size_t row = 0; row < lvl.rows; ++row) {
        for (size_t column = 0; column < lvl.columns; ++column) {
            if (lvl.data[row * lvl.columns + column] == look_for) {
                Rectangle block_hitbox = {
                    (float)column, (float)row,
                    1.0f, 1.0f
                };
                if (CheckCollisionRecs(player_hitbox, block_hitbox)) {
                    return true;
                }
            }
        }
    }
    return false;
}

char& get_collider(Vector2 pos, char look_for, level &lvl) {
    Rectangle player_hitbox = { pos.x, pos.y, 1.0f, 1.0f };

    for (size_t row = 0; row < lvl.rows; ++row) {
        for (size_t column = 0; column < lvl.columns; ++column) {
            if (lvl.data[row * lvl.columns + column] == look_for) {
                Rectangle block_hitbox = {
                    (float)column, (float)row,
                    1.0f, 1.0f
                };
                if (CheckCollisionRecs(player_hitbox, block_hitbox)) {
                    return lvl.data[row * lvl.columns + column];
                }
            }
        }
    }

    // Если ничего не нашли, возвращаем "попадание" по месту,
    // где стоит игрок (не очень безопасно, но для упрощения сойдёт).
    return lvl.data[
        (int)(roundf(pos.y) * lvl.columns + roundf(pos.x))
    ];
}

/*
   Загружаем (level_index + offset)-й уровень:
   - Копируем данные из LEVELS[level_index] в current_level_data
   - Вызываем spawn_player()
   - Пересчитываем метрики для отрисовки
*/
void load_level(int offset) {
    level_index += offset;

    // Если уровни кончились — переключаемся на Victory
    if (level_index >= LEVEL_COUNT) {
        current_state = STATE_VICTORY;
        create_victory_menu_background();
        return;
    }

    // Выделяем память под текущий уровень
    size_t rows    = LEVELS[level_index].rows;
    size_t columns = LEVELS[level_index].columns;
    current_level_data = new char[rows * columns];

    enemyCount = 0;

    // Копируем из шаблона
    for (int row = 0; row < (int)rows; row++) {
        for (int column = 0; column < (int)columns; column++) {
            char cell = LEVELS[level_index].data[row * columns + column];
            current_level_data[row * columns + column] = cell;

            // Если нашли врага, добавим в массив enemies[]
            if (cell == ENEMY_CHAR && enemyCount < MAX_ENEMIES) {
                enemies[enemyCount].pos = { (float)column, (float)row };
                enemies[enemyCount].dx  = 0.02f; // скорость вправо, к примеру
                enemies[enemyCount].alive = true;
                enemyCount++;

                // В самой карте заменим 'M' на ' ', чтобы не мешал
                current_level_data[row * columns + column] = AIR;
            }
        }
    }

    current_level = { rows, columns, current_level_data };

    spawn_player();
    derive_graphics_metrics_from_loaded_level();
}

/*
   Освобождаем память для текущего уровня.
   Вызывается обычно перед загрузкой следующего уровня
   или при выходе из игры.
*/
void unload_level() {
    if (current_level_data) {
        delete[] current_level_data;
        current_level_data = nullptr;
    }
}

#endif // LEVEL_H
