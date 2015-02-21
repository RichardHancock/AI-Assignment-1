#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "Vec2.h"
#include "Utility.h"

#pragma once

/**
@class Texture
@brief Encapsulates an SDL_Texture

Contains the ability to draw, load, etc.. Textures.
*/
class Texture
{
public:
	/**
	@brief Create a Texture
	@param std::string - Path to image
	@param SDL_Renderer* - Renderer
	*/
	Texture(std::string, SDL_Renderer*);

	/**
	@brief Create a Texture
	@param SDL_Surface* - A surface to convert into a texture (This is freed internally)
	@param SDL_Renderer* - Renderer
	*/
	Texture(SDL_Surface*, SDL_Renderer*);

	~Texture();

	/**
	@brief Gets the Dimensions of the stored texture
	@return Vec2 - Dimensions of Sprite
	*/
	Vec2 Texture::getDimensions();

	/**
	@brief Draw the Sprite
	@param Vec2 - Position to draw at
	*/
	void Texture::draw(Vec2 pos);

	/**
	@brief Draw the Sprite
	@param Vec2 - Position to draw at
	@param bool - Whether the sprite shouldn't be flipped (True doesn't flip, false does)
	*/
	void Texture::draw(Vec2 pos, bool facingRight);

	/**
	@brief Draw the Sprite
	@param Vec2 - Position to draw at
	@param float - Rotation of the sprite in degrees (Around middle of sprite)
	*/
	void Texture::draw(Vec2 pos, float rotation);

	/**
	@brief Draw the Sprite
	@param Vec2 - Position to draw at
	@param float - Rotation of the sprite in degrees around pivot point
	@param Vec2 - Pivot point to rotate around
	*/
	void Texture::draw(Vec2 pos, float rotation, Vec2 pivot);

	/**
	@brief Load Image
	@param std::string - Path to image
	@param SDL_Renderer* - Renderer
	*/
	bool Texture::load(std::string, SDL_Renderer*);

	/**
	@brief Load Image
	@param SDL_Surface* - A surface to convert into a texture (This is freed internally)
	@param SDL_Renderer* - Renderer
	*/
	bool Texture::load(SDL_Surface*, SDL_Renderer*);

	/**
	@brief Apply a tint to the texture (Warning this applied to all textures sharing if this is a pointer)
	@param Colour - Colour tint to apply
	*/
	void Texture::setColourTint(Colour colour);

	/**
	@brief Get the renderer used for this sprite
	@return SDL_Renderer* - The renderer used in the creation of this Texture
	*/
	SDL_Renderer* Texture::getRenderer();
private:
	/// Stored Dimensions of the Texture
	Vec2 dimensions;

	/// Texture data
	SDL_Texture* texture;

	/// Renderer
	SDL_Renderer* currentRenderer;

	/**
	@brief Create a texture from a passed in surface 
	@param SDL_Surface - Image Surface
	@return bool - Whether it was successful
	*/
	bool Texture::createTexture(SDL_Surface&);
};

