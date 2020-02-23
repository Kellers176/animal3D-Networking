#include "ShiftEvent.h"

ShiftEvent::ShiftEvent()
{
	numToIncriment = 0;
}

ShiftEvent::ShiftEvent(CookieClicker* cookie)
{
	myCookie = cookie;
	numToIncriment = 0;
}

ShiftEvent::~ShiftEvent()
{
}

void ShiftEvent::execute()
{
	numToIncriment++;
	myCookie->number++;
}

void ShiftEvent::dispatch()
{

}
