//
//  hash.cpp
//  HashTable
//
//  Created by Georgiy danielyan on 5/10/15.
//  Copyright (c) 2015 Goga. All rights reserved.
//
//  Hash Table Tutorial by PaulProgramming.
//  Followed along and replicated the code.
//  Hash Table and methods work properly.

#include "Hash.h"

#ifndef _HASH_CPP
#define _HASH_CPP

Hash::Hash()
{
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        HashTable[i] = new item;
        HashTable[i] ->name = "empty";
        HashTable[i] ->favoriteDrink = "empty";
        HashTable[i] ->next = nullptr;
    }
    
}

int Hash::HashFunction(string key){
    
    int index, hash = 0;
    
    for(int i = 0; i < key.length(); i++)
    {
        hash += (int)key[i];
    }
    cout << hash;
    index = hash % TABLE_SIZE;
    
    return index;
}

void Hash::addItem(string name, string drink)
{
    int index = HashFunction(name);
    
    if(HashTable[index] -> name == "empty")
    {
        HashTable[index] -> name = name;
        HashTable[index] -> favoriteDrink = drink;
    }
    else
    {
        item* ptr = HashTable[index];
        item* newItem = new item;
        
        newItem -> name = name;
        newItem -> favoriteDrink = drink;
        newItem -> next = nullptr;
        
        while(ptr -> next != nullptr)
        {
            ptr = ptr ->next;
        }
        ptr -> next = newItem;
    }
}

int Hash::numberOfItemsInIndex(int index)
{
    int count = 0;
    
    if(HashTable[index] -> name == "empty")
    {
        return count;
    }
    else
    {
        item* ptr = HashTable[index];
        while(ptr != nullptr)
        {
            count++;
            ptr = ptr -> next;
        }
    }
    
    return count;
}

int Hash::printTotalNumberOfItems()
{
    int numberOfItems = 0;
    
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        numberOfItems += numberOfItemsInIndex(i);
    }

    return numberOfItems;
}

void Hash::printTable()
{
    
    int number;
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        number = numberOfItemsInIndex(i);
        cout << "-------------------------\n";
        cout << "index = " << i << endl;
        cout << HashTable[i] -> name << endl;
        cout << HashTable[i] -> favoriteDrink << endl;
        cout << "# of items in bucket = " << number << endl;
        cout << "-------------------------\n";
    }
    
}

void Hash::printItemsInIndex(int index)
{
    item* ptr = HashTable[index];
    
    if(ptr -> name == "empty")
        cout << "Index " << index << " is Empty." << endl;
    else{
        cout << "Index " << index << " Contains the following: \n";
        
        while(ptr != nullptr)
        {
            cout << "--------------------\n";
            cout << ptr -> name << endl;
            cout << ptr -> favoriteDrink << endl;
            cout << "--------------------\n";
            
            ptr = ptr -> next;
        }
    }
    
}

void Hash::findDrink(string name)
{
    int index = HashFunction(name);
    bool foundName = false;
    string drink;
    
    item* ptr = HashTable[index];
    while(ptr != nullptr)
    {
        if(ptr -> name == name)
        {
            foundName = true;
            drink = ptr -> favoriteDrink;
        }
        
        ptr = ptr -> next;
    }
    
    if(foundName == true)
    {
        cout << "Favorite drink " << drink << endl;
    }
    else
    {
        cout << name << " info was not found in the hash table." << endl;
    }
    
}

void Hash::removeItem(string name)
{
    int index = HashFunction(name);
    
    item* delPtr;
    item* ptr1;
    item* ptr2;
    
    //Case 1: the index/bucket is empty.
    if(HashTable[index] -> name == "empty" && HashTable[index] -> favoriteDrink == "empty")
    {
        cout << name << "was not found in the hash table." << endl;
    }
    //Case 2: only a 1 item in the index/bucket and that item has a matching name.
    else if(HashTable[index] -> name == name && HashTable[index] -> next == nullptr)
    {
        HashTable[index] -> name = "empty";
        HashTable[index] -> favoriteDrink = "empty";
        
        cout << name << " was removed from the hash table." << endl;
    }
    //Case 3: match is located in the first item but there are some more stuff in the index/bucket.
    else if(HashTable[index] -> name == name && HashTable[index] -> next != nullptr)
    {
        delPtr = HashTable[index];
        HashTable[index] = HashTable[index] -> next;
        delete delPtr;
        delPtr = nullptr;
        cout << name << " was removed from the hash table." << endl;
        
    }
    //Case 4: the bucket contains some items but first item is not a match.
    else
    {
        ptr2 = HashTable[index];
        ptr1 = HashTable[index] -> next;
        
        while(ptr1 != nullptr && ptr1 -> name != name)
        {
            ptr2 = ptr1;
            ptr1 = ptr1 -> next;
        }
        //Case 4.1: No match.
        if(ptr1 == nullptr)
        {
            cout << name << " was not found in the hash table." << endl;
        }
        //Case 4.2: Find a match in the additional items within the bucket.
        else
        {
            delPtr = ptr1;
            ptr1 = ptr1 -> next;
            ptr2 -> next = ptr1;
            
            delete delPtr;
            delPtr = nullptr;
            cout << name << " was removed from the hash table." << endl;
        }
    }
}

#endif