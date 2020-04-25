#ifndef POWERPIPMESSAGE_H
#define POWERPIPMESSAGE_H

#ifdef __cplusplus
extern "C"
{
#else	// !__cplusplus
typedef struct PowerPipMessage				PowerPipMessage;
#endif	// __cplusplus


#pragma pack(push,1)
struct PowerPipMessage
{
	int typeID;
	bool powerTime;
};
#pragma pack(push)


#ifdef __cplusplus
}
#endif	// __cplusplus


#endif