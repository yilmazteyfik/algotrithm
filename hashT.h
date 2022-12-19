#ifndef SON_HASHT_H
#define SON_HASHT_H
#endif //SON_HASHT_H

#include <fstream>
#include <cmath>
#include <string>
#include <ctime>
#include "utilities.h"

static const int PRIME_const = 31;

struct element {
    int count{};
    std::string word;
    struct element& operator +=(const element& otherElem);
    bool operator ==(const element& otherElem) const;
    bool operator !=(const element& otherElem) const;
};

struct element& element::operator+=(const element& otherElem) {
    this->count = this->count + otherElem.count;
    return *this;
}

bool element::operator==(const element& otherElem) const {
    if (this->word == otherElem.word) return true;
    else return false;
}

bool element::operator!=(const element& otherElem) const {
    if (this->word == otherElem.word) return false;
    else return true;
}

std::ostream& operator<<(std::ostream& os, const element& elem) {
    os << elem.word << " " << elem.count;
    return os;
}


// WE MADE USE OF LECTURE NOTES OF Çiğdem Eriş. THANK YOU HOCAM

class hashT {
public:
    int hashFunction(const std::string& key) const;
    void insert(int hashIndex, const element& rec);
    void search(int hashIndex, const element& rec, bool& isFound) const;
    void selection();
    explicit hashT(int size = 101);
    ~hashT();
protected:
    element* hTable = (element*)(calloc(180001, sizeof(element)));
    int* indexStatusList;
    int length;
    int HTSize;
};


hashT::hashT(int size) {
    if (size < 1){
        std::cerr << "Size should be positive." << std::endl;
        exit(0);
    }
    HTSize = size;
    hTable = new element[HTSize];
    indexStatusList = new int[HTSize];
    for (int i = 0; i < HTSize; ++i) {
        indexStatusList[i] = 0;
    }
    length = 0;
}


hashT::~hashT() {
    delete[]hTable;
    delete[]indexStatusList;
}

void hashT::insert(int hashIndex, const element& rec) {
    int pCount = 0;
    int inc = 1;
    //that for collusion
    while (indexStatusList[hashIndex] == 1 && hTable[hashIndex] != rec && pCount < HTSize / 2) {
        pCount++;
        hashIndex = (hashIndex + inc) % HTSize;
        inc = inc + 2;
    }
    if (indexStatusList[hashIndex] != 1) {
        hTable[hashIndex] = rec;
        indexStatusList[hashIndex] = 1;

        length++;
    }
    else if (hTable[hashIndex] == rec) {
        hTable[hashIndex] += rec;
    }
    else std::cerr << "Hash table is full. Unable to resolve collision" << std::endl;

}

void hashT::search(int hashIndex, const element& rec, bool& isFound) const {
    int pCount = 0;
    int inc = 1;
    while (indexStatusList[hashIndex] != 0 && hTable[hashIndex] != rec && pCount < HTSize / 2) {
        pCount++;
        hashIndex = (hashIndex + inc) % HTSize;
        inc += 2;
    }
    if (indexStatusList[hashIndex] == 1 && hTable[hashIndex] == rec)
        isFound = true;
    else isFound = false;
}

int hashT::hashFunction(const std::string& key) const {
    size_t sum = 0;
    for (int i = 0; i < key.length(); i++)
        sum += (key[i] * (int)pow(PRIME_const, i)) % HTSize;
    return (int)(sum % HTSize);

}

void hashT::selection(){
    int arr[10];
    for (int i = 0; i < 10; ++i) {
        int max = i;
        for (int j = i + 1; j < HTSize; ++j)
            if (indexStatusList[j] > 0 && hTable[j].count > hTable[max].count)
                max = j;
        std::cout << hTable[max] << std::endl;
        indexStatusList[max] = 0;
        arr[i] = max;
    }
    int i = 0;
    while (i < 10)
    {
        indexStatusList[arr[i]] = 1;
        i++;
    }
}
