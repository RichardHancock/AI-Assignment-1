#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <string>
#include <SDL.h>
#include <unordered_map>

#include "Vec2.h"

#pragma once

/**
@brief An assortment of useful functions (random numbers, logging) that don't fit elsewhere.
*/
namespace Utility
{
	/**
	@brief Initialize the Random Number functions

	Call this before any random functions, else random will be the same
	sequence of numbers for each program execution.
	*/
	void randomInit();

	/**
	@brief Generate a random integer number between min and max

	@param int - Minimum Number for the range
	@param int - Maximum Number for the range
	@return int - Random int between min and max
	*/
	int randomInt(int min, int max);

	/**
	@brief Generate a random float number between min and max

	@todo This function is possibly unstable, it just started working with no real changes.

	@param float - Minimum Number for the range
	@param float - Maximum Number for the range
	@return float - Random float between min and max
	*/
	float randomFloat(float min, float max);

	/**
	@brief A type of log message
	*/
	enum LogType
	{
		E, //< Error
		W, //< Warning
		I  //< Info
	};

	/**
	@brief Log a message to the console

	Made this one function instead of multiple to reduce clutter. Could have used SDL_Log instead.
	@param LogType - Type of message E: Error, W: Warning, I: Info
	@param char* - The message to log
	*/
	void log(LogType, std::string);

	/**
	@brief Returns the center position of a rectangle
	@param SDL_Rect - Rectangle struct
	@return Vec2 - Center position of the rectangle
	*/
	Vec2 getRectCenter(SDL_Rect rect);

	/**
	@brief Enum containing all types of tiles
	
	This was in the level manager but was causing a recusive include loop that is easily avoided putting it here.
	*/
	enum TileType
	{
		blank = 0,
		block,
		start,
		finish,
		platform,
		platformHoles,
		beamLeft,
		beamRight,
		blockWarning
	};

	//Timer Management

	/**
	@brief creates a timer for use in game

	This code was used in the Group Project Unit, but was entirely written by me.
	I have upgraded it to use some really useful C++11 which did require a rewrite of all the functions, 
	but the general structure (Headers) is the same.
	*/
	class Timer
	{
	private:
		///a structure for the individual timers
		struct TimerStruct
		{
			float currentTime;
			float duration;
		};
	public:
		/**
		updates the time in the timer

		@param float - delta time
		*/
		static void update(float dt);

		/**
		Creates a new timer with a unique id and a duration

		@param std::string - The id of the timer
		@param float - the duration of the timer
		@returns bool - false if id is not unique
		*/
		static bool createTimer(std::string id, float duration);

		/**
		Stops the time and returns the time taken

		@param std::string - The id of the timer
		@returns float - the time taken
		*/
		static float stopTimer(std::string id);

		/**
		Checks to see if the timer has finished

		@param std::string - The id of the timer
		@returns bool - if the timer has ended
		*/
		static bool hasTimerFinished(std::string id);

		/**
		@brief Deletes all timers
		*/
		static void cleanup();

	private:
		//No one should call this so it is private
		Timer();

		static const float TIME_INTERVAL;

		/**
		@brief Stores the Timers

		1 - currentTime
		2 - duration
		*/
		static std::unordered_map<std::string, TimerStruct> timers;
	};
}

/**
@brief Defines a RGB colour

Didn't realise there was a SDL_Colour until it was too late, oh well...
*/
struct Colour
{
	uint8_t r; //< Red Channel
	uint8_t g; //< Green Channel
	uint8_t b; //< Blue Channel

	/**
	@brief Colour
	@param uint8_t - Red
	@param uint8_t - Green
	@param uint8_t - Blue
	*/
	Colour(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
};

