Cache_simulater
===============

A cache simulator I built for a class. Simulates a direct-mapped cache, set associative 2 - way, and 4 - way. 

    //
//  main.cpp
//  HW6
//
//  Created by Ibrahim Saeed on 12/6/12.
//  Copyright (c) 2012 Ibrahim Saeed. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include "cache.h"



using namespace std;



//function that turns a hex character into a 4-bit string in binary.


    string hexBinary_4bit(char hex_char){

        
        
        
        switch (hex_char)
        
        {
           case '0':
            {
                    return "0000";
                
            }
            case '1':
            {
                    return "0001";
                
            }
            case '2':
            {
                return "0010";
                
            }
            case '3':
            {
                return "0011";
                
            }
                case '4':
            {
                return "0100";
            }
        
            case '5':
            {
                return "0101";
            }
            case '6':
            {
                return "0110";
            }
            
            case '7':
            {
                return "0111";
            }
            case '8':
            {
                return "1000";
            }
            case '9':
            {
                return "1001";
            }
            case 'a':
            {
                return "1010";
            }
            case 'b':
            {
                return "1011";
            }
            case 'c':
            {
                return "1100";
            }
            case 'd':
            {
                return "1101";
            }
            case 'e':
            {
                return "1110";
            }
            case 'f':
            {
                return "1111";
            }
            default:
            {
                return "----";
            }
        
        }
        
    }



///function that turns a hexadecimal string to a 32 bit tring of binary numbers. 

        string hexBinary_32bit (string hexaString){


            string result; 
            
            

            for (int i = 0; i < hexaString.size(); i++){
                
                
                result = result + hexBinary_4bit(hexaString[i]);
                
                
            }
            
            return result; 
            
        
        }

//function that returns log of base 2

        
        int log_base_2(int num){

            int count = 1;
            
            if (num == 1) {
                
                count = 0;
                return count; 
            }
            
            
                else {
                            while (num / 2 > 1) {
                
                                num = num/2;
                                count ++;
                
                            }
                
                return count;
                }
                
            }
            

//function that takes a binary string and returns decimal number. integer.




    int binay_to_base10(string binAry){
        
        
        int sum;
        int size = (binAry.size() - 1);
        for (int i = 0; i < binAry.size(); i++){
            
            if (binAry[i] == '1') 
                
                
                sum += pow(2.0, (double)(size-i));
            
            else
                
                sum = sum + 0;
                
            }
            
        return sum; 
        
        }
    
//----------------------------------------------------------------------------------------------------
        
void Direct_cacheSimulator(ifstream& file_data2, int index_size, int offset_Size, vector<cacheline> El_cache){
    
    
    
    //For Direct Mapped Caches,
    // my ADT 'cacheline' has data members tag, index, offset, 
    
    
    
    
    
    
    
    
    //Throw out the junk. 
    string useless;
    
    
    
    string hex_address;
    string bin_address;
    string index_str;
    string tag_str; 
    double cache_pos;
    
    double hit_count = 0.0;
    double miss_count = 0.0;
    
    //Every run through this while loop deals with ONE address from the file. 
    
    while (file_data2 >> hex_address) {
        
        //gotta throw out junk!
        file_data2 >> useless;
        
        
        //The Address is currently in Hexadecimal. 
        
        
            
        //Get Hex string into a string of binary.
        
        bin_address = hexBinary_32bit(hex_address);
        
        //Get the Index string from the 32 bit string. 
        
        index_str = bin_address.substr((31 - index_size - offset_Size), index_size);
    
        // Get the Tag string from the 32 bit string. 
        tag_str = bin_address.substr(0, (bin_address.size() - index_size - offset_Size));
        
        
        //Since Index string is just a Binary string, I change it to a decimal number so I can use it
        //as a position in my vector of cachelines. 
        
        
        cache_pos = binay_to_base10(index_str);
    
        // Setting a cacheline 'Current' to the 'index' position in the Cache. 
        
        cacheline current = El_cache[cache_pos];
        
        //Hit or Miss?
        //If it's a miss, we set the tag of the CURRENT address to the tag in the spot of the Cacheline.
        //When it's a compulsory miss, I have to make it valid.
        
        if   (current.Is_valid() == true) {
            
            if (tag_str == current.Get_tag()) 
                //hit
                hit_count = hit_count +1;
                
            else{
                    
                    miss_count = miss_count + 1; 
                    current.set_tag(tag_str); //set tag of cache line to the cache line of current address. 
            }
        }
            
            
        else {
               //not valid, so it's a miss. 
            miss_count = miss_count + 1; 
            //make it vaild
            current.set_validity(true);
            current.set_tag(tag_str); //set tag of cache line to the cache line of current address.

                
        }
        El_cache[cache_pos]=current;
    }// end the while loop
    
    
    
    
    cout << "hits = " << hit_count << endl;
    cout << "Misses = " << miss_count << endl;
    double hit_rate = (hit_count / (hit_count + miss_count)) * 100.0;
    cout << "Hit Rate : " << hit_rate << "%" << endl; 
    
}
        
        
//---------------------------------------------------------------------------------------------------

void Set_2Way_cacheSimulator(ifstream& file_data2, int index_size, int offset_Size, vector<cacheline> El_cache){
    
    string useless;
    
    int run_counter = 1; //for LRU purposes.
    
    string hex_address;
    string bin_address;
    string index_str;
    string tag_str;
    double cache_pos;
    
    double hit_count = 0;
    double miss_count = 0;
    
    
    
    while (file_data2 >> hex_address) {
        
        file_data2 >> useless;
        
        bin_address = hexBinary_32bit(hex_address);
        
        index_str = bin_address.substr((31 - index_size - offset_Size), index_size);
        
        
        tag_str = bin_address.substr(0, (bin_address.size() - index_size - offset_Size));
        
        
        cache_pos = binay_to_base10(index_str);
        
        cacheline current;
        
        current = El_cache[cache_pos];
    
        
        if   (current.Is_valid() == true) {
            
            
                    //Have to check if there's a match with either of the tags in the Cacheline. 
                    if (tag_str == current.Get_tag() ||tag_str == current.Get_tag_2()) {
                            //hit
                        hit_count = hit_count +1;
                    }
            
                    else {
                
                        miss_count = miss_count + 1;
            
                        //here comes the LRU part. Which tag do I set current address to. 
                        //LRU is a data member on the Cacheline ADT. 
            
                            if (current.Get_LRU_tag() <= current.Get_LRU_tag_2()){
            
                                //means tag 1 was used less recently then tag 2.
                                //throw address into tag 1.
                                current.set_tag(tag_str); //set tag of cache line to the cache line of current address.
                                current.set_LRU_tag(run_counter); // Set LRU at this tag to the run_counter to keep track of
                                                                 //  when we used it. 
                            }
                
                            else {
                    
                                current.set_tag_2(tag_str);
                                current.set_LRU_tag_2(run_counter);
                    
                            }
            
                
                
                    }
        
        }
        else {
                    
            miss_count = miss_count + 1;
            current.set_validity(true);
            
            
            if (current.Get_LRU_tag() <= current.Get_LRU_tag_2()){
                
                //means tag 1 was used less recently then tag 2.
                //throw address into tag 1.
                current.set_tag(tag_str); //set tag of cache line to the cache line of current address.
                current.set_LRU_tag(run_counter);
            }
            
            else {
                
                current.set_tag_2(tag_str);
                current.set_LRU_tag_2(run_counter);
                
            }

            
            
            
        }
        
    
       
        El_cache[cache_pos]= current;
        run_counter ++;//Counter for the run through this While loop. 
        
    } // end the while loop
    
    
    
    cout << "hits = " << hit_count << endl;
    cout << "Misses = " << miss_count << endl;
    double hit_rate = (hit_count / (hit_count + miss_count)) * 100.0;
    cout << "Hit Rate : " << hit_rate << "%" << endl;
    
    
}


//---------------------------------------------------------------------------------------------------
//####################################################################################################


void Set_4Way_cacheSimulator(ifstream& file_data2, int index_size, int offset_Size, vector<cacheline> El_cache){
    
    string useless;
    
    int run_counter = 1; //for LRU purposes.
    
    string hex_address;
    string bin_address;
    string index_str;
    string tag_str;
    double cache_pos;
    double hit_count = 0;
    double miss_count = 0;
    
    
    
    while (file_data2 >> hex_address) {
        
       
        file_data2 >> useless;
        
        
        bin_address = hexBinary_32bit(hex_address);
        
        index_str = bin_address.substr((31 - index_size - offset_Size), index_size);
        
        
        tag_str = bin_address.substr(0, (bin_address.size() - index_size - offset_Size));
        
        
        
        cache_pos = binay_to_base10(index_str);
       
        
        cacheline current;//starting with invalid position.
        
        current = El_cache[cache_pos];
        
                
        //Very Similar idea from the previous function, except there are four tags instead of two
        // and four places to compare before we decide where to dump an address. 
        
        
        if   (current.Is_valid() == true) {
            
            if (tag_str == current.Get_tag()    || tag_str == current.Get_tag_2() ||
                tag_str == current.Get_tag_3()  || tag_str == current.Get_tag_3()) {
                
                //hit
                hit_count = hit_count +1;
            }
            
            else {
                
                miss_count = miss_count + 1;
                
                //here comes the LRU part. Which tag do I set current address to.
                
                
              
                if ((current.Get_LRU_tag() <= current.Get_LRU_tag_2()) &&
                    (current.Get_LRU_tag() <= current.Get_LRU_tag_3()) &&
                    (current.Get_LRU_tag() <= current.Get_LRU_tag_4())) {
                
                
                        current.set_tag(tag_str); //set tag of cache line to the cache line of current address.
                        current.set_LRU_tag(run_counter);
                }
                
                
                
                
                if ((current.Get_LRU_tag_2() <= current.Get_LRU_tag() &&
                    (current.Get_LRU_tag_2() <= current.Get_LRU_tag_3()) &&
                    (current.Get_LRU_tag_2() <= current.Get_LRU_tag_4()))) {
                    
                    
                    current.set_tag_2(tag_str); //set tag of cache line to the cache line of current address.
                    current.set_LRU_tag_2(run_counter);
                }
                
                
                
                if ((current.Get_LRU_tag_3() <= current.Get_LRU_tag() &&
                     (current.Get_LRU_tag_3() <= current.Get_LRU_tag_2()) &&
                     (current.Get_LRU_tag_3() <= current.Get_LRU_tag_4()))) {
                    
                    
                    current.set_tag_3(tag_str); //set tag of cache line to the cache line of current address.
                    current.set_LRU_tag_3(run_counter);
                }
                
                
                
                if ((current.Get_LRU_tag_4() <= current.Get_LRU_tag() &&
                    (current.Get_LRU_tag_4() <= current.Get_LRU_tag_2()) &&
                    (current.Get_LRU_tag_4() <= current.Get_LRU_tag_3()))) {
                    
                    
                    current.set_tag_4(tag_str); //set tag of cache line to the cache line of current address.
                    current.set_LRU_tag_4(run_counter);
                }
                
                
                
            }
            
        }
        else {
            
            miss_count = miss_count + 1;
            current.set_validity(true);
            
            //here comes the LRU part. Which tag do I set current address to.
            
            
            if ((current.Get_LRU_tag() <= current.Get_LRU_tag_2()) &&
                (current.Get_LRU_tag() <= current.Get_LRU_tag_3()) &&
                (current.Get_LRU_tag() <= current.Get_LRU_tag_4())) {
                
                
                current.set_tag(tag_str); //set tag of cache line to the cache line of current address.
                current.set_LRU_tag(run_counter);
            }
            
            
            
            
            if ((current.Get_LRU_tag_2() <= current.Get_LRU_tag() &&
                 (current.Get_LRU_tag_2() <= current.Get_LRU_tag_3()) &&
                 (current.Get_LRU_tag_2() <= current.Get_LRU_tag_4()))) {
                
                
                current.set_tag_2(tag_str); //set tag of cache line to the cache line of current address.
                current.set_LRU_tag_2(run_counter);
            }
            
            
            
            if ((current.Get_LRU_tag_3() <= current.Get_LRU_tag() &&
                 (current.Get_LRU_tag_3() <= current.Get_LRU_tag_2()) &&
                 (current.Get_LRU_tag_3() <= current.Get_LRU_tag_4()))) {
                
                
                current.set_tag_3(tag_str); //set tag of cache line to the cache line of current address.
                current.set_LRU_tag_3(run_counter);
            }
            
            
            
            if ((current.Get_LRU_tag_4() <= current.Get_LRU_tag() &&
                 (current.Get_LRU_tag_4() <= current.Get_LRU_tag_2()) &&
                 (current.Get_LRU_tag_4() <= current.Get_LRU_tag_3()))) {
                
                
                current.set_tag_4(tag_str); //set tag of cache line to the cache line of current address.
                current.set_LRU_tag_4(run_counter);
            }
            
            
            
            
        }
        
        
        
        El_cache[cache_pos]= current;
        run_counter ++;
        
    } // end the while loop
    
    
    
    cout << "hits = " << hit_count << endl;
    cout << "Misses = " << miss_count << endl;
    double hit_rate = (hit_count / (hit_count + miss_count)) * 100.0;
    cout << "Hit Rate : " << hit_rate << "%" << endl;
    
    
}














//function to print date off the file.

void print_file(ifstream& data2){
    string crap;
    string file_data;
    while (data2 >> file_data){
        data2 >> crap;
        cout << file_data << endl;
            
    }
    
}

            
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////

        

int main()
{

    

    
    // ask user for cache and line size
    
    int cache_size;
    cout << "What is your Cache size? Please stick with bytes that are powers of 2. " << endl;
    cin >> cache_size;
    
    
    int line_size;
    cout << "What is the line size in your Cache?" << endl;
    cin >> line_size;
    
    
    
    cout << "Press '1' for Direct Mapped, '2' for Set 2 way and '3' for Set 4 way. " << endl;
    char Cache_type;
    cin >> Cache_type;
    
    
    //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // Direct-Mapped. 
    
    
    
    if (Cache_type == '1') {
        
        
        int num_lines = (cache_size/line_size);// for direct mapped
        
        cout << "Number of lines is " << num_lines << endl;
        
        int index_size = log_base_2(num_lines);
        cout << "Size of index is " << index_size << " bits" << endl;
        
        
        
        int off_set_size = log_base_2(line_size);
        cout << "Size of offset is " << off_set_size << " bits" << endl;
        
        
        
        //declare cache.
        vector<cacheline> cache;
        //cache.resize(num_lines); //for direct map.
        
        cache.resize(num_lines);
        
        
        
        cout << "Enter file name: ";
        
        
        
        
        ifstream address;
        string file_name;
        cin >> file_name;
        //   address.open("/Users/ibrahimsaeed/Desktop/HW6/HW6/bzip.trace");
        //Users/ibrahimsaeed/Desktop/HW6/HW6/blarg.txt
        
        
        address.open(file_name.data());
        while(!address.is_open()){
            address.clear();
            cout << "File not found dude, try again. ";
            cin >> file_name;
            
            address.open(file_name.data());
        }
        
        
        Direct_cacheSimulator(address, index_size, off_set_size, cache);

        
        
    }
    
    
    //##########################################################################################################
    //Set-Associative 2-Way. 
    
    
    
    if (Cache_type == '2') {
        
        
        int num_lines = (cache_size/line_size)/2;// 
        
        cout << "Number of lines is " << num_lines << endl;
        
        int index_size = log_base_2(num_lines);
        cout << "Size of index is " << index_size << " bits" << endl;
        
        
        
        int off_set_size = log_base_2(line_size);
        cout << "Size of offset is " << off_set_size << " bits" << endl;
        
        
        
        //declare cache.
        vector<cacheline> cache;
        //cache.resize(num_lines); //for direct map.
        
        cache.resize(num_lines);
        
        
        
        cout << "Enter file name: ";
        
        
        
        
        ifstream address;
        string file_name;
        cin >> file_name;
        //   address.open("/Users/ibrahimsaeed/Desktop/HW6/HW6/bzip.trace");
        //Users/ibrahimsaeed/Desktop/HW6/HW6/blarg.txt
        
        
        address.open(file_name.data());
        while(!address.is_open()){
            address.clear();
            cout << "File not found dude, try again. ";
            cin >> file_name;
            
            address.open(file_name.data());
        }
        
        Set_2Way_cacheSimulator(address, index_size, off_set_size, cache);
        
        
        
    }
    

    
    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    //Set-Associative 4-Way
    
    if (Cache_type == '3') {
        
        
        int num_lines = (cache_size/line_size)/4;
        
        cout << "Number of lines is " << num_lines << endl;
        
        int index_size = log_base_2(num_lines);
        cout << "Size of index is " << index_size << " bits" << endl;
        
        
        
        int off_set_size = log_base_2(line_size);
        cout << "Size of offset is " << off_set_size << " bits" << endl;
        
        
        
        //declare cache.
        vector<cacheline> cache;
      
        
        cache.resize(num_lines);
        
        
        
        cout << "Enter file name: ";
        
        
        
        
        ifstream address;
        string file_name;
        cin >> file_name;
        //   address.open("/Users/ibrahimsaeed/Desktop/HW6/HW6/bzip.trace");
        //Users/ibrahimsaeed/Desktop/HW6/HW6/blarg.txt
        
        
        address.open(file_name.data());
        while(!address.is_open()){
            address.clear();
            cout << "File not found dude, try again. ";
            cin >> file_name;
            
            address.open(file_name.data());
        }
        
        Set_4Way_cacheSimulator(address, index_size, off_set_size, cache);
        
        
        
    }
    
   
    


    return 0;
}
