#ifndef config_h
#define config_h

typedef struct {
    char ip[16];
    int port;
    char db_address[256];
} Config;

Config readConfig(const char* filename);


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

typedef struct  {
    int dni;
    std::string password;
    char ip[16];
    int port;
    char dbPath[256];
}Config2;

Config2 readConfig2(const char* fileName);


#endif
