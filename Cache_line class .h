//
//  cache.h
//  HW6
//
//  Created by Ibrahim Saeed on 12/11/12.
//  Copyright (c) 2012 Ibrahim Saeed. All rights reserved.
//


#include <vector>
#include <string>
#include <iostream>

using namespace std;


#ifndef CACHELINE_H
#define CACHELINE_H

class cacheline{
public:
    
    
    //constructor
    cacheline ();
    
    
    
    
  
    
    void set_tag(string n);
    void set_tag_2(string n);
    void set_tag_3(string n);
    void set_tag_4(string n);
    void set_validity(bool y);
    void set_index(string n); //maybe you want these to be intes... check later.
    void set_LRU_tag(int n);
    void set_LRU_tag_2(int n);
    void set_LRU_tag_3(int n);
    void set_LRU_tag_4(int n);
    //accessor functions to access my data memebers
    
    
    string Get_tag() const;
    string Get_tag_2() const;
    string Get_tag_3() const;
    string Get_tag_4() const;
    string Get_index() const;
    
    
    bool    Is_valid() const;
    int Get_LRU_tag() const;
    int Get_LRU_tag_2() const;
    int Get_LRU_tag_3() const;
    int Get_LRU_tag_4() const;
    
    
    
    
private:
    
    
    
    string tag;
    string tag_2;
    string tag_3;
    string tag_4;
    string index;
    string off_set;
    bool validity;
    int LRU_tag;
    int LRU_tag_2;
    int LRU_tag_3;
    int LRU_tag_4;
    

    
};


#endif /* defined(__HW6__cache__) */
