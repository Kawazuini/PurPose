/**
 * @file   NumberSelector.cpp
 * @brief  NumberSelector
 * @author Maeda Takumi
 */
#ifndef NUMBERSELECTOR_H
#define NUMBERSELECTOR_H

#include "Command.h"

/**
 * @brief  \~english  Number Selector
 * @brief  \~japanese ナンバーセレクタ
 * @author \~ Maeda Takumi
 */
class NumberSelector final : public Command {
public:
    /**
     * @brief \~english  number selector processing function
     * @brief \~japanese ナンバーセレクタ処理関数
     */
    using NumberSelectorFunction = void (GameManager::*)(const int& aNumber);
private:
    /* カウンタ文字列 */ static const List<String> COUNT_TEXT;
    /* セレクト最大値 */ int mMax;
    /* セレクト最小値 */ int mMin;
    /* 決定時処理関数 */ NumberSelectorFunction mSelect;
public:
    /**
     * \~english
     * @param aGameManager target of command
     * @param aTitle       title
     * @param aMax         max of counter
     * @param aMin         min of counter
     * @param aSelect      execution function when selecting
     * \~japanese
     * @param aGameManager コマンド対象
     * @param aTitle       タイトル
     * @param aMax         カウンタ最大値
     * @param aMin         カウンタ最小値
     * @param aSelect      選択時実行関数
     */
    NumberSelector(
            GameManager& aGameManager,
            const String& aTitle,
            const int& aMax,
            const int& aMin,
            const NumberSelectorFunction& aSelect
            );
    virtual ~NumberSelector() = default;

    /**
     * @brief \~english  drawing processing
     * @brief \~japanese 描画処理
     */
    void draw(Device& aDevice) override;

    /**
     * \~english
     * @brief change selected Command.
     * @param aAmount change amount
     * \~japanese
     * @brief 選択肢を変更します。
     * @param aAmount 選択変更量
     */
    void changeCommand(const int& aAmount) override;

    /**
     * @brief \~english  do select function.
     * @brief \~japanese 選択時関数を実行します。
     */
    void choose() override;

    /**
     * @brief \~english  cancel to selector.
     * @brief \~japanese セレクタをキャンセルします。
     */
    void cancel() override {
    };
};

#endif /* NUMBERSELECTOR_H */

