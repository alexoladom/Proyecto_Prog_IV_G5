#include "config.h"
#include "iostream"
#include <string.h>
#include <stdio.h>

using namespace std;

Config2 readConfig2(const char* fileName){
	    ifstream file(fileName);
	    if (!file.is_open()) {
	        cerr << "Error opening file: " << fileName << endl;
	    }

	    string line;
	    Config2 config;

	    while (getline(file, line)) {
	        istringstream iss(line);
	        string key;
	        if (line.find("Dni admin:") != string::npos) {
	            iss.ignore(11); // Ignore "Dni admin: "
	            iss >> config.dni;
	        } else if (line.find("Contraseña admin:") != string::npos) {
	            iss.ignore(18); // Ignore "Contraseña admin: "
	            iss >> config.password;
	        } else if (line.find("IP:") != string::npos) {
	            iss.ignore(4); // Ignore "IP: "
	            iss >> config.ip;
	        } else if (line.find("Port:") != string::npos) {
	            iss.ignore(6); // Ignore "Port: "
	            iss >> config.port;
	        } else if (line.find("Base de datos:") != string::npos) {
	            iss.ignore(15); // Ignore "Base de datos: "
	            iss.getline(config.dbPath, 256);
	        }
	    }

	    file.close();
	    return config;


}



Config readConfig(const char* filename) {
    Config config;
    FILE* file = fopen(filename, "r");

    if (!file) {
        fprintf(stderr, "No se puede cargar el archivo de configuración %s\n", filename);
        exit(1);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char* equals = strchr(line, '=');
        if (equals) {
            *equals = '\0';
            char* key = line;
            char* value = equals + 1;

            // Quitar espacios en blanco alrededor de key y value
            while (isspace((unsigned char)*key)) key++;
            while (isspace((unsigned char)*value)) value++;
            char* end = key + strlen(key) - 1;
            while (end > key && isspace((unsigned char)*end)) end--;
            end[1] = '\0';
            end = value + strlen(value) - 1;
            while (end > value && isspace((unsigned char)*end)) end--;
            end[1] = '\0';

            if (strcmp(key, "ip") == 0) {
                strncpy(config.ip, value, sizeof(config.ip) - 1);
            } else if (strcmp(key, "port") == 0) {
                config.port = atoi(value);
            } else if (strcmp(key, "db_address") == 0) {
                strncpy(config.db_address, value, sizeof(config.db_address) - 1);
            }
        }
    }
    fclose(file);
    return config;
}
