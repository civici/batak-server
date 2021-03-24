#pragma once

#include <stdio.h>
#include <stdlib.h>

struct Card{

    int val;
    int koz;

};

struct Card* card_new(int val, int koz);