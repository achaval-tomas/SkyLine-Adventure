#pragma once

// SCREEN INFORMATION
#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720

// BASE PLATFORMS HEIGHT
#define GROUND_HEIGHT 520

// MAXIMUM NUMBER OF COINS
#define MAX_COINS     max_coins

// PLAYER INFORMATION
#define PLAYER_WIDTH          64
#define PLAYER_HEIGHT         64
#define PLAYER_CROUCH_HEIGHT  48
#define PLAYER_CROUCH_WIDTH   64
#define PLAYER_START_POS      Vector2f(1000, GROUND_HEIGHT-PLAYER_HEIGHT-15)
#define PLAYER_WON_THE_GAME   coinsCollected == max_coins && player.onWinningPlat(&player, winningPlatform) && !game.IsWaiting()
#define PLAYER_LOST_THE_GAME  player.hitByBullet(&player, comingBullets) && !game.IsWaiting()

// LONG PARAMS FOR TEXT FUNCS
#define COINS_INFO_PARAMS     renderer, ROUND_FONT, 35, std::to_string(coinsCollected)  + "/" + maxCoinsStr, BROWN
#define TIMER_TEXT_PARAMS     renderer, ROUND_FONT, 35, gameTimeStr                     + "s", timerColor
#define TIME_TO_BEAT_PARAMS   renderer, ROUND_FONT, 35, "Time to beat: " + highScoreStr + "s", YELLOW
#define TIME_DIFF_POS_PARAMS  renderer, ROUND_FONT, 35, "+" + timeDiffStr               + "s", RED
#define TIME_DIFF_NEG_PARAMS  renderer, ROUND_FONT, 35, timeDiffStr                     + "s", DARK_GREEN
#define BACKGROUND_SEL_PARAMS renderer, ROUND_FONT, 50, "Click to select your city."         , WHITE
#define DAY_CITY_PARAMS       renderer, ROUND_FONT, 50, "Radiant District"                   , BLACK
#define NIGHT_CITY_PARAMS     renderer, ROUND_FONT, 50, "Nebula Metropolis"                  , CYAN

// USEFUL VECTORS
#define ZERO_VECT Vector2f()

// WINNING PLATFORM ORIGIN POSITION AND OFFSET
#define WINNING_PLATFORM_WIDTH             200
#define WINNING_PLATFORM_HEIGHT            30
#define WINNING_PLATFORM_Y                 120
#define WINNING_PLATFORM_Y_DAY             WINNING_PLATFORM_Y
#define WINNING_PLATFORM_X_DAY             60
#define WINNING_PLATFORM_Y_NIGHT           WINNING_PLATFORM_Y
#define WINNING_PLATFORM_X_NIGHT           950
#define WINNING_PLATFORM_DAY_POS 	       Vector2f(WINNING_PLATFORM_X_DAY, WINNING_PLATFORM_Y_DAY)
#define WINNING_PLATFORM_NIGHT_POS 		   Vector2f(WINNING_PLATFORM_X_NIGHT, WINNING_PLATFORM_Y_NIGHT)
#define WINNING_PLATFORM_SET_OFFSET_POS    Vector2f(winningPlatformPosX + offsetPlat, WINNING_PLATFORM_Y)
#define WINNING_PLATFORM_RESET_OFFSET_POS  Vector2f(winningPlatformPosX - offsetPlat, WINNING_PLATFORM_Y)

// FINISH FLAG POS
#define WINNING_FLAG_COORDS  Vector2f(winningPlatform->getPos().x + 15, WINNING_PLATFORM_Y - 40)
#define WINNING_FLAG_POS     WINNING_FLAG_COORDS, winningFlagTex
#define WINNING_COIN_COORDS  Vector2f(winningPlatform->getPos().x + 100, WINNING_PLATFORM_Y - 20)
#define WINNING_COIN_POS     WINNING_COIN_COORDS, coinTex

// USEFUL CONSTANTS
#define STEP 1
#define HIGH_SCORE_STARTER 120.0f

// COLOR CONSTANTS
#define DARK_BLUE        {  8,  30,  51, 255}
#define GOLD             {209,  94,  17, 255}
#define CYAN             { 97, 255, 218, 255}
#define RED              {255,   0,   0, 255}
#define YELLOW           {252, 247,  83, 255}
#define BLACK            {  0,   0,   0,   0}
#define WHITE            {255, 255, 255, 255}
#define DARK_GREEN       { 15, 161,   5,   0}
#define SUPERDARK_GREEN  { 37,  82,  49, 255}
#define BROWN            {122,  83,  27, 255}

// BULLET INFORMATION
#define BULLET_LEFT_GEN       Vector2f( -30, 50 + rand() % (GROUND_HEIGHT-80))
#define BULLET_RIGHT_GEN      Vector2f(1250, 50 + rand() % (GROUND_HEIGHT-80))
#define BULLET_SPEED          500
#define BULLET_LEFT_SPEED     Vector2f( BULLET_SPEED, 0)
#define BULLET_RIGHT_SPEED    Vector2f(-BULLET_SPEED, 0)
#define BULLET_MOD            4
#define BULLET_INTERVAL       2
#define BULLET_LOW_INTERVAL   (int)gameTime % BULLET_MOD < BULLET_INTERVAL
#define BULLET_HIGH_INTERVAL  (int)gameTime % BULLET_MOD >= BULLET_INTERVAL

// FONT PATHS
#define ROUND_FONT      "res/fonts/roundedFont.ttf"
/*
#define BEBAS_FONT      "res/fonts/BebasNeue-Regular.ttf"
#define PIXEL_FONT      "res/fonts/pixelFont.ttf"
*/

// USEFUL STRINGS
#define START_TEXT      "Press SPACE to start the game!"
#define RESTART_TEXT    "Press 'R' or 'SPACE' to Restart."
#define NEW_BEST_TIME   "New Best Time!"
#define GAME_INFO1      "Collect all the coins and get on top of"
#define GAME_INFO2      "the Green Platform as fast as you can!"

// ACTION REFRESH TIMES
#define JUMP_REFRESH    (currentTime - lastJumpTime)   > 0.1f
#define CROUCH_REFRESH  (currentTime - lastCrouchTime) > 0.2f
#define RESTART_REFRESH (currentTime - lastResetTime)  > 1.0f

// CONTROLS KEYBINDS
#define PRESSED_START     keyboard[SDL_SCANCODE_SPACE]  && game.AtMainMenu()
#define PRESSED_CONTROLS  keyboard[SDL_SCANCODE_K]      && game.AtMainMenu()
#define PRESSED_JUMP     (keyboard[SDL_SCANCODE_W]      || keyboard[SDL_SCANCODE_UP]    ) && JUMP_REFRESH && player.canJumpNow(&player, platforms)
#define PRESSED_DOWN     (keyboard[SDL_SCANCODE_S]      || keyboard[SDL_SCANCODE_DOWN]  )
#define PRESSED_LEFT     (keyboard[SDL_SCANCODE_A]      || keyboard[SDL_SCANCODE_LEFT]  )
#define PRESSED_RIGHT    (keyboard[SDL_SCANCODE_D]      || keyboard[SDL_SCANCODE_RIGHT] )
#define PRESSED_CROUCH   (keyboard[SDL_SCANCODE_LCTRL]  || keyboard[SDL_SCANCODE_RCTRL] ) && CROUCH_REFRESH
#define PRESSED_ESCAPE   (keyboard[SDL_SCANCODE_P]      || keyboard[SDL_SCANCODE_ESCAPE]) && RESTART_REFRESH && !game.AtMainMenu() 
#define PRESSED_RESTART  (keyboard[SDL_SCANCODE_R]      || keyboard[SDL_SCANCODE_SPACE] ) && RESTART_REFRESH && !game.NeedsSetUp()


// CONTROLS INFO (unused)

#define CONTROLS_INFO "Press 'K' to check the keybinds."
#define ESCAPE_INFO   "Press 'ESC' or 'P' to go to main menu."
#define JUMP_INFO     "Press 'W' or 'up arrow' to Jump."
#define LEFT_INFO     "Press 'A' or 'left arrow' to move Left."
#define DOWN_INFO     "Press 'S' or 'down arrow' to fall faster."
#define RIGHT_INFO    "Press 'D' or 'right arrow' to move Right."
#define CROUCH_INFO   "Press 'CTRL' to crouch or stand up."
#define RESTART_INFO   RESTART_TEXT


