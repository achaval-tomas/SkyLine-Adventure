#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Math.hpp"
#include "Constants.hpp"
#include <vector>

class Entity {
public:
	Entity(Vector2f p_pos, SDL_Texture* p_tex);

	inline Vector2f& getPos() {return pos;}
	inline void setPos(Vector2f p_pos){ pos = p_pos; }

	SDL_Texture* getTex();
	void setTex(Entity* p_player, SDL_Texture* p_tex);

	SDL_Rect getCurrentFrame();

private:
	Vector2f pos;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};



class MovingEntity : public Entity 
{
public:
	MovingEntity(Vector2f p_pos, SDL_Texture* p_tex);

	inline void setSpeed(Vector2f p_speed){ speed = p_speed; }
	inline Vector2f& getSpeed() {return speed;}

	inline void setCollision(bool p_coll){ isColliding = p_coll; }
	inline bool getCollision(){ return isColliding; }
 
	/*                                        ENTITY MOVEMENT HANDLERS                                   */
	void moveUp(MovingEntity* p_player, std::vector<Entity> p_platforms);
	void moveDown(MovingEntity* p_player, std::vector<Entity> p_platforms);	
	void moveRight(MovingEntity* p_player, std::vector<Entity> p_platforms);
	void moveLeft(MovingEntity* p_player, std::vector<Entity> p_platforms);

    /*                                   COLLISION BETWEEN ENTITIES & BULLETS                             */
	bool checkCollision(MovingEntity* p_player, std::vector<Entity> p_platforms);

private:
	Vector2f speed;
	bool isColliding;
};


class Player : public MovingEntity
{
public:
	Player(Vector2f p_pos, SDL_Texture* p_tex);

	inline void setCrouch(bool c){ isCrouching = c; }
	inline bool getCrouch(){ return isCrouching; }
	void pCrouch(Player* p_player, std::vector<Entity> p_platforms, SDL_Texture* p_crouchTex, SDL_Texture* p_standTex);

	/*                                          PLAYER INFORMATION METHODS                                      */
	bool canJumpNow(Player* p_player, std::vector<Entity> p_platforms);
	bool hitByBullet(Player* p_player, std::vector<MovingEntity*> p_bullets);
	bool onWinningPlat(Player* p_player, Entity* p_winningPlatform);
	unsigned int collectedCoin(Player* p_player, std::vector<Entity> p_coins);

	/*                                       EXTERNAL FACTORS AFFECTING PLAYER                                   */
	void adjustToMovement(Player* p_player, Entity* p_winningPlatform, float p_platPosDiff);

private:
	bool isCrouching;
};