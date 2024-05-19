#ifndef config_h
#define config_h

typedef struct {
    char ip[16];
    int port;
    char db_address[256];
} Config;

Config readConfig(const char* filename);




#endif
