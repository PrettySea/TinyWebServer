#ifndef GLOBAL_H
#define GLOBAL_H

#ifndef BEGIN_TINYWEBSERVER_NAMESPACE
#    define BEGIN_TINYWEBSERVER_NAMESPACE \
        namespace tiny \
        { \
        namespace webserver \
        {
#endif

#ifndef END_TINYWEBSERVER_NAMESPACE
#    define END_TINYWEBSERVER_NAMESPACE \
        } \
        }
#endif

#ifndef USE_TINYWEBSERVER_NAMESPACE
#    define USE_TINYWEBSERVER_NAMESPACE using namespace tiny::webserver;
#endif
#endif