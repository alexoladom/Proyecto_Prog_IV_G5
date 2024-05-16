#include "Logger.h"
#include <iostream>
#include <time.h>


std::ofstream Logger::logFile;

const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

void Logger::init(const std::string& logFilePath) {
    logFile.open(logFilePath, std::ios_base::app);
    if (!logFile.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de registro." << std::endl;
    }
}

void Logger::logInfo(const std::string& message) {
    if (logFile.is_open()) {
        logFile <<currentDateTime()<< " - [INFO] " << message << std::endl;
    } else {
        std::cerr << "Error: El archivo de registro no está abierto." << std::endl;
    }
}

void Logger::logError(const std::string& message) {
    if (logFile.is_open()) {
        logFile <<currentDateTime()<< " - [ERROR] " << message << std::endl;
    } else {
        std::cerr << "Error: El archivo de registro no está abierto." << std::endl;
    }
}

void Logger::close() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

//Ejemplo de implementacion de logger:
//#include "Logger.h"
//
//int main() {
//    // Inicializar el logger
//    Logger::init("archivo_log.txt");
//
//    // Registrar mensajes
//    Logger::logInfo("Inicio del programa");
//    Logger::logError("Error al procesar la reserva");
//
//    // Cerrar el logger
//    Logger::close();
//
//    return 0;
//}
