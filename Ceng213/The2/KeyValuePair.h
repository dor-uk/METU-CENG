#ifndef KEYVALUEPAIR_H
#define KEYVALUEPAIR_H

// DO NOT CHANGE THIS FILE.

#include <iostream>

template<class K, class V>
class KeyValuePair {
public:
    KeyValuePair() {}

    KeyValuePair(const K &key) {
        this->key = key;
    }

    KeyValuePair(const K &key, const V &value) {
        this->key = key;
        this->value = value;
    }

    bool operator<(const KeyValuePair &rhs) const {
        return key < rhs.key;
    }

    bool operator>(const KeyValuePair &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const KeyValuePair &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const KeyValuePair &rhs) const {
        return !(*this < rhs);
    }

    bool operator==(const KeyValuePair &rhs) const {
        return key == rhs.key;
    }

    bool operator!=(const KeyValuePair &rhs) const {
        return !(rhs == *this);
    }

    const K &getKey() const {
        return key;
    }

    const V &getValue() const {
        return value;
    }

    void setValue(const V &value) {
        this->value = value;
    }

    friend std::ostream &operator<<(std::ostream &os, const KeyValuePair &pair) {
        os << "KeyValuePair(key: \"" << pair.key << "\", value: \"" << pair.value << "\")";
        return os;
    }

private:
    K key;
    V value;
};

#endif //KEYVALUEPAIR_H
