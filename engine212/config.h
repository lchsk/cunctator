#ifndef ENGINE_CONFIG_H
#define ENGINE_CONFIG_H


/* Settings ******************************************************************/

#define DEBUG
#define DEBUG_LOG_LOADING

/* Macros ********************************************************************/

#ifdef DEBUG
#define DEBUG_TEST 1
#else
#define DEBUG_TEST 0
#endif

#define LOGSTR(...) \
            do { if (DEBUG_TEST) fprintf(stderr, __VA_ARGS__); } while (0)

#define LOGFMT(fmt, ...) \
        do { if (DEBUG_TEST) fprintf(stderr, "%s:%d\t%s\t" fmt, __FILE__, \
                                __LINE__, __func__, __VA_ARGS__); } while (0)

#endif /* ENGINE_CONFIG_H */
