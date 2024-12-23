#ifndef ASSETS_H
#define ASSETS_H

#include "raylib.h"
#include "globals.h"

#include <string>
#include <cassert>

Texture2D wizard_idle_texture_2d;
Music bgMusic;

/* ------------------------
   1) Fonts
   ------------------------ */
void load_fonts() {
    // Загрузим один шрифт
    // Можно менять путь/размер
    menu_font = LoadFontEx("data/fonts/ARCADE_N.ttf", 48, nullptr, 250);

}

void load_music() {
    bgMusic = LoadMusicStream("data/music/music.mp3");
}
void unload_music() {
    UnloadMusicStream(bgMusic);
}

void unload_fonts() {
    UnloadFont(menu_font);
}

/* ------------------------
   2) Images / Sprites
   ------------------------ */
void load_images() {
    wall_image  = LoadTexture("data/images/wall.png");
    air_image   = LoadTexture("data/images/air.png");
    exit_image  = LoadTexture("data/images/exit.png");

    // Загрузим анимацию монеты
    coin_sprite = load_sprite("data/images/coin/coin", ".png", 3, true, 18);
    // Загрузим анимацию игрока
    player_sprite = load_sprite("data/images/player/player", ".png", 3, true, 10);
}

void unload_images() {
    UnloadTexture(wall_image);
    UnloadTexture(air_image);
    UnloadTexture(exit_image);

    unload_sprite(player_sprite);
    unload_sprite(coin_sprite);
}

/*
   Упрощённые функции отрисовки (draw_image / draw_sprite)
*/
void draw_image(Texture2D image, Vector2 pos, float size) {
    draw_image(image, pos, size, size);
}

void draw_image(Texture2D image, Vector2 pos, float width, float height) {
    Rectangle source = { 0, 0, (float)image.width, (float)image.height };
    Rectangle dest   = { pos.x, pos.y, width, height };
    DrawTexturePro(image, source, dest, {0,0}, 0.0f, WHITE);
}

/*
   Загрузка набора кадров в один sprite
   Пример: coin00.png, coin01.png, coin02.png
*/
sprite load_sprite(
    const std::string &file_name_prefix,
    const std::string &file_name_suffix,
    size_t frame_count,
    bool loop,
    size_t frames_to_skip
) {
    assert(frame_count < 100);

    sprite result = {
        frame_count,       // frame_count
        frames_to_skip,    // frames_to_skip
        0,                 // frames_skipped
        0,                 // frame_index
        loop,              // loop
        0,                 // prev_game_frame
        new Texture2D[frame_count] // frames
    };

    for (size_t i = 0; i < frame_count; ++i) {
        // Формируем имя файла
        std::string file_name;
        if (frame_count < 10) {
            file_name = file_name_prefix + std::to_string(i) + file_name_suffix;
        } else {
            // Если кадров >=10, добавим ведущий 0 для i<10
            // coin00.png, coin01.png, ... coin09.png, coin10.png, ...
            if (i < 10) {
                file_name = file_name_prefix + "0" + std::to_string(i) + file_name_suffix;
            } else {
                file_name = file_name_prefix + std::to_string(i) + file_name_suffix;
            }
        }

        result.frames[i] = LoadTexture(file_name.c_str());
    }

    return result;
}

void unload_sprite(sprite &spr) {
    if (!spr.frames) return;

    for (size_t i = 0; i < spr.frame_count; ++i) {
        UnloadTexture(spr.frames[i]);
    }
    delete[] spr.frames;
    spr.frames = nullptr;
}

/*
   Рисуем текущий кадр спрайта
   и обновляем кадр, если прошло нужное кол-во пропущенных кадров
*/
void draw_sprite(sprite &spr, Vector2 pos, float width, float height) {
    // Рисуем спрайт
    draw_image(spr.frames[spr.frame_index], pos, width, height);

    // Если в этом кадре game_frame уже учтён, не обновляем
    if (spr.prev_game_frame == game_frame) return;

    // Считаем пропущенные кадры
    if (spr.frames_skipped < spr.frames_to_skip) {
        spr.frames_skipped++;
    } else {
        spr.frames_skipped = 0;
        spr.frame_index++;
        if (spr.frame_index >= spr.frame_count) {
            spr.frame_index = spr.loop ? 0 : spr.frame_count - 1;
        }
    }
    spr.prev_game_frame = game_frame;
}

void draw_sprite(sprite &spr, Vector2 pos, float size) {
    draw_sprite(spr, pos, size, size);
}

/* ------------------------
   3) Sounds
   ------------------------ */
void load_sounds() {
    InitAudioDevice();
    coin_sound = LoadSound("data/sounds/coin.wav");
    exit_sound = LoadSound("data/sounds/exit.wav");
}

void unload_sounds() {
    UnloadSound(coin_sound);
    UnloadSound(exit_sound);
    CloseAudioDevice();
}

#endif // ASSETS_H
