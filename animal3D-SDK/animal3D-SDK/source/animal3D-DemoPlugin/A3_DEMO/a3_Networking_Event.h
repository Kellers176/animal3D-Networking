#ifndef A3_NETWORKING_EVENT_H
#define A3_NETWORKING_EVENT_H


class a3_Networking_Event
{
public:

	a3_Networking_Event();
	~a3_Networking_Event();

	virtual void execute() = 0;
	virtual void dispatch() = 0;

private:


};


#endif