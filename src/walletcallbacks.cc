#include "asynccallback.h"
#include "walletlog.h"

namespace exawallet
{

  void Wallet::newBlock(uint64_t height)
  {
    ENTER_FUNC();
    AsyncCallback<uint64_t> *async = constructAsyncCallback<uint64_t>(this, "newBlock");
    async->param = height;
    async->Enqueue();
    EXIT_FUNC();
  }

  void Wallet::refreshed()
  {
    ENTER_FUNC();
    AsyncCallback<void> *async = constructAsyncCallback<void>(this, "refreshed");
    async->Enqueue();
    EXIT_FUNC();
  }

  void Wallet::moneySpent(const std::string &tx, uint64_t amount)
  {
    ENTER_FUNC();
    AsyncCallback<TransactionAmount> *async = constructAsyncCallback<TransactionAmount>(this, "moneySpent");
    async->param = TransactionAmount{tx, std::to_string(amount)};
    async->Enqueue();
    EXIT_FUNC();
  }

  void Wallet::moneyReceived(const std::string &tx, uint64_t amount)
  {
    ENTER_FUNC();
    AsyncCallback<TransactionAmount> *async = constructAsyncCallback<TransactionAmount>(this, "moneyReceived");
    async->param = TransactionAmount{tx, std::to_string(amount)};
    async->Enqueue();
    EXIT_FUNC();
  }

  void Wallet::unconfirmedMoneyReceived(const std::string &tx, uint64_t amount)
  {
    ENTER_FUNC();
    AsyncCallback<TransactionAmount> *async = constructAsyncCallback<TransactionAmount>(this, "unconfirmedMoneyReceived");
    async->param = TransactionAmount{tx, std::to_string(amount)};
    async->Enqueue();
    EXIT_FUNC();
  }

  void Wallet::tokensSpent(const std::string &tx, uint64_t token_amount)
  {
    ENTER_FUNC();
    AsyncCallback<TransactionAmount> *async = constructAsyncCallback<TransactionAmount>(this, "tokensSpent");
    async->param = TransactionAmount{tx, std::to_string(token_amount)};
    async->Enqueue();
    EXIT_FUNC();
  }

  void Wallet::tokensReceived(const std::string &tx, uint64_t token_amount)
  {
    ENTER_FUNC();
    AsyncCallback<TransactionAmount> *async = constructAsyncCallback<TransactionAmount>(this, "tokensReceived");
    async->param = TransactionAmount{tx, std::to_string(token_amount)};
    async->Enqueue();
    EXIT_FUNC();
  }

  void Wallet::unconfirmedTokensReceived(const std::string &tx, uint64_t token_amount)
  {
    ENTER_FUNC();
    AsyncCallback<TransactionAmount> *async = constructAsyncCallback<TransactionAmount>(this, "unconfirmedTokensReceived");
    async->param = TransactionAmount{tx, std::to_string(token_amount)};
    async->Enqueue();
    EXIT_FUNC();
  }

  void Wallet::updated()
  {
    ENTER_FUNC();
    AsyncCallback<void> *async = constructAsyncCallback<void>(this, "updated");
    async->Enqueue();
    EXIT_FUNC();
  }

} //namespace exawallet
