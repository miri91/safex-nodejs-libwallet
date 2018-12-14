#include "wallettasks.h"

#include "wallet.h"
#include "pendingtransaction.h"


#include "safexnativewallet.h"
#include "walletlog.h"


namespace exawallet {

using namespace v8;

std::string CreateWalletTask::doWork() {
    ENTER_FUNC();
    auto manager = SafexNativeWalletManagerFactory::getWalletManager();
    if (manager->walletExists(args_.path)) {
        return "Wallet already exists: " + args_.path;
    }

    wallet_ = manager->createWallet(args_.path, args_.password, args_.language, args_.nettype);

    if (!wallet_) {
        return "WalletManager returned null wallet pointer";
    }

    if (!wallet_->errorString().empty()) {
        return wallet_->errorString();
    }

    if (!wallet_->init(args_.daemonAddress)) {
        return "Couldn't init wallet";
    }

    wallet_->setTrustedDaemon(true);
    wallet_->startRefresh();
    EXIT_FUNC();
    return {};
}

Local<Value> CreateWalletTask::afterWork(std::string& error) {
    ENTER_FUNC();
    EXIT_FUNC();
    return Wallet::NewInstance(wallet_);
}

std::string CreateWalletFromKeysTask::doWork() {
    ENTER_FUNC();
  auto manager = SafexNativeWalletManagerFactory::getWalletManager();
  if (manager->walletExists(args_.path)) {
    return "Wallet already exists: " + args_.path;
  }

  wallet_ = manager->createWalletFromKeys(args_.path, args_.password, args_.language, args_.nettype, args_.restoreHeight, args_.addressString, args_.viewKeyString, args_.spendKeyString);


  if (!wallet_) {
    return "WalletManager returned null wallet pointer";
  }

  if (!wallet_->errorString().empty()) {
    return wallet_->errorString();
  }

  if (!wallet_->init(args_.daemonAddress)) {
    return "Couldn't init wallet";
  }

  wallet_->setTrustedDaemon(true);
  wallet_->startRefresh();
  EXIT_FUNC();
  return {};
}

Local<Value> CreateWalletFromKeysTask::afterWork(std::string& error) {
    ENTER_FUNC();
    EXIT_FUNC();
  return Wallet::NewInstance(wallet_);
}

std::string OpenWalletTask::doWork() {
    auto manager = SafexNativeWalletManagerFactory::getWalletManager();
    if (!manager->walletExists(args_.path)) {
        return "wallet does not exist: " + args_.path;
    }

    wallet_ = manager->openWallet(args_.path, args_.password, args_.nettype);

    if (!wallet_) {
        return "WalletManager returned null wallet pointer";
    }

    if (!wallet_->errorString().empty()) {
        return wallet_->errorString();
    }

    if (!wallet_->init(args_.daemonAddress)) {
        return "Couldn't init wallet";
    }

    //set refresh height as latest block wallet has seen - 1 day
    uint64_t currentHeight = wallet_->blockChainHeight();
    wallet_->setRefreshFromBlockHeight(currentHeight - 720 > 0 ? currentHeight - 720 : 0);

    wallet_->setTrustedDaemon(true);
    wallet_->startRefresh();
    EXIT_FUNC();
    return {};
}

Local<Value> OpenWalletTask::afterWork(std::string& error) {
    ENTER_FUNC();
    EXIT_FUNC();
    return Wallet::NewInstance(wallet_);
}

std::string CloseWalletTask::doWork() {
    ENTER_FUNC();
    auto manager = SafexNativeWalletManagerFactory::getWalletManager();
    manager->closeWallet(wallet_, store_);
    EXIT_FUNC();
    return {};
}

Local<Value> CloseWalletTask::afterWork(std::string& error) {
    ENTER_FUNC();
    EXIT_FUNC();
    return Nan::Undefined();
}

std::string RecoveryWalletTask::doWork() {
    ENTER_FUNC();
    auto manager = SafexNativeWalletManagerFactory::getWalletManager();

    wallet_ = manager->recoveryWallet(args_.path,
                                       args_.password,
                                       args_.mnemonic,
                                       args_.nettype,
                                       args_.restoreHeight);

    if (!wallet_) {
        return "WalletManager returned null wallet pointer";
    }

    if (!wallet_->errorString().empty()) {
        return wallet_->errorString();
    }
    
    if (!wallet_->init(args_.daemonAddress)) {
        return "Couldn't init wallet";
    }

    wallet_->setTrustedDaemon(true);
    wallet_->startRefresh();
    EXIT_FUNC();
    return {};
}

Local<Value> RecoveryWalletTask::afterWork(std::string& error) {
    ENTER_FUNC();
    EXIT_FUNC();
    return Wallet::NewInstance(wallet_);
}

std::string StoreWalletTask::doWork() {
    ENTER_FUNC();
    if (!wallet_->store(wallet_->path())) {
        std::cout << "Error storing wallet path:" << wallet_->path() << std::endl;
        return "Couldn't store wallet";
    }

    EXIT_FUNC();
    return {};
}
Local<Value> StoreWalletTask::afterWork(std::string& error) {
    ENTER_FUNC();
    EXIT_FUNC();
    return Nan::Undefined();
}

std::string CreateTransactionTask::doWork() {
    ENTER_FUNC();
    //std::cout << "CreateTransactionTask::doWork amount=" <<  args_.amount << " tx_type=" << static_cast<int>(args_.tx_type) << std::endl;

    transaction_ = wallet_->createTransaction(args_.address, args_.paymentId, args_.amount, args_.mixin, args_.priority, 0 /*subaddr account*/,{} /*subaddr indices*/, args_.tx_type);
    if (!wallet_->errorString().empty()) {
        return wallet_->errorString();
    }

    EXIT_FUNC();
    return {};
}

Local<Value> CreateTransactionTask::afterWork(std::string& error) {
    ENTER_FUNC();
    return PendingTransaction::NewInstance(transaction_);
}

std::string CommitTransactionTask::doWork() {
    if (!transaction_->commit()) {
        return "Couldn't commit transaction: " + transaction_->errorString();
    }
    EXIT_FUNC();

    return {};
}

Local<Value> CommitTransactionTask::afterWork(std::string& error) {
    ENTER_FUNC();
    EXIT_FUNC();
    return Nan::Undefined();
}

}
