//
// Created by Wouter Groeneveld on 27/07/18.
//

#ifdef CODE_COMPILED_AS_PART_OF_TEST
#include <engine/gba/tonc_core_stub.h>
#else
#include <engine/gba/tonc_core.h>
#endif
#include <engine/background/text_stream.h>
#include "palette_manager.h"

int getBits(int number, int k, int p) {
    return (((1 << k) - 1) & (number >> p));
}

void PaletteManager::persist() {
    dma3_cpy(this->paletteAddress(), this->data, this->size);
}

COLOR PaletteManager::change(int bank, int index, COLOR newColor) {
    auto palBank = this->paletteBank();
    COLOR oldColor = palBank[bank][index];
    palBank[bank][index] = newColor;
    return oldColor;
}

COLOR PaletteManager::color(u32 red, u32 green, u32 blue) {
    if(red > 31) red = 31;
    if(green > 31) green = 31;
    if(blue > 31) blue = 31;
    return red | (green<<5) | (blue<<10);
}

u32 PaletteManager::red(COLOR r) {
    return getBits(r, 5, 0);
}

u32 PaletteManager::green(COLOR r) {
    return getBits(r, 5, 5);
}

u32 PaletteManager::blue(COLOR r) {
    return getBits(r, 5, 10);
}

void PaletteManager::increaseBrightness(u32 intensity) {
    if(intensity > 31) {
        failure(Brightness_Intensity_Too_High);
        return;
    }

    auto palBank = this->paletteBank();
    for(int bank = 0; bank < PALETTE_BANK_SIZE; bank++) {
        for(int index = 0; index < PALETTE_BANK_SIZE; index++) {
            auto current = palBank[bank][index];
            auto next = PaletteManager::color(PaletteManager::red(current) + intensity,
                    PaletteManager::green(current) + intensity, PaletteManager::blue(current) + intensity);

            change(bank, index, next);
        }
    }
}

void PaletteManager::persistToBank(int bank) {
    auto palBank = this->paletteBank();
    dma3_cpy(palBank[bank], this->data, PALETTE_BANK_SIZE);
}