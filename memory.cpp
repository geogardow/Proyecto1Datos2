//
// Created by geogardow on 16/3/22.
//

#include "memory.h"
#include "iostream"
#include <string>

memory::memory(){
    var = "0";
}

void memory::setVar(std::string v) {
    var = v;
}

void memory::varToString() {
    std::cout<<var<<std::endl;
}