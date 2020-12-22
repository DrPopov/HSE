#pragma once
#include <gmp.h>

/**
 * Значение для задания ограничения при генерировании произвольного числа
 */
#define inf      "1000000000000000000000000000000000000000000000000000000000000000000"

// maximum modulus
const long mxN = 1073741789;
// max order G = mxN + 65536
const long mxr = 1073807325;


//! Структура для хранения точки
typedef struct{
    mpz_t x, y;
}Point;

//! Структура для хранения параметров эллиптической кривой y^2  = x^3 + ax + b
typedef struct {
    mpz_t a, b, N, r;
    Point G;

}Curve;


//! Структура для хранения  пары  эл. подп  иси
typedef struct{
    mpz_t a, b;
}Pair;



//! mod(v^-1, u)
void exgcd(mpz_t *v, mpz_t *u, mpz_t *r);

//! mod(a, N)
void modn(mpz_t *a, Curve *e);

//! return mod(a, r)
void modr (mpz_t *a, Curve *e);

void disc(Curve *e);

//! Алгоритм выработки эл. подписи ECDSA
void SignGeneration();

//! Алгоритм проверки эл. подписи ECDSA
void SignVerification();

#include "ECDSA.h"
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//! mod(v^-1, u)
void exgcd(mpz_t *v, mpz_t *u, mpz_t *r);

//! mod(a, N)
void modn(mpz_t *a, Curve *e);

//! mod(a, r)
void modr (mpz_t *a, Curve *e);

//! Возвращает дескриминант  E
void disc(Curve *e);

//! Возвращает 1, есди р == 0
int isO (Point *p);

//! Возвращает 1, если точка Р лежит на кривой
int ison(Point *p, Curve *e);

//! Сложение точки Е
void padd (Point *r, Point *p, Point *q, Curve *e, int inverr, Point *zer0);

//! Умножение kP
void pmul (Point *r, Point *p, mpz_t k, Curve  *e, int inverr, Point *zer0);

//! Напечатать точку п с префиксом ф
void pprint (char *f, Point p, Curve *e);

//! Инициализация элептической кривой
int ellinit (long i[], Curve *e, int inverr);

//! Фун-ция генерации псевдослучайног числа [0..1)
double rnd(void);

//! Вычисление Эл. цифровой подрись
Pair signature (mpz_t s, long f, Curve *e, int inverr, Point *zer0);
//! Проверка цифровой подпсии
int verify (Point *W, mpz_t f, Pair sg, Curve  *e, int inverr, Point *zer0);

//! Проверка работоспособности подписи
void ec_dsa (long f, long d);



