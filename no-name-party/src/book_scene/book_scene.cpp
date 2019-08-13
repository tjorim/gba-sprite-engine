//
// Created by tiele on 9/08/2019.
//

#include <libgba-sprite-engine/background/text_stream.h>

#include "book_scene.h"
#include "../game_scene/game_scene.h"

#include "background/background_books.h"
#include "foreground/sprites/shared_book_scene.h"

#include "foreground/sprites/book_blue.h"
#include "foreground/sprites/book_green.h"
#include "foreground/sprites/book_red.h"
#include "foreground/sprites/book_yellow.h"

BookScene::BookScene(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Background *> BookScene::backgrounds() {
    return {
            background_books.get()
    };
}

std::vector<Sprite *> BookScene::sprites() {
    std::vector<Sprite *> sprites;

    for (auto &book : books) {
        sprites.push_back(book.get());
    }

    TextStream::instance().setText(std::string("Sprites ") + std::to_string(sprites.size()), 1, 0);

    return sprites;
}

void BookScene::load() {
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(
            new BackgroundPaletteManager(background_booksPal, sizeof(background_booksPal)));
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(
            new ForegroundPaletteManager(shared_book_scenePal, sizeof(shared_book_scenePal)));

    background_books = std::unique_ptr<Background>(
            new Background(1, background_booksTiles, sizeof(background_booksTiles),
                    background_booksMap, sizeof(background_booksMap)));
    background_books->useMapScreenBlock(16);
}

void BookScene::tick(u16 keys) {

}
