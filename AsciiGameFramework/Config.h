#pragma once
#include <vector>
#include <string>

using string = std::string;

#define DEBUG_MODE 0

static const unsigned int WORLD_SIZE_X_GAME = 90;
static const unsigned int WORLD_SIZE_Y_GAME = 24;
static const unsigned int SCREEN_PADDING = 4;
const std::vector<string> GAME_BACKGROUND_FILES = { "background1.txt", "background2.txt" };

static const unsigned int WORLD_SIZE_X_TEST_ROOM = 120;
static const unsigned int WORLD_SIZE_Y_TEST_ROOM = 30;

// todo dedurre model width ed height dal model
// todo permettere di settare le dimensioni della porta direttamente