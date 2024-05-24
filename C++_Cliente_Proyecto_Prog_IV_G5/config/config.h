#ifndef config_h
#define config_h
#include <string>


typedef struct {
    char ip[16];
    int port;
    char db_address[256];
} Config;

Config readConfig(const char* filename);

typedef struct {
	int dni;
	std::string password;
    char ip[16];
    int port;
}
Config2;

Config2 readConfig2(const char* fileName);




#endif
