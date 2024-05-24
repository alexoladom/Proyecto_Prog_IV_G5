#include "config.h"
#include "iostream"
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <sstream>

using namespace std;


Config2 readConfig2(const char* fileName){
	    ifstream file(fileName);
	    if (!file.is_open()) {
	        cerr << "Error abriendo archivo config: " << fileName <<endl;
	    }

	    string linea;

	    Config2 conf;

	    while (getline(file, linea)) {
	        istringstream iss(linea);
	        if (linea.find("Dni admin:") != string::npos) {
				iss.ignore(11); // Ignore "Dni admin: "
				iss >> conf.dni;
			} else if (linea.find("Contraseña admin:") != string::npos) {
				iss.ignore(18); // Ignore "Contraseña admin: "
				iss >> conf.password;
			}else if (linea.find("IP:") != string::npos) {
	            iss.ignore(4);
	            iss >> conf.ip;
	        } else if (linea.find("Port:") != string::npos) {
	            iss.ignore(6);
	            iss >> conf.port;
	        }
	    }

	    file.close();
	    return conf;
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
