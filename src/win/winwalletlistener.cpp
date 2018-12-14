//
// Created by amarko on 29.11.18..
//


#include <cstdint>
#include <winwalletlistener.h>

#include <windows_wrapper.h>
#include "walletlog.h"

namespace Safex
{


  void WinWalletListenerProxy::moneySpent(void *target, const char *txId, uint64_t amount)
  {
    ENTER_FUNC();
    WinWalletListener *sink = static_cast<WinWalletListener *>(target);
    sink->moneySpent((txId), amount);
    EXIT_FUNC();
  }

  void WinWalletListenerProxy::moneyReceived(void *target, const char *txId, uint64_t amount)
  {
    ENTER_FUNC();
    WinWalletListener *sink = static_cast<WinWalletListener *>(target);
    sink->moneyReceived((txId), amount);
    EXIT_FUNC();
  }

  void WinWalletListenerProxy::unconfirmedMoneyReceived(void *target, const char *txId, uint64_t amount)
  {
    ENTER_FUNC();
    WinWalletListener *sink = static_cast<WinWalletListener *>(target);
    sink->unconfirmedMoneyReceived(std::string(txId), amount);
    EXIT_FUNC();
  }

  void WinWalletListenerProxy::tokensSpent(void *target, const char *txId, uint64_t token_amount)
  {
    ENTER_FUNC();
    WinWalletListener *sink = static_cast<WinWalletListener *>(target);
    sink->tokensSpent(std::string(txId), token_amount);
    EXIT_FUNC();
  }

  void WinWalletListenerProxy::tokensReceived(void *target, const char *txId, uint64_t token_amount)
  {
    ENTER_FUNC();
    WinWalletListener *sink = static_cast<WinWalletListener *>(target);
    sink->tokensReceived(std::string(txId), token_amount);
    EXIT_FUNC();
  }

  void WinWalletListenerProxy::unconfirmedTokensReceived(void *target, const char *txId, uint64_t token_amount)
  {
    ENTER_FUNC();
    WinWalletListener *sink = static_cast<WinWalletListener *>(target);
    sink->unconfirmedTokensReceived(std::string(txId), token_amount);
    EXIT_FUNC();
  }

  void WinWalletListenerProxy::newBlock(void *target, uint64_t height)
  {
    ENTER_FUNC();
    WinWalletListener *sink = static_cast<WinWalletListener *>(target);
    sink->newBlock(height);
    EXIT_FUNC();
  }

  void WinWalletListenerProxy::updated(void *target)
  {
    ENTER_FUNC();
    WinWalletListener *sink = static_cast<WinWalletListener *>(target);
    sink->updated();
    EXIT_FUNC();
  }

  void WinWalletListenerProxy::refreshed(void *target)
  {
    ENTER_FUNC();
    WinWalletListener *sink = static_cast<WinWalletListener *>(target);
    sink->refreshed();
    EXIT_FUNC();
  }


}
