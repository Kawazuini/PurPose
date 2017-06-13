/**
 * @file   Wallet.h
 * @brief  Wallet
 * @author Maeda Takumi
 */
#ifndef WALLET_H
#define WALLET_H

#include "main.h"

/**
 * @brief  \~english  money manager
 * @brief  \~japanese お金管理
 * @author \~ Maeda Takumi
 */
class Wallet {
public:
    /**
     * @brief \~english  max of possession amount
     * @brief \~japanese 所持可能金額上限
     */
    static const int MAX_MONEY;
private:
    /* お金 */ int mMoney;
public:
    Wallet();
    virtual ~Wallet() = default;

    /**
     * \~english
     * @brief income
     * @param aMoney money of increase
     * \~japanese
     * @brief 収入
     * @param aMoney 増加額
     */
    void operator+=(const int& aMoney);
    /**
     * \~english
     * @brief spending
     * @param aMoney money of decrease
     * \~japanese
     * @brief 支出
     * @param aMoney 減少額
     */
    void operator-=(const int& aMoney);

    /**
     * \~english
     * @brief  get possession amount.
     * @return possession amount
     * \~japanese
     * @brief  所持金額を取得します。
     * @return 所持金額
     */
    const int& money() const;
};

#endif /* WALLET_H */

