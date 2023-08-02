#include "Entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

/*-------------------------------------------- GENERAL ENTITIES CLASS --------------------------------------------*/
Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex)
:pos(p_pos), tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	SDL_QueryTexture(p_tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
}

SDL_Texture* Entity::getTex(){
	return tex;
}

void Entity::setTex(Entity* p_ent, SDL_Texture* p_tex){
	int oldHeight, newHeight;
	SDL_QueryTexture(p_ent->getTex(), NULL, NULL, NULL, &oldHeight);
	tex = p_tex;
    SDL_QueryTexture(p_ent->getTex(), NULL, NULL, NULL, &newHeight);
    
    p_ent->setPos(Vector2f(p_ent->getPos().x, p_ent->getPos().y + (oldHeight - newHeight)));
	SDL_QueryTexture(p_tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
}

SDL_Rect Entity::getCurrentFrame(){
	return currentFrame;
}



/*--------------------------------------------- MOVING ENTITIES CLASS ---------------------------------------------*/
MovingEntity::MovingEntity(Vector2f p_pos, SDL_Texture* p_tex)
:Entity(p_pos, p_tex) 
{
	speed = ZERO_VECT;
	isColliding = false;
}

/*                                                MOVEMENT HANDLERS                                                */
void MovingEntity::moveUp(MovingEntity* p_ent, std::vector<Entity> p_platforms)
{
	for (unsigned int i = 0u; i<10; ++i){
    	p_ent->setPos(Vector2f(p_ent->getPos().x, p_ent->getPos().y - 1));

    	if (checkCollision(p_ent, p_platforms)) {
			p_ent->setPos(Vector2f(p_ent->getPos().x, p_ent->getPos().y + 1));
			break;
    	}
	}
}

void MovingEntity::moveDown(MovingEntity* p_ent, std::vector<Entity> p_platforms)
{	
	for (unsigned int i = 0u; i<7; ++i){
    	p_ent->setPos(Vector2f(p_ent->getPos().x, p_ent->getPos().y + 1));

    	if (checkCollision(p_ent, p_platforms)){
    		p_ent->setPos(Vector2f(p_ent->getPos().x, p_ent->getPos().y - 1));
			break;
    	}
	}
}	

void MovingEntity::moveRight(MovingEntity* p_ent, std::vector<Entity> p_platforms)
{
 	p_ent->setPos(Vector2f(p_ent->getPos().x + 5, p_ent->getPos().y));

    if (checkCollision(p_ent, p_platforms)){
		p_ent->setPos(Vector2f(p_ent->getPos().x - 5, p_ent->getPos().y));
    }
}

void MovingEntity::moveLeft(MovingEntity* p_ent, std::vector<Entity> p_platforms)
{
 	p_ent->setPos(Vector2f(p_ent->getPos().x - 5, p_ent->getPos().y));

 	if (checkCollision(p_ent, p_platforms)) {
		p_ent->setPos(Vector2f(p_ent->getPos().x + 5, p_ent->getPos().y));
    }
}


/*                           COLLISION CHECK OF MOVING ENTITIES AND OHTER ENTITIES/SCREEN BORDER                           */

bool MovingEntity::checkCollision(MovingEntity* p_player, std::vector<Entity> p_platforms)
{	
	int gWidth, gHeight;
	bool collisionDetected = false;

	int pWidth  = p_player->getCurrentFrame().w; // Get size of player.
	int pHeight = p_player->getCurrentFrame().h;

	for (Entity& ground : p_platforms){
		gWidth  = ground.getCurrentFrame().w; // Get size of ground block.
		gHeight = ground.getCurrentFrame().h;

		collisionDetected = (( (p_player->getPos().y + pHeight) >  (ground.getPos().y)            )    // Player is within ground-height range.
						&&   ( (p_player->getPos().y)           <  (ground.getPos().y + gHeight)  )
						&&   ( (p_player->getPos().x + pWidth)  >  (ground.getPos().x)            )    // Player is within ground-width range.
						&&   ( (p_player->getPos().x)           <  (ground.getPos().x + gWidth)   ) );

		if (collisionDetected)
			break;
	}

	collisionDetected = (    ( (p_player->getPos().y + pHeight) >  720   )    // Player is outside screen Height range.
						||   ( (p_player->getPos().x + pWidth)  >  1310  )    // Player is outside screen Width range.
						||   ( (p_player->getPos().x)           <  -30     ))
						|| collisionDetected ;
 
	p_player->setCollision(collisionDetected);
	
	return collisionDetected;	
}


/*----------------------------------------------------- PLAYER CLASS -------------------------------------------------------*/
Player::Player(Vector2f p_pos, SDL_Texture* p_tex)
:MovingEntity(p_pos, p_tex)
{
	isCrouching = false;
}

void Player::pCrouch(Player* p_player, std::vector<Entity> p_platforms, SDL_Texture* p_crouchTex, SDL_Texture* p_standTex){
	bool isC = p_player->getCrouch();
	p_player->setCrouch(!isC);

	if (!isC)
	{   p_player->setTex(p_player, p_crouchTex);  }
	else 
	{   p_player->setTex(p_player, p_standTex);   }

 	if (checkCollision(p_player, p_platforms)) {
		p_player->setCrouch(isC);
	
		if (isC)
		{	p_player->setTex(p_player, p_crouchTex); }
		else 
		{	p_player->setTex(p_player, p_standTex);  }
    }

}

/*                                                   COLLISION BETWEEN PLAYER AND BULLETS                                       */
bool Player::hitByBullet(Player* p_player, std::vector<MovingEntity*> p_bullets){
	int bWidth, bHeight;
	bool playerIsHit = false;

	int pWidth  = p_player->getCurrentFrame().w; // Get size of player.
	int pHeight = p_player->getCurrentFrame().h;

	for (Entity* bullet : p_bullets){
		bWidth  = bullet->getCurrentFrame().w; // Get size of bullet block.
		bHeight = bullet->getCurrentFrame().h;

		playerIsHit =    (   ( (p_player->getPos().y + pHeight) >  (bullet->getPos().y + bHeight*0.2)  )
						&&   ( (p_player->getPos().y)           <  (bullet->getPos().y + bHeight*0.8)  )
						&&   ( (p_player->getPos().x + pWidth)  >  (bullet->getPos().x + bWidth *0.4)  ) 
						&&   ( (p_player->getPos().x)           <  (bullet->getPos().x + bWidth *0.4)  ));

		if (playerIsHit)
			break;
	} 

	return playerIsHit;  // True if collision was hit by ANY bullet.
}


bool Player::onWinningPlat(Player* p_player, Entity* p_winningPlatform){

	int pWidth  = p_player->getCurrentFrame().w; // Get size of player.
	int pHeight = p_player->getCurrentFrame().h;

	bool onWinningPlat = (   p_player->getPos().y + pHeight   ==  p_winningPlatform->getPos().y
						&&   p_player->getPos().x + pWidth*0.5 >  p_winningPlatform->getPos().x
						&&   p_player->getPos().x + pWidth*0.5 <  p_winningPlatform->getPos().x + WINNING_PLATFORM_WIDTH );

	return onWinningPlat;
}


unsigned int Player::collectedCoin(Player* p_player, std::vector<Entity> p_coins){
	int cWidth, cHeight;

	int pWidth  = p_player->getCurrentFrame().w; // Get size of player.
	int pHeight = p_player->getCurrentFrame().h;

	unsigned int coinIndex = 0u;
	bool coinWasCollected = false;

	while(coinIndex<p_coins.size() && !coinWasCollected){

		cWidth  = p_coins[coinIndex].getCurrentFrame().w; // Get size of coin block.
		cHeight = p_coins[coinIndex].getCurrentFrame().h;

		coinWasCollected =(  ( (p_player->getPos().y + pHeight) >  (p_coins[coinIndex].getPos().y)                      )  // Player is within coin-height range.
						&&   ( (p_player->getPos().y)           <  (p_coins[coinIndex].getPos().y + cHeight)            )
						&&   ( (p_player->getPos().x + pWidth)  >  (p_coins[coinIndex].getPos().x          + pWidth*0.3))  // Player is within coin-width range.
						&&   ( (p_player->getPos().x)           <  (p_coins[coinIndex].getPos().x + cWidth - pWidth*0.3)) );

		if (!coinWasCollected) 
			++coinIndex;
	}

	return coinIndex;
}

bool Player::canJumpNow(Player* p_player, std::vector<Entity> p_platforms)
{	
	int gWidth;
	bool canJump = false;

	int pWidth  = p_player->getCurrentFrame().w; // Get size of player.
	int pHeight = p_player->getCurrentFrame().h;

	for (Entity& ground : p_platforms){
		gWidth  = ground.getCurrentFrame().w; // Get size of ground block.

		canJump = ((    p_player->getPos().y + pHeight  ==  ground.getPos().y              )    // Player is standing on platform.
			      &&   (p_player->getPos().x + pWidth   >=  ground.getPos().x + 5          )    // Player is within ground-width range.
		     	  &&   (p_player->getPos().x            <=  ground.getPos().x + gWidth - 5 ) );

		if (canJump)
			break;
	}
 
	return canJump;	
}

void Player::adjustToMovement(Player* p_player, Entity* p_winningPlatform, float p_platPosDiff){

	int pWidth  = p_player->getCurrentFrame().w; // Get size of player.
	int pHeight = p_player->getCurrentFrame().h;

	int winPlatX = p_winningPlatform->getPos().x;
	int winPlatY = p_winningPlatform->getPos().y;
	int playerX  = p_player->getPos().x;
	int playerY  = p_player->getPos().y;

	bool isBeingPushed = (winPlatY <= playerY + pHeight) && (winPlatY + WINNING_PLATFORM_HEIGHT >= playerY)  // IS IN HEIGHT RANGE
					&& ( (winPlatX + WINNING_PLATFORM_WIDTH >= playerX  && winPlatX <= playerX + pWidth) );  // IS IN WIDTH RANGE

	if(isBeingPushed)
	{
		p_player->setPos(Vector2f(p_player->getPos().x - p_platPosDiff, p_player->getPos().y));
	} 

}