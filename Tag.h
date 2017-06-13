/**
 * @file   Tag.cpp
 * @brief  Tag
 * @author Maeda Takumi
 */
#ifndef TAG_H
#define TAG_H

/**
 * @brief  \~english  Tag
 * @brief  \~japanese 値札
 * @author \~ Maeda Takumi
 */
class Tag {
private:
    /* 値段     */ int mValue;
public:
    /**
     * \~english
     * @param aValue value
     * \~japanese
     * @param aValue 価値
     */
    Tag(const int& aValue);
    virtual ~Tag() = default;
};

#endif /* TAG_H */

