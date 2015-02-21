#include "Utility.h"

void Utility::randomInit()
{
	srand((unsigned int) time(NULL));
}

int Utility::randomInt(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

float Utility::randomFloat(float min, float max)
{
	// Not written by me it's from: http://stackoverflow.com/a/5289624
	// Could have used C++11 for random floats, but I think this is adequate.
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = max - min;
	float r = random * diff;
	return min + r;
}

void Utility::log(LogType type, std::string message)
{
	//Get current time
	time_t currentTime = time(NULL);
	tm timeStruct;
	localtime_s(&timeStruct, &currentTime);
	char textTime[9];

	//strftime(textTime, 11, "%T", &timeStruct); Apparently only Microsoft don't support the %T.
	strftime(textTime,9, "%H:%M:%S", &timeStruct);

	std::cout << textTime;

	switch (type)
	{
	case I:
		std::cout << " Info: ";
		break;
	case W:
		std::cout << " Warning: ";
		break;
	case E:
		std::cout << " Error: ";
		break;
	default:
		std::cout << " ???: ";
		break;
	}

	std::cout << message.c_str() << std::endl;
}

Vec2 Utility::getRectCenter(SDL_Rect rect)
{
	Vec2 center;
	center.x = (float)(rect.x + (rect.w / 2));
	center.y = (float)(rect.y + (rect.h / 2));
	return center;
}

//Timer

std::unordered_map<std::string, Utility::Timer::TimerStruct> Utility::Timer::timers;
const float Utility::Timer::TIME_INTERVAL = 1.0f;

Utility::Timer::Timer() {}

void Utility::Timer::update(float dt)
{
	//Need auto& to get a reference otherwise it's just a local copy (Really Fun Bug to Find)
	for (auto& timer : timers)
	{
		timer.second.currentTime += (float)(TIME_INTERVAL * dt);
	}
}

bool Utility::Timer::createTimer(std::string id, float duration)
{
	//Unordered map can't have duplicates
	if (timers.count(id) == 1)
	{
		log(W,"Timer id specified already exists");
		return false;
	}

	//Create the Timer
	TimerStruct timer = {0.0f, duration};

	//Push it into the timers unordered_map
	timers.insert(std::make_pair(id,timer));

	return true;
}

float Utility::Timer::stopTimer(std::string id)
{
	if (timers.count(id) == 0) { return -1.0f; }

	float finalCurrentTime = timers[id].currentTime;

	timers.erase(id);

	return finalCurrentTime;
}

bool Utility::Timer::hasTimerFinished(std::string id)
{
	if (!timers.count(id))
	{
		log(W,"Unknown timer was asked if finished. Timer ID:" +id);
		return false;
	}
	
	TimerStruct timer = timers[id];
	if (timer.currentTime >= timer.duration)
	{
		//Could call stop timer but would have an extra id check (Which is wasteful)
		timers.erase(id);
		return true;
	}
	else
	{
		return false;
	}
}

void Utility::Timer::cleanup()
{
	timers.clear();
}