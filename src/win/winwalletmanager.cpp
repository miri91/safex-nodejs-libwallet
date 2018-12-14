//
// Created by amarko on 29.11.18..
//

#include <string>
#include <vector>
#include <tuple>

#include <winwalletmanager.h>

#include <windows_wrapper.h>
#include "walletlog.h"


namespace Safex
{

  SafexNativeWallet *WinWalletManager::createWallet(const std::string &path, const std::string &password, const std::string &language, NetworkType nettype)
  {
    ENTER_FUNC();
    SafexNativeWallet *nativeWallet = new WinWallet(win_mng_createWallet(m_innerPtr, path.c_str(), password.c_str(), language.c_str(), nettype));
    EXIT_FUNC();
    return nativeWallet;
  }

  SafexNativeWallet *WinWalletManager::openWallet(const std::string &path, const std::string &password, NetworkType nettype)
  {
    ENTER_FUNC();
    WinWallet *nativeWallet = new WinWallet(win_mng_openWallet(m_innerPtr, path.c_str(), password.c_str(), static_cast<uint32_t>(nettype)));
    EXIT_FUNC();
    return nativeWallet;
  }

  SafexNativeWallet *WinWalletManager::recoveryWallet(const std::string &path, const std::string &password, const std::string &mnemonic, NetworkType nettype, uint64_t restoreHeight)
  {
    ENTER_FUNC();
    WinWallet *nativeWallet = new WinWallet(win_mng_recoveryWallet(m_innerPtr, path.c_str(), password.c_str(), mnemonic.c_str(), static_cast<uint32_t>(nettype), restoreHeight));
    EXIT_FUNC();
    return nativeWallet;
  }

  SafexNativeWallet *WinWalletManager::recoveryWallet(const std::string &path, const std::string &mnemonic, NetworkType nettype, uint64_t restoreHeight)
  {
    ENTER_FUNC();
    EXIT_FUNC();
    return nullptr;
  }

  SafexNativeWallet *WinWalletManager::createWalletFromKeys(const std::string &path, const std::string &password, const std::string &language, NetworkType nettype, uint64_t restoreHeight,
          const std::string &addressString, const std::string &viewKeyString, const std::string &spendKeyString)
  {
    ENTER_FUNC();
    WinWallet *nativeWallet = new WinWallet(win_mng_createWalletFromKeys(m_innerPtr, path.c_str(), password.c_str(), language.c_str(), static_cast<uint32_t>(nettype), restoreHeight,
                                                                         addressString.c_str(), viewKeyString.c_str(), spendKeyString.c_str()));

    EXIT_FUNC();
    return nativeWallet;
  }

  bool WinWalletManager::closeWallet(SafexNativeWallet *wallet, bool store)
  {
    ENTER_FUNC();
    EXIT_FUNC();
    return false;
  }

  bool WinWalletManager::walletExists(const std::string &path)
  {
    ENTER_FUNC();
    auto result = win_mng_walletExists(m_innerPtr, path.c_str());
    EXIT_FUNC();
    return result;
  }

  bool WinWalletManager::verifyWalletPassword(const std::string &keys_file_name, const std::string &password, bool no_spend_key) const
  {
    ENTER_FUNC();
    EXIT_FUNC();
    return false;
  }

  std::vector<std::string> WinWalletManager::findWallets(const std::string &path)
  {
    ENTER_FUNC();
    auto result = std::vector<std::string>();
    EXIT_FUNC();
    return result;
  }

  std::string WinWalletManager::errorString() const
  {
    ENTER_FUNC();
    auto result = std::string();
    EXIT_FUNC();
    return result;
  }

  void WinWalletManager::setDaemonAddress(const std::string &address)
  {
    ENTER_FUNC();
    EXIT_FUNC();
  }

  bool WinWalletManager::connected(uint32_t *version)
  {
    ENTER_FUNC();
    auto result = false;
    EXIT_FUNC();
    return result;
  }

  uint64_t WinWalletManager::blockchainHeight()
  {
    ENTER_FUNC();
    auto result = static_cast<uint64_t>(0);
    EXIT_FUNC();
    return result;
  }

  uint64_t WinWalletManager::blockchainTargetHeight()
  {
    ENTER_FUNC();
    auto result = static_cast<uint64_t>(0);
    EXIT_FUNC();
    return result;
  }

  uint64_t WinWalletManager::networkDifficulty()
  {
    ENTER_FUNC();
    auto result = static_cast<uint64_t>(0);
    EXIT_FUNC();
    return result;
  }

  double WinWalletManager::miningHashRate()
  {
    ENTER_FUNC();
    auto result = static_cast<uint64_t>(0);
    EXIT_FUNC();
    return result;
  }

  uint64_t WinWalletManager::blockTarget()
  {
    ENTER_FUNC();
    auto result = static_cast<uint64_t>(0);
    EXIT_FUNC();
    return result;
  }

  bool WinWalletManager::isMining()
  {
    ENTER_FUNC();
    auto result = false;
    EXIT_FUNC();
    return result;
  }

  bool WinWalletManager::startMining(const std::string &address, uint32_t threads, bool background_mining, bool ignore_battery)
  {
    ENTER_FUNC();
    auto result = false;
    EXIT_FUNC();
    return result;
  }

  bool WinWalletManager::stopMining()
  {
    ENTER_FUNC();
    auto result = false;
    EXIT_FUNC();
    return result;
  }

  std::string WinWalletManager::resolveOpenAlias(const std::string &address, bool &dnssec_valid) const
  {
    ENTER_FUNC();
    auto result = std::string();
    EXIT_FUNC();
    return result;
  }

  std::tuple<bool, std::string, std::string, std::string, std::string> WinWalletManager::checkUpdates(const std::string &software, std::string subdir)
  {
    ENTER_FUNC();
    auto result = std::tuple<bool, std::string, std::string, std::string, std::string>();
    EXIT_FUNC();
    return result;
  }

  WinWalletManager *WinWalletManagerFactory::getWalletManager()
  {
    ENTER_FUNC();
    WinWalletManager *winWalletManager = new WinWalletManager(::win_mngf_getWalletManager());
    WinWalletManagerFactory::setLogLevel(LogLevel::LogLevel_0); //by default mlog it prints on stdout on Windows
    EXIT_FUNC();
    return winWalletManager;
  }

  void WinWalletManagerFactory::setLogLevel(int level)
  {
    ENTER_FUNC();
    win_mlog_set_log_levelI(level);
    EXIT_FUNC();
  }

  void WinWalletManagerFactory::setLogCategories(const std::string &categories)
  {
    ENTER_FUNC();
    win_mlog_set_log_levelCPtr(categories.c_str());
    EXIT_FUNC();
  }
}
