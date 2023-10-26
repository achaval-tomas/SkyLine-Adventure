#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <time.h>

#include "GameState.hpp"
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"
#include "Text.hpp"
#include "Constants.hpp"

int main(int argc, char* args[]){
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl; 

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_Init HAS FAILED. Error: " << SDL_GetError() << std::endl;

	if (TTF_Init() == -1)
		std::cout << "SDL_TTF HAS FAILED. Error: " << SDL_GetError() << std::endl;

	if (Mix_Init(0) == -1)
		std::cout << "SDL_Mixer HAS FAILED. Error: " << SDL_GetError() << std::endl;

	srand(time(0));
	RenderWindow window("SkyLine Adventure", SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_Renderer* renderer = window.getRenderer();

/*                      LOADING TEXTURES AND SOUND EFFECTS FOR THE GAME                           */

    SDL_Texture* logoTex                 = window.loadTexture("res/gfx/logoSkylineAdventure.png"  );
    SDL_Texture* menuBackgroundTex       = window.loadTexture("res/gfx/menuBackground.jpg"        );
	SDL_Texture* backgroundTex           = window.loadTexture("res/gfx/backgroundScene.png"       );
	SDL_Texture* backgroundNightTex      = window.loadTexture("res/gfx/backgroundScene2.png"      );
	SDL_Texture* backgroundSelTex        = window.loadTexture("res/gfx/backgroundSelection.png"   );
	SDL_Texture* gamemodeSelTex          = window.loadTexture("res/gfx/gameModeSelection.png"     );
	SDL_Texture* platformTex             = window.loadTexture("res/gfx/platform.png"              );
	SDL_Texture* platformNightTex        = window.loadTexture("res/gfx/platformNight.png"         );
	SDL_Texture* winningPlatformTex      = window.loadTexture("res/gfx/winningPlatform.png"       );
	SDL_Texture* winningPlatformNightTex = window.loadTexture("res/gfx/winningPlatformNight.png"  );
	SDL_Texture* winningFlagTex          = window.loadTexture("res/gfx/winningFlag.png"           );
	SDL_Texture* bulletTex               = window.loadTexture("res/gfx/bullet.png"                );
	SDL_Texture* superBulletTex          = window.loadTexture("res/gfx/superBullet.png"           );
	SDL_Texture* coinTex                 = window.loadTexture("res/gfx/coin.png"                  );
	SDL_Texture* coinCounterTex          = window.loadTexture("res/gfx/coinCounter.png"           );
	SDL_Texture* playerStandTex          = window.loadTexture("res/gfx/playerStraight.png"        );
	SDL_Texture* playerRightTex          = window.loadTexture("res/gfx/playerRight.png"           );
	SDL_Texture* playerLeftTex           = window.loadTexture("res/gfx/playerLeft.png"            );
    SDL_Texture* playerCrouchTex         = window.loadTexture("res/gfx/playerCrouch.png"          );
    SDL_Texture* playerCrouchLeftTex     = window.loadTexture("res/gfx/playerCrouchLeft.png"      );
    SDL_Texture* playerCrouchRightTex    = window.loadTexture("res/gfx/playerCrouchRight.png"     );
    SDL_Texture* youWonTex               = window.loadTexture("res/gfx/winnerScreen.png"          );
    SDL_Texture* gameOverTex             = window.loadTexture("res/gfx/gameOver.png"              );

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_Chunk* clickSound      = Mix_LoadWAV("res/sfx/clickSound.wav"    );
    Mix_Chunk* jumpSound       = Mix_LoadWAV("res/sfx/jumpSound.wav"     );
    Mix_Chunk* coinSound       = Mix_LoadWAV("res/sfx/coinSound.wav"     );
    Mix_Chunk* winSound        = Mix_LoadWAV("res/sfx/winningSound.wav"  );
    Mix_Chunk* newRecordSound  = Mix_LoadWAV("res/sfx/newRecordSound.wav");
    Mix_Chunk* bulletHitSound  = Mix_LoadWAV("res/sfx/bulletHitSound.wav");
    Mix_Chunk* crouchSound     = Mix_LoadWAV("res/sfx/crouchSound.wav"   );

    Mix_Music* backgroundMusicDay   = Mix_LoadMUS("res/sfx/backgroundMusicDay.wav");
    Mix_Music* backgroundMusicNight = Mix_LoadMUS("res/sfx/backgroundMusicNight.wav");
    Mix_Music* menuMusic            = Mix_LoadMUS("res/sfx/menuMusic.wav");

/*                    INITIALIZING ALL GAME ENTITIES (Textures with special properties)                            */

    Entity gameLogo(Vector2f(700, 400), logoTex);

    Entity menuBackground(ZERO_VECT, menuBackgroundTex);
    Entity backgroundDay(ZERO_VECT, backgroundTex);
    Entity backgroundNight(ZERO_VECT, backgroundNightTex);
    Entity backgroundSelection(ZERO_VECT, backgroundSelTex);
    Entity gamemodeSelection(ZERO_VECT, gamemodeSelTex);
    Entity background = backgroundDay;

    Entity gameOver(Vector2f(395, 100), gameOverTex);
    Entity youWon(Vector2f(395, 100), youWonTex);
    Entity coinCounter(Vector2f(1115, 15), coinCounterTex);

	// "std::vector" is like a dynamic array. We're setting the platforms of the game.
	std::vector<Entity> platformsDay = {Entity(WINNING_PLATFORM_DAY_POS           , winningPlatformTex),
									 	Entity(Vector2f(0   , GROUND_HEIGHT      ), platformTex       ), 
						   			 	Entity(Vector2f(250 , GROUND_HEIGHT      ), platformTex       ),
						   			 	Entity(Vector2f(500 , GROUND_HEIGHT      ), platformTex       ),
						   			 	Entity(Vector2f(750 , GROUND_HEIGHT      ), platformTex       ),
						   			 	Entity(Vector2f(1000, GROUND_HEIGHT      ), platformTex       ),
						   			 	Entity(Vector2f(1250, GROUND_HEIGHT      ), platformTex       ),
						   			 	Entity(Vector2f(630 , GROUND_HEIGHT -  50), platformTex       ),
						   			 	Entity(Vector2f(300 , GROUND_HEIGHT -  90), platformTex       ),
						   			 	Entity(Vector2f(380 , GROUND_HEIGHT - 180), platformTex       ),
						   			 	Entity(Vector2f(640 , GROUND_HEIGHT - 270), platformTex       ),
						   			 	Entity(Vector2f(320 , GROUND_HEIGHT - 350), platformTex       ) };

	std::vector<Entity> platformsNight = {Entity(WINNING_PLATFORM_NIGHT_POS         , winningPlatformNightTex),
									 	  Entity(Vector2f(0   , GROUND_HEIGHT      ), platformNightTex       ), 
						   			      Entity(Vector2f(250 , GROUND_HEIGHT      ), platformNightTex       ),
						   			 	  Entity(Vector2f(500 , GROUND_HEIGHT      ), platformNightTex       ),
						   			 	  Entity(Vector2f(750 , GROUND_HEIGHT      ), platformNightTex       ),
						   			 	  Entity(Vector2f(1000, GROUND_HEIGHT      ), platformNightTex       ),
						   			 	  Entity(Vector2f(1250, GROUND_HEIGHT      ), platformNightTex       ),
						   			 	  Entity(Vector2f(330 , GROUND_HEIGHT -  90), platformNightTex       ),
						   			 	  Entity(Vector2f(0   , GROUND_HEIGHT - 160), platformNightTex       ),
						   			 	  Entity(Vector2f(650 , GROUND_HEIGHT - 170), platformNightTex       ),
						   			 	  Entity(Vector2f(310 , GROUND_HEIGHT - 280), platformNightTex       ),
						   			 	  Entity(Vector2f(640 , GROUND_HEIGHT - 380), platformNightTex       ),
						   			 	  Entity(Vector2f(1030, GROUND_HEIGHT - 240), platformNightTex       ),
						   			 	  Entity(Vector2f(10  , GROUND_HEIGHT - 400), platformNightTex       ) };

	std::vector<Entity> platforms = platformsDay;
	Entity* winningPlatform = &platforms[0];
	int winningPlatformPosX = WINNING_PLATFORM_X_DAY;
    Entity winningFlag(WINNING_FLAG_POS);
  
  	// Initializing player and first bullets.
	Player player(PLAYER_START_POS,  playerStandTex);
	MovingEntity bullet1(BULLET_LEFT_GEN,  bulletTex);
	MovingEntity bullet2(BULLET_LEFT_GEN,  bulletTex);
	MovingEntity bullet3(BULLET_LEFT_GEN,  bulletTex);
	MovingEntity bullet4(BULLET_LEFT_GEN,  bulletTex);
	MovingEntity bullet5(BULLET_LEFT_GEN,  bulletTex);
	MovingEntity bullet6(BULLET_LEFT_GEN,  bulletTex);

	std::vector<MovingEntity*> movingEntities = {&player, &bullet1, &bullet2};
	std::vector<MovingEntity*> comingBullets  = {&bullet1, &bullet2};

	std::vector<MovingEntity*> easyEntities = movingEntities;
	std::vector<MovingEntity*> easyBullets  = comingBullets;

	std::vector<MovingEntity*> mediumEntities = {&player, &bullet1, &bullet2, &bullet3, &bullet4};
	std::vector<MovingEntity*> mediumBullets  =  {&bullet1, &bullet2, &bullet3, &bullet4};

	std::vector<MovingEntity*> impossibleEntities = {&player, &bullet1, &bullet2, &bullet3, &bullet4, &bullet5, &bullet6};
	std::vector<MovingEntity*> impossibleBullets  = {&bullet1, &bullet2, &bullet3, &bullet4, &bullet5, &bullet6};

	std::vector<Entity> coins = {};						    
	int max_coins = coins.size();


/*                CREATING THE TEXTURES FOR THE GENREAL WRITTEN INFORMATION                   */

	Text start 		 (renderer, ROUND_FONT, 75, START_TEXT   , DARK_BLUE);
	Text info1 		 (renderer, ROUND_FONT, 60, GAME_INFO1   , SUPERDARK_GREEN);
	Text info2 		 (renderer, ROUND_FONT, 60, GAME_INFO2   , SUPERDARK_GREEN);
	Text seeControls (renderer, ROUND_FONT, 45, CONTROLS_INFO, GOLD);

	Text restartInfo (renderer, ROUND_FONT, 35, RESTART_TEXT , YELLOW);
	Text newRecord   (renderer, ROUND_FONT, 35, NEW_BEST_TIME, DARK_GREEN);


/*                              INITIALIZING ALL THE GAME VARIABLES                         */

	GameState game = GameState();

	SDL_Event event;

	// INITIALIZE ALL NUMERIC VARIABLES
	const float timeStep = 0.033f;
	float accumulator    = 0.0f;
	float currentTime    = utils::hireTimeInSeconds();
	float gameTime       = 0.0f;
	float newTime        = currentTime;
	float frameTime      = newTime - currentTime;
	float startTime      = currentTime;

	float lastJumpTime   = std::numeric_limits<float>::min();
	float lastCrouchTime = std::numeric_limits<float>::min();
	float lastResetTime  = std::numeric_limits<float>::min();

	float highScore      = HIGH_SCORE_STARTER;

	float offsetLogo     = 0.0f;
	float offsetPlat     = 0.0f;
	float offsetCoin     = 0.0f;
	float platPosDiff    = 0.0f;

	unsigned int coinIndex   = max_coins + 1u;
	int coinsCollected       = 0;

	// INITIALIZE STRINGS
	std::string maxCoinsStr  = std::to_string(max_coins);
	std::string timeDiffStr  = std::to_string(0.0f);
	std::string gameTimeStr  = std::to_string(gameTime);
	std::string highScoreStr = std::to_string(highScore);

	// INITIALIZE NOT FREQUENTLY UPDATED TEXT
	Text timeToBeat(TIME_TO_BEAT_PARAMS);
	Text coinsInfo(COINS_INFO_PARAMS);

	// INITIALIZE TIMER COLOR
	SDL_Color timerColor = BLACK;

	// INITIALIZE KEYBOARD INPUTS ARRAY
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);

	// SET UP MUSIC VOLUME
	Mix_VolumeMusic(30);

/*                              GAME LOOP STARTS                                     */
	while (game.LoopStarted()){

		newTime      = utils::hireTimeInSeconds();
		frameTime    = newTime - currentTime;
		currentTime  = newTime;
		accumulator += frameTime;

        /*                    ONLY PROCESS INFORMATION WHEN ENOUGH TIME HAS PASSED                       */
		if (accumulator >= timeStep){
		accumulator = 0.0f; 

			if (SDL_PollEvent(&event) && (event.type == SDL_QUIT)){
				game.Quit();
			}

			if (game.BeingPlayed()){
				/*                             UPDATE GAMETIME                                   */
				gameTime = utils::hireTimeInSeconds() - startTime;

				/*                           SET UP GAME IF NEEDED                               */
				if (game.NeedsSetUp()){

					// GAME STATS SET UP
					startTime = utils::hireTimeInSeconds();
					highScoreStr = std::to_string(highScore);
					highScoreStr.resize(5);
					timeToBeat.destroyText();
					timeToBeat = Text(TIME_TO_BEAT_PARAMS);

					// COIN-RELATED SET UP
					coinsCollected = 0;
					coins.clear();
					for (Entity& plat : platforms){
						if (plat.getPos().y < GROUND_HEIGHT){
							Entity coin(Vector2f(10 + plat.getPos().x + rand() % 230 , plat.getPos().y -  20),  coinTex);		
							coins.push_back(coin);
							coin.setPos(Vector2f(10 + plat.getPos().x + rand() % 230 , plat.getPos().y -  20));
							coins.push_back(coin);
						}
					}
					max_coins = coins.size();
					maxCoinsStr  = std::to_string(max_coins);
					coinsInfo.destroyText();
					coinsInfo = Text(COINS_INFO_PARAMS);

					// PLAYER SET UP
					player.setPos(PLAYER_START_POS);
					player.setTex(&player, playerStandTex);
					player.setCrouch(false);
					player.setSpeed(ZERO_VECT);

					// BULLETS SET UP
			   	 	for(MovingEntity* bul : comingBullets){
						bul->setPos(BULLET_LEFT_GEN);
						bul->setSpeed(BULLET_LEFT_SPEED);
						bul->setTex(bul, bulletTex);
					}

					game.SetUpDone();
				}

				/*                         OFFSET MOVING PLATFORMS AND OBJECTS                            */
				offsetPlat = 50*sin(gameTime);
				winningPlatform->setPos(WINNING_PLATFORM_SET_OFFSET_POS);
				winningFlag.setPos(WINNING_FLAG_COORDS);

				/*                       HANDLE MOVING PLATFORM PUSHING PLAYER                             */
				if (player.getPos().y < WINNING_PLATFORM_Y + WINNING_PLATFORM_HEIGHT){
					platPosDiff -= winningPlatform->getPos().x;
					player.adjustToMovement(&player, winningPlatform, platPosDiff);
				}

				/*                              HANDLE PLAYER CONTROLS                                     */
				if (PRESSED_CROUCH){
					player.pCrouch(&player, platforms, playerCrouchTex, playerStandTex);
					Mix_PlayChannel(-1, crouchSound, 0);
					lastCrouchTime = currentTime;
				} else if(PRESSED_JUMP){
					if (!player.getCrouch()){
						player.setSpeed(Vector2f(player.getSpeed().x, player.getSpeed().y - 13));
					} else {
						player.setSpeed(Vector2f(player.getSpeed().x, player.getSpeed().y - 8));
					}
					lastJumpTime = currentTime;
					Mix_PlayChannel(-1, jumpSound, 0);
				} else if(PRESSED_DOWN){
					player.moveDown(&player, platforms);
				}

				if (PRESSED_LEFT){
					player.moveLeft(&player, platforms);
					if(!player.getCrouch()){
					  	player.setTex(&player, playerLeftTex);
			   		} else {
			    		player.setTex(&player, playerCrouchLeftTex); 
					}
				}

				if (PRESSED_RIGHT){
					player.moveRight(&player, platforms);
					if(!player.getCrouch()){
					    player.setTex(&player, playerRightTex);
					} else {
					    player.setTex(&player, playerCrouchRightTex);
					}
				}


		        /*                                HANDLING ALL MOVING ENTITIES                                */
				for(MovingEntity* ent : movingEntities){
					if (ent->getSpeed().x > 0.0f){
						ent->moveRight(ent, platforms);
						ent->setSpeed(Vector2f(ent->getSpeed().x - 1, ent->getSpeed().y));
					} else if (ent->getSpeed().x < 0.0f){
						ent->moveLeft(ent, platforms);
						ent->setSpeed(Vector2f(ent->getSpeed().x + 1, ent->getSpeed().y));
					}
					if (ent->getSpeed().y > 0.0f){
						ent->moveDown(ent, platforms);
						ent->setSpeed(Vector2f(ent->getSpeed().x, ent->getSpeed().y - 1));
					} else if (ent->getSpeed().y < 0.0f){
						ent->moveUp(ent, platforms);
						ent->setSpeed(Vector2f(ent->getSpeed().x, ent->getSpeed().y + 1));
					}
				}

				if (player.getSpeed().y == 0.0f){
					player.moveDown(&player, platforms);   // Player is constantly and inevitably falling down like "Gravity".
				}

			    /*                                 HANDLE BULLET REGENERATION                                  */
				for(MovingEntity* bul : comingBullets){
					if (bul->getCollision()){
						if (BULLET_LOW_INTERVAL){
							if (bul->getTex() != bulletTex)
								bul->setTex(bul, bulletTex);

							bul->setPos(BULLET_LEFT_GEN);
							bul->setSpeed(BULLET_LEFT_SPEED);
						} else {
							if (bul->getTex() != superBulletTex) 
								bul->setTex(bul, superBulletTex);

	        	        	bul->setPos(BULLET_RIGHT_GEN);
							bul->setSpeed(BULLET_RIGHT_SPEED);
						}
				    }
				}

				/*                                    HANDLING COIN COLLECTION                                 */
				coinIndex = player.collectedCoin(&player, coins);
				if (coinIndex < coins.size()){
					Mix_PlayChannel(-1, coinSound, 0);
					coins.erase(coins.begin() + coinIndex);
					coins.shrink_to_fit();
					coinsCollected += 1;

					coinsInfo.destroyText();
					coinsInfo = Text(COINS_INFO_PARAMS);
				}

				/*                             RENDER AND DISPLAY EVERYTHING ON SCREEN                         */
				window.clear();
				window.render(background);

				for(Entity& plat : platforms){
					window.render(plat);
				}

				for(Entity& coin : coins){             // RENDER ALL COINS WITH WAVING OFFSET
					offsetCoin = 1.5*sin(gameTime*10);
					coin.setPos(Vector2f(coin.getPos().x, coin.getPos().y + offsetCoin));
					window.render(coin);
					coin.setPos(Vector2f(coin.getPos().x, coin.getPos().y - offsetCoin));
				}

				for(MovingEntity* ent : movingEntities){
					window.render(*ent);
				}

				window.render(coinCounter);
				window.render(winningFlag);

				gameTimeStr = std::to_string(gameTime);
				gameTimeStr = gameTimeStr.substr(0, gameTimeStr.find(".") + 4);
				Text timer(TIMER_TEXT_PARAMS);

				timeToBeat.displayText( 15, 670, renderer);
				coinsInfo.displayText(1170,  12, renderer);
				timer.displayText(560, 5, renderer);
				
				timer.destroyText();
			
				window.display();

			   /*                                 HANDLING GAME OVER AND GAME WINNING                         */
				if (PLAYER_LOST_THE_GAME){
					window.clear();
					window.render(background);
					window.render(gameOver);

					Mix_PlayChannel(-1, bulletHitSound, 0);

					restartInfo.displayText(440, 630, renderer);
					window.display();

					game.EndRound();
				} else if (PLAYER_WON_THE_GAME){

					window.render(youWon);

					timeDiffStr = std::to_string(gameTime-highScore);
					timeDiffStr = timeDiffStr.substr(0, timeDiffStr.find(".") + 4);

					if (gameTime <= highScore){
						Mix_PlayChannel(-1, newRecordSound, 0);
						newRecord.displayText(15, 5, renderer);

						Text improvement(TIME_DIFF_NEG_PARAMS);
						improvement.displayText(325, 670, renderer);
						improvement.destroyText();

						highScore = gameTime;
					} else {
						Mix_PlayChannel(-1, winSound, 0);
						Text improvement(TIME_DIFF_POS_PARAMS);
						improvement.displayText(325, 670, renderer);
						improvement.destroyText();
					}

					restartInfo.displayText(440, 620, renderer);
					window.display();

					timeToBeat.destroyText();

					game.EndRound();
				}

				// Winning platform re-set Offset.
				platPosDiff = winningPlatform->getPos().x;
			    winningPlatform->setPos(WINNING_PLATFORM_RESET_OFFSET_POS);

			} else if (game.AtMainMenu()){

				if (!Mix_PlayingMusic())
					Mix_FadeInMusic(menuMusic, -1, 1500);

				window.clear();
				window.render(menuBackground);

				offsetLogo = sin(newTime)*50;
				gameLogo.setPos(Vector2f(gameLogo.getPos().x, gameLogo.getPos().y + offsetLogo));
				window.render(gameLogo);
				gameLogo.setPos(Vector2f(gameLogo.getPos().x, gameLogo.getPos().y - offsetLogo));

				start.displayText(15, 20, renderer);
				info1.displayText(15, 140, renderer);
				info2.displayText(15, 200, renderer);
				seeControls.displayText(15, 300, renderer);

				window.display();

				if (PRESSED_START){
					game.ChooseMap();
				}

				if (PRESSED_CONTROLS){
					game.ShowControls();
				}


			} else if (game.CheckingControls()){
				window.clear();
				window.render(menuBackground);

				Text escape      (renderer, ROUND_FONT, 45, ESCAPE_INFO  , DARK_BLUE);
				Text jump        (renderer, ROUND_FONT, 45, JUMP_INFO    , DARK_BLUE);
				Text down        (renderer, ROUND_FONT, 45, DOWN_INFO    , DARK_BLUE);
				Text left        (renderer, ROUND_FONT, 45, LEFT_INFO    , DARK_BLUE);
				Text right       (renderer, ROUND_FONT, 45, RIGHT_INFO   , DARK_BLUE);
				Text crouch      (renderer, ROUND_FONT, 45, CROUCH_INFO  , DARK_BLUE);
				Text restart     (renderer, ROUND_FONT, 45, RESTART_INFO , DARK_BLUE);

				escape.displayText(230,  30, renderer);
				jump.displayText(230, 100, renderer);
				left.displayText(230, 170, renderer);
				down.displayText(230, 240, renderer);
				right.displayText(230, 310, renderer);
				crouch.displayText(230, 380, renderer);
				restart.displayText(230, 450, renderer);

				escape.destroyText();
				jump.destroyText();
				down.destroyText();
				left.destroyText();
				right.destroyText();
				crouch.destroyText();
				restart.destroyText(); 

				window.display();

				game.Wait();

			} else if (game.ChoosingMap()){

				if (!game.IsWaiting()){
					window.clear();
					window.render(backgroundSelection);

					Text backgroundSelText(BACKGROUND_SEL_PARAMS);
					Text dayCityText(DAY_CITY_PARAMS);
					Text nightCityText(NIGHT_CITY_PARAMS);

					backgroundSelText.displayText(343, 40, renderer);
					dayCityText.displayText(800, 350, renderer);
					nightCityText.displayText(120, 350, renderer);

					nightCityText.destroyText();
					dayCityText.destroyText();
					backgroundSelText.destroyText();

					window.display();

					game.Wait();
				}

				if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT){
					Mix_HaltMusic();
					Mix_PlayChannel(-1, clickSound, 0);

					if (event.motion.x < 640){
						Mix_FadeInMusic(backgroundMusicNight, -1, 1000);
						timerColor   = CYAN;
						background   = backgroundNight;
						platforms    = platformsNight;
						winningPlatform = &platforms[0];
						winningPlatformPosX = WINNING_PLATFORM_X_NIGHT;
					} else {
						Mix_FadeInMusic(backgroundMusicDay, -1, 1000);
						timerColor = BLACK;
						background = backgroundDay;
						platforms = platformsDay;
						winningPlatform = &platforms[0];
						winningPlatformPosX = WINNING_PLATFORM_X_DAY;
					}

					game.ChooseGamemode();
				}

			} else if (game.ChoosingGamemode()){
				if (!game.IsWaiting()){
					window.clear();
					window.render(background);
					window.render(gamemodeSelection);
					window.display();
					game.Wait();
				}

				if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT){
					Mix_PlayChannel(-1, clickSound, 0);

					if (event.motion.x < 427){
						comingBullets = easyBullets;
						movingEntities = easyEntities;
					} else if (event.motion.x > 854){
						comingBullets = impossibleBullets;
						movingEntities = impossibleEntities;
					} else {
						comingBullets = mediumBullets;
						movingEntities = mediumEntities;
					}

					game.StartPlaying();
				}


			}
			/*                                 HANDLE KEYBOARD INPUTS                                        */

			if(PRESSED_RESTART){
				Mix_HaltChannel(-1);
				lastResetTime = currentTime;

				game.Restart();
			}

			if(PRESSED_ESCAPE){
				lastResetTime = currentTime;

				Mix_FadeOutMusic(1000);
				Mix_HaltChannel(-1);

				timeToBeat.destroyText();
				coinsInfo.destroyText();
				highScore = HIGH_SCORE_STARTER;

				game.Leave();
			}
		}
	}

	window.cleanUp(); // DELETE EVERYTHING ON SCREEN

	Mix_HaltMusic();
	Mix_HaltChannel(-1);   // STOP ALL PLAYING MUSIC & SOUND EFFECTS

	// FREE ALL MEMORY   TO-DO
	coins.clear();
	platforms.clear();
	movingEntities.clear();
	comingBullets.clear();

	start.destroyText();
	info1.destroyText();
	info2.destroyText();
	restartInfo.destroyText();
	newRecord.destroyText();
	seeControls.destroyText();    

	Mix_Quit();
	TTF_Quit();     // QUIT ALL PROCESSES
	SDL_Quit(); 

	return 0;
}