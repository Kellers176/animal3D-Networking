#ifndef RESETMESSAGE_H
#define RESETMESSAGE_H

#ifdef __cplusplus
extern "C"
{
#else	// !__cplusplus
typedef struct ResetMessage				ResetMessage;
#endif	// __cplusplus


#pragma pack(push,1)
struct ResetMessage
{
	int typeID;
	bool resetMe;
};
#pragma pack(push)


#ifdef __cplusplus
}
#endif	// __cplusplus


#endif