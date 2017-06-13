/**
 * @file   Wallet.cpp
 * @brief  Wallet
 * @author Maeda Takumi
 */
#include "Wallet.h"

const int Wallet::MAX_MONEY(9999999);

Wallet::Wallet() :
mMoney(0) {
}

void Wallet::operator+=(const int& aMoney) {
    mMoney += aMoney;
    mMoney = Math::min(mMoney, MAX_MONEY);
}

void Wallet::operator-=(const int& aMoney) {
    mMoney -= aMoney;
    mMoney = Math::max(mMoney, 0);
}

const int& Wallet::money() const {
    return mMoney;
}

