//
// Created by geogardow on 16/3/22.
//

#include "client.h"
#include "client.cpp"
#include <string>

int main() {
    client c = client();
    c.sendRequest("Hello its meeeeee");
}

