//
// Created by amarko on 14.12.18..
//

#include <string>

#define DEBUG_WALLET

#ifndef SAFEX_NODEJS_LIBWALLET_WALLETLOG_H
#define SAFEX_NODEJS_LIBWALLET_WALLETLOG_H

void logToFile(std::string file, std::string function, int line, std::string text);

#ifdef DEBUG_WALLET
#define ENTER_FUNC() do {logToFile(__FILE__, __FUNCTION__, __LINE__, "enter");} while(0);
#define EXIT_FUNC() do {logToFile(__FILE__, __FUNCTION__, __LINE__, "exit");} while(0);
#define LOG_TEXT(text) do {logToFile(__FILE__, __FUNCTION__, __LINE__, text);} while(0);
#else
#define ENTER_FUNC()
#define EXIT_FUNC()
#define LOG_TEXT(file, function, line, text)
#endif

#endif //SAFEX_NODEJS_LIBWALLET_WALLETLOG_H
