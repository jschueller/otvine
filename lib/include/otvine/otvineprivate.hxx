
#ifndef OTVINE_PRIVATE_HXX
#define OTVINE_PRIVATE_HXX

/* From http://gcc.gnu.org/wiki/Visibility */
/* Generic helper definitions for shared library support */
#if defined _WIN32 || defined __CYGWIN__
#define OTVINE_HELPER_DLL_IMPORT __declspec(dllimport)
#define OTVINE_HELPER_DLL_EXPORT __declspec(dllexport)
#define OTVINE_HELPER_DLL_LOCAL
#else
#if __GNUC__ >= 4
#define OTVINE_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
#define OTVINE_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
#define OTVINE_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#else
#define OTVINE_HELPER_DLL_IMPORT
#define OTVINE_HELPER_DLL_EXPORT
#define OTVINE_HELPER_DLL_LOCAL
#endif
#endif

/* Now we use the generic helper definitions above to define OTVINE_API and OTVINE_LOCAL.
 * OTVINE_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
 * OTVINE_LOCAL is used for non-api symbols. */

#ifndef OTVINE_STATIC /* defined if OT is compiled as a DLL */
#ifdef OTVINE_DLL_EXPORTS /* defined if we are building the OT DLL (instead of using it) */
#define OTVINE_API OTVINE_HELPER_DLL_EXPORT
#else
#define OTVINE_API OTVINE_HELPER_DLL_IMPORT
#endif /* OTVINE_DLL_EXPORTS */
#define OTVINE_LOCAL OTVINE_HELPER_DLL_LOCAL
#else /* OTVINE_STATIC is defined: this means OT is a static lib. */
#define OTVINE_API
#define OTVINE_LOCAL
#endif /* !OTVINE_STATIC */


#endif // OTVINE_PRIVATE_HXX

