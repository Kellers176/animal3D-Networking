#ifndef COOKIECLICKER_H
#define COOKIECLICKER_H


#ifdef __cplusplus
extern "C"
{
#else	// !__cplusplus
typedef struct CookieClicker				CookieClicker;
#endif	// __cplusplus


#pragma pack(push,1)
struct CookieClicker
{
	unsigned char typeID;
	int number;
};
#pragma pack(push)


#ifdef __cplusplus
}
#endif	// __cplusplus


#endif // !COOKIECLICKER
