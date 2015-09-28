#ifndef TALKBACKINTERFACECOMMON_H
#define TALKBACKINTERFACECOMMON_H


#if defined(_WIN32)
 #define TALKBACKCALL __cdecl
#else
 #define TALKBACKCALL
#endif


#if defined(__cplusplus)
extern "C" {
#endif

#ifndef TalkbackInterface_API
 #if defined(_WIN32)
  #define TalkbackInterface_API __declspec(dllimport)
 #else
  #define TalkbackInterface_API extern
 #endif
#endif


#if defined(__cplusplus)
}
#endif
#endif // TALKBACKINTERFACECOMMON_H
