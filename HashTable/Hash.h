//
//  hash.h
//  HashTable
//
//  Created by Georgiy danielyan on 5/10/15.
//  Copyright (c) 2015 Goga. All rights reserved.
//
//  Hash Table Tutorial by PaulProgramming.
//  Followed along and replicated the code.
//  Hash Table and methods work properly.

#include <string>
#include <stdio.h>
#include <cstdlib>
#include <iostream>

using namespace std;

#ifndef _HASH_H
#define _HASH_H

const int TABLE_SIZE = 4;

class Hash
{
    
private:
    struct item{
        string name;
        string favoriteDrink;
        item* next;
    };
    
    item* HashTable[TABLE_SIZE];
    
public:
    Hash();
    int HashFunction(string key);
    void addItem(string name, string drink);
    int numberOfItemsInIndex(int index);
    int printTotalNumberOfItems();
    void printTable();
    void printItemsInIndex(int index);
    void findDrink(string drink);
    void removeItem(string name);
    
}; // end Hash

#endif
