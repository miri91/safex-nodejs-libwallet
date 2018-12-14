//
// Created by amarko on 14.12.18..
//
#include <string>
#include <fstream>

#define LOG_FILENAME "output_wallet_log.txt"

void logToFile(std::string file, std::string function, int line, std::string text) {
    static std::ofstream outfile;
    static bool opened = false;
    if (!opened) {
        outfile.open(LOG_FILENAME, std::ios_base::app);
        opened = true;
    }

    outfile << file << " | " << function<< "@" << line << ":  " << text << std::endl;
}