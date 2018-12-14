//
// Created by amarko on 29.11.18..
//

#include <wallet_api.h>
#include <windows_wrapper.h>
#include <cstring>

#include "winpendingtransaction.h"
#include "walletlog.h"

namespace Safex
{

  WinPendingTransaction::WinPendingTransaction(void *ptr) : m_innerPtr(ptr)
  {
    ENTER_FUNC();
    EXIT_FUNC();
  }

  WinPendingTransaction::~WinPendingTransaction()
  {
    ENTER_FUNC();
    ::win_pt_delete(m_innerPtr);
    EXIT_FUNC();
  }

  int WinPendingTransaction::status() const
  {
    ENTER_FUNC();
    auto result = ::win_pt_status(m_innerPtr);
    EXIT_FUNC();
    return result;
  }

  std::string WinPendingTransaction::errorString() const
  {
    ENTER_FUNC();
    auto result = std::string(win_pt_errorString(m_innerPtr));
    EXIT_FUNC();
    return result;
  }

  bool WinPendingTransaction::commit(const std::string &filename, bool overwrite)
  {
    ENTER_FUNC();
    auto result = static_cast<bool>(::win_pt_commit(m_innerPtr));
    EXIT_FUNC();
    return result;
  }

  uint64_t WinPendingTransaction::amount() const
  {
    ENTER_FUNC();
    auto result = ::win_pt_amount(m_innerPtr);
    EXIT_FUNC();
    return result;
  }

  uint64_t WinPendingTransaction::tokenAmount() const
  {
    ENTER_FUNC();
    auto result = ::win_pt_tokenAmount(m_innerPtr);
    EXIT_FUNC();
    return result;
  }

  uint64_t WinPendingTransaction::dust() const
  {
    ENTER_FUNC();
    auto result = ::win_pt_dust(m_innerPtr);
    EXIT_FUNC();
    return result;
  }

  uint64_t WinPendingTransaction::fee() const
  {
    ENTER_FUNC();
    auto result = ::win_pt_fee(m_innerPtr);
    EXIT_FUNC();
    return result;
  }

  std::vector<std::string> WinPendingTransaction::txid() const
  {
    ENTER_FUNC();
    char *results = ::win_pt_txid(m_innerPtr);
    char *temp = results;
    std::vector<std::string> ret;
    while (temp[0] != 0)
    {
      unsigned char txid[64];
      memmove((void *) txid, (void *) temp, 64);
      ret.push_back(std::string((char *) txid));
      temp += 64;
    }

    return ret;
  }

  uint64_t WinPendingTransaction::txCount() const
  {
    ENTER_FUNC();
    auto result = ::win_pt_txCount(m_innerPtr);
    EXIT_FUNC();
    return result;
  }

  std::vector<uint32_t> WinPendingTransaction::subaddrAccount() const
  {
    ENTER_FUNC();
    EXIT_FUNC();
    return {};
  }

  std::vector<std::set<uint32_t>> WinPendingTransaction::subaddrIndices() const
  {
    ENTER_FUNC();
    EXIT_FUNC();
    return {};
  }

}
