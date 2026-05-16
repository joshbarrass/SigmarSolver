#ifndef _DLL_EXPORT_H
#define _DLL_EXPORT_H

#ifdef _MSC_VER
  #define EXPORT __declspec(dllexport)
#else
  #define EXPORT
#endif

#endif
