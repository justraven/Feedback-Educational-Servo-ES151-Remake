#ifndef PARSE_H
#define PARSE_H

#include <Arduino.h>

#define DATA_STR(x) data_flock[x]
#define READ_DATA_UNTIL(x) data = Serial.readStringUntil(x)
#define MAX 10

static String data = "";
static String data_flock[MAX];

static void parseString(){

    int counter = 0;
    String temp = "";

    if(data[data.length() - 2] != ';')
        data = data + ';';
    
    for(int x=0; x < data.length(); x++){
        if(data[x] == ';'){
            data_flock[counter] = temp;
            temp = "";
            counter++;
        }
        else
            temp = temp + data[x];
    }
}



#endif