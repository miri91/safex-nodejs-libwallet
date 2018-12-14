//
// Created by amarko on 28.11.18..
//


#include <winwallet.h>

#include <windows_wrapper.h>
#include "winwalletlistener.h"
#include "winpendingtransaction.h"
#include "walletlog.h"


namespace Safex {

WinTransactionInfo::Transfer::Transfer(uint64_t _amount, uint64_t _token_amount, const std::string &_address)
    : amount(_amount), token_amount(_token_amount), address(_address) {}


  WinTransactionInfo::~WinTransactionInfo()
  {
    ENTER_FUNC();
    win_txinfo_deleteTransactionInfo(m_innerPtr);
    EXIT_FUNC();
  }

  int WinTransactionInfo::direction() const
  {
    ENTER_FUNC();
    auto result = static_cast<int>(win_txinfo_direction(m_innerPtr));
    EXIT_FUNC();
    return result;
  }

  bool WinTransactionInfo::isPending() const
  {
    ENTER_FUNC();
    auto result = static_cast<bool>(win_txinfo_isPendingB(m_innerPtr));
    EXIT_FUNC();
    return result;
  }

  bool WinTransactionInfo::isFailed() const
  {
    ENTER_FUNC();
    auto result = static_cast<bool>(win_txinfo_isFailedB(m_innerPtr));
    EXIT_FUNC();
    return result;
  }

  uint64_t WinTransactionInfo::amount() const
  {
    ENTER_FUNC();
    auto result = win_txinfo_amount(m_innerPtr);
    EXIT_FUNC();
    return result;
  }

  uint64_t WinTransactionInfo::fee() const
  {
    ENTER_FUNC();
    auto result = win_txinfo_fee(m_innerPtr);
    EXIT_FUNC();
    return result;
  }

  uint64_t WinTransactionInfo::blockHeight() const
  {
    ENTER_FUNC();
    auto result = win_txinfo_blockHeight(m_innerPtr);
    EXIT_FUNC();
    return result;
  }

  std::set<uint32_t> WinTransactionInfo::subaddrIndex() const
  {
    ENTER_FUNC();
    auto result = std::set<uint32_t>();
    EXIT_FUNC();
    return result;
  }

  uint32_t WinTransactionInfo::subaddrAccount() const
  {
    ENTER_FUNC();
    auto result = 0;
    EXIT_FUNC();
    return result;
  }

  std::string WinTransactionInfo::label() const
  {
    ENTER_FUNC();
    auto result = std::string(win_txinfo_label(m_innerPtr));
    EXIT_FUNC();
    return result;
  }

  uint64_t WinTransactionInfo::confirmations() const
  {
    ENTER_FUNC();
    auto result = win_txinfo_confirmations(m_innerPtr);
    EXIT_FUNC();
    return result;
  }

  uint64_t WinTransactionInfo::unlockTime() const
  {
    ENTER_FUNC();
    auto result = win_txinfo_unlockTime(m_innerPtr);
    EXIT_FUNC();
    return result;
  }

  std::string WinTransactionInfo::hash() const
  {
    ENTER_FUNC();
    auto result = std::string(win_txinfo_hash(m_innerPtr));
    EXIT_FUNC();
    return result;
  }

  std::time_t WinTransactionInfo::timestamp() const
  {
    ENTER_FUNC();
    auto result = static_cast<std::time_t>(win_txinfo_timestamp(m_innerPtr));
    EXIT_FUNC();
    return result;
  }

  std::string WinTransactionInfo::paymentId() const
  {
    ENTER_FUNC();
    auto result = std::string(win_txinfo_paymentId(m_innerPtr));
    EXIT_FUNC();
    return result;
  }

  const std::vector<WinTransactionInfo::Transfer> &WinTransactionInfo::transfers() const
  {
    ENTER_FUNC();
    std::vector<WinTransactionInfo::Transfer> ret;
    char* buffer = ::win_txinfo_transfers(m_innerPtr);
    uint32_t offset = 0;

    uint32_t transfer_len;
    memcpy(&transfer_len, buffer, sizeof(uint32_t));
    offset += sizeof(uint32_t);
    for(uint32_t i = 0; i < transfer_len; ++i) {
      uint32_t addr_len = 0;
      uint64_t amount;
      uint64_t token_amount;
      std::string addr;
      memcpy(&(amount), buffer+offset, sizeof(uint64_t));
      offset += sizeof(uint64_t);
      memcpy(&(token_amount), buffer+offset, sizeof(uint64_t));
      offset += sizeof(uint64_t);
      addr = std::string(buffer+offset);
      offset += addr.size() + 1;

      ret.emplace_back(amount, token_amount, addr);
    }
    EXIT_FUNC();
    return ret;
  }

  TransactionType WinTransactionInfo::transactionType() const
  {
    ENTER_FUNC();
    auto result = static_cast<TransactionType>(win_txinfo_transactionType(m_innerPtr));
    EXIT_FUNC();
    return result;
  }


  WinTransactionHistory::~WinTransactionHistory()
  {
    ENTER_FUNC();
    win_txhist_Delete(m_innerPtr);
    EXIT_FUNC();
  }

  int WinTransactionHistory::count() const
  {
    ENTER_FUNC();
    auto result = static_cast<int>(win_txhist_count(m_innerPtr));
    EXIT_FUNC();
    return result;
  }

  WinTransactionInfo *WinTransactionHistory::transaction(int index) const
  {
    ENTER_FUNC();
    void* txInfo = win_txhist_transactionInt(m_innerPtr, index);
    auto result = new WinTransactionInfo(txInfo);
    EXIT_FUNC();
    return result;
  }

  WinTransactionInfo *WinTransactionHistory::transaction(const std::string &id) const
  {
    ENTER_FUNC();
    void* txInfo = win_txhist_transactionStr(m_innerPtr, id.c_str());
    auto result = new WinTransactionInfo(txInfo);
    EXIT_FUNC();
    return result;
  }

  std::vector<WinTransactionInfo *> WinTransactionHistory::getAll() const
  {
    ENTER_FUNC();
    std::vector<WinTransactionInfo *> ret;

    uint32_t size = 0;
    void** results = win_txhist_getAll(m_innerPtr, &size);

    for(uint32_t i = 0; i < size; ++i) {
      ret.push_back(new WinTransactionInfo(results[i]));
    }
    EXIT_FUNC();
    return ret;
  }

  void WinTransactionHistory::refresh()
  {
    ENTER_FUNC();
    win_txhist_refresh(m_innerPtr);
    EXIT_FUNC();
  }




  WinWallet::~WinWallet()
  {
    ENTER_FUNC();
    EXIT_FUNC();

  }

  std::string WinWallet::seed() const
  {
    ENTER_FUNC();
    auto result = std::string(win_seed(m_innerPtr));
    EXIT_FUNC();
    return result;
  }

  Wallet *WinWallet::createWallet(const std::string &path, const std::string &password, const std::string &language, NetworkType nettype)
  {
    ENTER_FUNC();
    EXIT_FUNC();
    return nullptr;
  }

  std::string WinWallet::address(uint32_t accountIndex, uint32_t addressIndex) const
  {
    ENTER_FUNC();
    auto result = std::string(win_address(m_innerPtr));
    EXIT_FUNC();
    return result;
  }

  std::string WinWallet::path() const
  {
    ENTER_FUNC();
    auto result = std::string(win_path(m_innerPtr));
    EXIT_FUNC();
    return result;
  }

  NetworkType WinWallet::nettype() const
  {
    ENTER_FUNC();
    auto result = static_cast<NetworkType>(win_nettype(m_innerPtr));
    EXIT_FUNC();
    return result;
  }

  std::string WinWallet::secretViewKey() const
  {
    ENTER_FUNC();
    auto result = std::string(win_secretViewKey(m_innerPtr));
    EXIT_FUNC();
    return result;
  }

  std::string WinWallet::publicViewKey() const
  {
    ENTER_FUNC();
    auto result = std::string(win_publicViewKey(m_innerPtr));
    EXIT_FUNC();
    return result;
  }

  std::string WinWallet::secretSpendKey() const
  {
    ENTER_FUNC();
    auto result = std::string(win_secretSpendKey(m_innerPtr));
    EXIT_FUNC();
    return result;
  }

  std::string WinWallet::publicSpendKey() const
  {
    auto result = std::string(win_publicSpendKey(m_innerPtr));
    EXIT_FUNC();
    return result;
  }

  bool WinWallet::setPassword(const std::string &password)
  {
    ENTER_FUNC();
    auto result = static_cast<bool>(win_setPasswordB(m_innerPtr, password.c_str()));
    EXIT_FUNC();
    return result;
  }

  std::string WinWallet::errorString() const
  {
    ENTER_FUNC();
    auto result = std::string(win_errorString(m_innerPtr));
    EXIT_FUNC();
    return result;
  }

  bool WinWallet::init(const std::string &daemon_address, uint64_t upper_transaction_size_limit, const std::string &daemon_username, const std::string &daemon_password, bool use_ssl, bool lightWallet)
  {
    ENTER_FUNC();
    auto result = static_cast<bool>(win_initB(m_innerPtr, daemon_address.c_str()));
    EXIT_FUNC();
    return result;
  }

  bool WinWallet::store(const std::string &path)
  {
    ENTER_FUNC();
    auto result = static_cast<bool>(win_storeB(m_innerPtr, path.c_str()));
    EXIT_FUNC();
    return result;
  }

  void WinWallet::segregatePreForkOutputs(bool segregate) {
    ENTER_FUNC();
    win_segregatePreForkOutputs(m_innerPtr, static_cast<uint8_t>(segregate));
    EXIT_FUNC();
  }

  void WinWallet::keyReuseMitigation2(bool mitigation) {
    ENTER_FUNC();
    win_keyReuseMitigation2(m_innerPtr, mitigation);
    EXIT_FUNC();
  }

  uint64_t WinWallet::getRefreshFromBlockHeight() const
  {
    auto result = win_getRefreshFromBlockHeight(m_innerPtr);
    EXIT_FUNC();
    return result;
  }

  bool WinWallet::trustedDaemon() const
  {
    ENTER_FUNC();
    auto result = static_cast<bool>(win_trustedDaemonB(m_innerPtr));
    EXIT_FUNC();
    return result;
  }

  std::string WinWallet::genPaymentId()
  {
    ENTER_FUNC();
    auto result = std::string(win_GenPaymentId());
    EXIT_FUNC();
    return result;
  }

  uint64_t WinWallet::daemonBlockChainHeight() const
  {
    ENTER_FUNC();
    auto result = win_daemonBlockChainHeight(m_innerPtr);
    EXIT_FUNC();
    return result;
  }

  bool WinWallet::synchronized() const
  {
    ENTER_FUNC();
    auto result = static_cast<bool>(win_synchronizedB(m_innerPtr));
    EXIT_FUNC();
    return result;
  }

  bool WinWallet::paymentIdValid(const std::string &paiment_id)
  {
    ENTER_FUNC();
    auto result = static_cast<bool>(win_PaymentIdValid(paiment_id.c_str()));
    EXIT_FUNC();
    return result;
  }

  bool WinWallet::addressValid(const std::string &str, NetworkType nettype)
  {
    ENTER_FUNC();
    auto result = static_cast<bool>(win_static_addressValid(str.c_str(), static_cast<uint32_t>(nettype)));
    EXIT_FUNC();
    return result;
  }

  uint32_t WinWallet::defaultMixin() const
  {
    ENTER_FUNC();
    auto result = 0;
    EXIT_FUNC();
    return result;
  }

  WinTransactionHistory *WinWallet::history()
  {
    ENTER_FUNC();
    auto result = static_cast<WinTransactionHistory*>(nullptr);
    EXIT_FUNC();
    return result;
  }

  Safex::Wallet::ConnectionStatus WinWallet::connected() const
  {
    ENTER_FUNC();
    auto result = static_cast<Safex::Wallet::ConnectionStatus>(win_connected(m_innerPtr));
    EXIT_FUNC();
    return result;
  }

  void WinWallet::setTrustedDaemon(bool arg)
  {
    ENTER_FUNC();
    win_setTrustedDaemon(m_innerPtr, static_cast<uint8_t>(arg));
    EXIT_FUNC();
  }

  uint64_t WinWallet::balanceAll() const
  {
    ENTER_FUNC();
    auto result = win_balanceAll(m_innerPtr);
    EXIT_FUNC();
    return result;
  }

  uint64_t WinWallet::unlockedBalanceAll() const
  {
    ENTER_FUNC();
    auto result = win_unlockedBalanceAll(m_innerPtr);
    EXIT_FUNC();
    return result;
  }

  uint64_t WinWallet::tokenBalanceAll() const
  {
    ENTER_FUNC();
    auto result = win_tokenBalanceAll(m_innerPtr);
    EXIT_FUNC();
    return result;
  }

  uint64_t WinWallet::unlockedTokenBalanceAll() const
  {
    ENTER_FUNC();
    auto result = win_unlockedTokenBalanceAll(m_innerPtr);
    EXIT_FUNC();
    return result;

  }


  void WinWallet::setDefaultMixin(uint32_t arg)
  {
    ENTER_FUNC();
    EXIT_FUNC();
  }

  std::string WinWallet::signMessage(const std::string &message)
  {
    ENTER_FUNC();
    auto result = std::string();
    EXIT_FUNC();
    return result;
  }

  int WinWallet::status() const
  {
    ENTER_FUNC();
    EXIT_FUNC();
    return 0;
  }

  bool WinWallet::verifySignedMessage(const std::string &message, const std::string &addres, const std::string &signature) const
  {
    ENTER_FUNC();
    EXIT_FUNC();
    return false;
  }

  uint64_t WinWallet::blockChainHeight() const
  {
    ENTER_FUNC();
    auto result = win_blockChainHeight(m_innerPtr);
    EXIT_FUNC();
    return result;
  }

  void WinWallet::setListener(WinWalletListener * wltListener)
  {
    ENTER_FUNC();
    m_nativeListenerPtr = win_lstn_Create(static_cast<void *>(wltListener));
    ::win_lstn_setMoneySpent(m_nativeListenerPtr, &WinWalletListenerProxy::moneySpent);
    ::win_lstn_setMoneyReceived(m_nativeListenerPtr, &WinWalletListenerProxy::moneyReceived);
    ::win_lstn_setUnconfirmedMoneyReceived(m_nativeListenerPtr, &WinWalletListenerProxy::unconfirmedMoneyReceived);
    ::win_lstn_setTokensSpent(m_nativeListenerPtr, &WinWalletListenerProxy::tokensSpent);
    ::win_lstn_setTokenReceived(m_nativeListenerPtr, &WinWalletListenerProxy::tokensReceived);
    ::win_lstn_setUnconfirmedTokenReceived(m_nativeListenerPtr, &WinWalletListenerProxy::unconfirmedTokensReceived);
    ::win_lstn_setNewBlock(m_nativeListenerPtr, &WinWalletListenerProxy::newBlock);
    ::win_lstn_setUpdated(m_nativeListenerPtr, &WinWalletListenerProxy::updated);
    ::win_lstn_setRefreshed(m_nativeListenerPtr, &WinWalletListenerProxy::refreshed);
    ::win_SetListener(m_innerPtr, m_nativeListenerPtr);
    EXIT_FUNC();
  }

  WinPendingTransaction *WinWallet::createTransaction(const std::string &dst_addr, const std::string &payment_id, optional<uint64_t> value_amount, uint32_t mixin_count,
          PendingTransaction::Priority priority, uint32_t subaddr_account, std::set<uint32_t> subaddr_indices, const TransactionType tx_type)
  {
    ENTER_FUNC();

    std::cout << "WinWallet::createTransaction checkpoint 1" << std::endl;
    void* temp = win_createTransaction(m_innerPtr,dst_addr.c_str(), payment_id.c_str(), *value_amount, mixin_count, priority,
            0 /*subaddr_account*/, 0 /*subaddr_indices*/, static_cast<uint32_t>(tx_type));
    WinPendingTransaction *retValue = new WinPendingTransaction(temp);
    EXIT_FUNC();
    return retValue;
  }

  void WinWallet::startRefresh()
  {
    ENTER_FUNC();
    win_startRefresh(m_innerPtr);
    EXIT_FUNC();
  }

  void WinWallet::pauseRefresh()
  {
    ENTER_FUNC();
    EXIT_FUNC();
  }

  bool WinWallet::refresh()
  {
    ENTER_FUNC();
    auto result = static_cast<bool>(win_refresh(m_innerPtr));
    EXIT_FUNC();
    return result;
  }

  void WinWallet::refreshAsync()
  {
    ENTER_FUNC();

  }

  void WinWallet::setRefreshFromBlockHeight(uint64_t refresh_from_block_height)
  {
    ENTER_FUNC();
    win_setRefreshFromBlockHeight(m_innerPtr, refresh_from_block_height);
    EXIT_FUNC();
  }

  void WinWallet::setAutoRefreshInterval(int millis) {
    ENTER_FUNC();
    win_setAutoRefreshInterval(m_innerPtr, millis);
    EXIT_FUNC();
  }

  bool WinWallet::rescanBlockchain()
  {
    ENTER_FUNC();
    auto result = static_cast<bool>(win_rescanBlockchain(m_innerPtr));
    EXIT_FUNC();
    return result;
  }

  void WinWallet::rescanBlockchainAsync()
  {
    ENTER_FUNC();
    win_rescanBlockchainAsync(m_innerPtr);
    EXIT_FUNC();
  }


}
