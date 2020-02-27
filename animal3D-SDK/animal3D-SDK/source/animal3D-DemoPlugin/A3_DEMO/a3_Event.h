#ifndef A3_EVENT_H
#define A3_EVENT_H

class a3_Event
{
public:

	a3_Event();
	~a3_Event();

	virtual void execute() = 0;
	virtual void dispatch() = 0;

private:


};
#endif