#include "Text.hpp"
#include "RenderWindow.hpp"


Text::Text(SDL_Renderer *renderer, const std::string &font_path, int font_size, 
	  		const std::string &message_text, const SDL_Color &color)
{
	_text_texture = loadFont(renderer, font_path, font_size, message_text, color);
	SDL_QueryTexture(_text_texture, nullptr, nullptr, &_text_rect.w, &_text_rect.h);
}

void Text::displayText(int x, int y, SDL_Renderer *renderer) const {
	_text_rect.x = x;
	_text_rect.y = y;
	SDL_RenderCopy(renderer, _text_texture, nullptr, &_text_rect);
}

SDL_Texture* Text::loadFont(SDL_Renderer *renderer, const std::string &font_path, int font_size, 
											const std::string &message_text, const SDL_Color &color)
{
	TTF_Font *font = TTF_OpenFont(font_path.c_str(), font_size);
	if (!font){std::cout << "Failed to load Font.\n" << std::endl;}

	SDL_Surface *textSurface = TTF_RenderUTF8_Solid(font, message_text.c_str(), color);
	if (!textSurface){std::cout << "Failed to create text surface.\n" << std::endl;}

	SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!text_texture){std::cout << "Failed to create text texture.\n" << std::endl;}

    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);

    return text_texture;
}

void Text::destroyText(void){
	SDL_DestroyTexture(_text_texture);
}