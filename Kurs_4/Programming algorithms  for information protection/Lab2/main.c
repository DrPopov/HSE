#include <stdio.h>
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ECDSA.h"

//! Глобальная кривая
Curve e;

//! Точка на бесконечности zer0
Point zerO;
//! Невозможный обратный модуль N
int inverr;


int main() {
    typedef long eparm[6];
    mpz_t d, f;
    zerO.x = inf; zerO.y = 0;
    srand(time(NULL));

    // Тестрование: основные параметры эл. кривой в краткой форме Вейещтрасса:
    // s y^2 = x^3 + ax + b (mod N)
    eparm *sp, sets[10] = {
            {355, 671, 1073741789, 13693, 10088, 1073807281},
            {  0,   7,   67096021,  6580,   779,   16769911}, // 4
            { -3,   1,     877073,     0,     1,     878159},
            {  0,  14,      22651,    63,    30,        151}, // 151
            {  3,   2,          5,     2,     1,          5},

            {  0,   7,   67096021,  2402,  6067,   33539822}, // 2
            {  0,   7,   67096021,  6580,   779,   67079644}, // 1
            {  0,   7,     877069,     3, 97123,     877069},

            { 39, 387,      22651,    95,    27,      22651},
    };
    //  Хеш-фунция f
    f = 0x789abcde;
    d = 0;

    for (sp = sets; ; sp++) {
        if (ellinit (*sp))
            ec_dsa (f, d);

        else
            break;
    }
}
