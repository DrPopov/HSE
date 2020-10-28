#include "curve.h"
#include <gmp.h>
//#include "parameters.h"


/**
 * Вывод координат точки в проективных координатах на экран
 */
void printProjectivePoint (const struct Point *point)
{
    gmp_printf("\nX = %Zd\nY = %Zd\nZ = %Zd\n\n", point->X, point->Y, point->Z);
}

/**
 *  Инициализация нейтрального элемента в проективных координатах 0 = (0, 1, 1)
 */
void neutralPointInit (struct Point *point){
    mpz_init(point->X); mpz_init(point->Y); mpz_init( point->Z);
    mpz_set_str(point->X, "0", 10);
    mpz_set_str(point->Y, "1", 10);
    mpz_set_str(point->Z, "1", 10);
}

/**
 * Инициализация точки с произвольными координатами
 */
void customPointInit (struct Point *point, char *X, char *Y, char *Z) {
    mpz_init(point->X);  mpz_init(point->Y); mpz_init(point->Z);
    mpz_set_str(point->X, X, 10);
    mpz_set_str(point->Y, Y, 10);
    mpz_set_str(point->Z, Z, 10);
}

/**
 *  Инициализация порождающей точки
 */
void basePointInit (struct Point *point, const struct JacobiCurve *curve){
    neutralPointInit(point);
    mpz_set(point->X, curve->X_base);
    mpz_set(point->Y, curve->Y_base);
    mpz_set(point->Z, curve->Z_base);

}

/*
 * Перевод в аффинные координаты из проективных:
 *      x = X / Z
 *      y = X / Z^2
 *      z = 0
 */
void affineCoordinatesConversion (struct Point *res, const struct Point *point, const struct JacobiCurve *curve){
    mpz_t x, y, z, exp;
    mpz_init(x); mpz_init(y); mpz_init(z); mpz_init(exp);

    // x = X / Z
    mpz_invert(x, point->Z, curve->p);                  // x = 1 / Z
    mpz_mul(x, x, point->X);                            // x * X / Z
    mpz_mod(x, x, curve->p);                         // x * X mod p


    // y = Y / Z^2
    mpz_set_str(exp, "2", 10);
    mpz_invert(y, point->Z, curve->p);                   // y = 1 / Z
    mpz_powm(y, y, exp, curve->p);                       // y = 1 / Z^2
    mpz_mul(y, y, point->Y);                          // y = Y / Z^2
    mpz_mod(y, y, curve->p);


    // z = 0
    mpz_set_str(z, "0", 10);                           // z = 0


    mpz_set(res->X, x);
    mpz_set(res->Y, y);
    mpz_set(res->Z, z);


    // Clear
    mpz_clear(x); mpz_clear(y); mpz_clear(z); mpz_clear(exp);

}

/*
 * Вывод координат точки в аффинных координатах
 */
void printAffinePoint (const struct Point *point, const struct JacobiCurve *curve)
{
    struct Point res;
    mpz_init(res.X); mpz_init(res.Y); mpz_init(res.Z);
    neutralPointInit (&res);

    affineCoordinatesConversion (&res, point, curve);
    gmp_printf("x = %Zd\ny = %Zd\n\n",  res.X, res.Y);
}

/*
 * Инициализация кривой в форме квадрики Якоби:
 * Y^2 = e * X^4 - 2 * d * X^2 * Z^2 + Z^4
 */
void JacobiCurveInit(struct JacobiCurve *curve){
    mpz_t buf1, buf2, buf3, exp;
    mpz_inits(buf1,  buf2, buf3);
    mpz_init(exp);

    mpz_set_str(curve->theta, theta_str, 10);
    mpz_set_str(curve->a,         a_str, 10);
    mpz_set_str(curve->x,    x_base_str, 10);
    mpz_set_str(curve->y,    y_base_str, 10);
    mpz_set_str(curve->p,         p_str, 10);
    mpz_set_str(curve->q,         q_str, 10);
    mpz_set_str(curve->e,           "0", 10);
    mpz_set_str(curve->d,           "0", 10);
    mpz_set_str(curve->X_base,      "0", 10);
    mpz_set_str(curve->Y_base,      "0", 10);
    mpz_set_str(curve->Z_base,      "0", 10);


    // e = (-(3 * theta^2 + 4 * a)) / 16
    mpz_set_str(exp, "2", 10);
    mpz_set_str(buf2, "4", 10);
    mpz_set_str(buf3, "3", 10);                             // buf3 = 3
    mpz_powm(curve->e, curve->theta, exp, curve->p);        // e = theta^2
    mpz_mul(curve->e, buf3, curve->e);                      // e = 3 * theta^2
    // --------------------------------------------------------buf1 = 4 * a
    mpz_mul(buf1, buf2, curve->a);                          // buf1 = 4 * a
    mpz_mod(buf1, buf1, curve->p);
    // ---------------
    mpz_add(buf1, curve->e, buf1);                          // buf1 = 3 * theta^2 + 4 * a
    mpz_mod(buf1, buf1, curve->p);

    mpz_set_str(buf3, "-1", 10);                            // buf3 = -1
    mpz_mul(buf1, buf1, buf3);
    mpz_mod(buf1, buf1, curve->p);                          // buf1 = -(3 * theta^2 + 4 * a)

    mpz_set_str(buf3, "16", 10);                            // buf3 = 16
    mpz_invert(buf3, buf3, curve->p);                       // buf3 = 1 / 16
    mpz_mul(curve->e, buf3, buf1);                          // e = (-(3 * theta^2 + 4 * a)) / 16
    mpz_mod(curve->e, curve->e, curve->p);


    // d = 3 * theta / 4
    mpz_set_str(buf3, "3", 10);
    mpz_mul(curve->d, buf3, curve->theta);
    //mpz_add(curve->d, curve->theta, curve->theta);          // d = 2 * theta
    //mpz_mod(curve->d, curve->d, curve->p);
    //mpz_add(curve->d, curve->d, curve->theta);              // d = 3 * theta
    mpz_mod(curve->d,curve->d,curve->p);
    mpz_set_str(buf3, "4", 10);
    mpz_invert(buf3, buf3, curve->p);                       // buf3 = 1 / 4
    mpz_mul(curve->d, buf3, curve->d);                      // d = 3 * theta / 4
    mpz_mod(curve->d, curve->d, curve->p);

    // X_base = 2 * (x - theta)
    mpz_sub(curve->X_base, curve->x, curve->theta);         // X_base = x - X_base
    mpz_mod(curve->X_base, curve->X_base, curve->p);
    mpz_add(curve->X_base, curve->X_base, curve->X_base);   // X_base= 2 * (x - theta)
    mpz_mod(curve->X_base, curve->X_base, curve->p);

    // Y_base = (2 * x + theta) * (x - theta)^2 - y^2
    mpz_add(buf1, curve->x, curve->x);                      // buf1 = 2 * x
    mpz_mod(buf1, buf1, curve->p);
    mpz_add(buf1, buf1, curve->theta);                      // buf1 = 2 * x + theta
    mpz_mod(buf1, buf1, curve->p);
    mpz_sub(buf2, curve->x, curve->theta);                  // buf2 = x - theta
    mpz_mod(buf2, buf2, curve->p);
    mpz_powm(buf2, buf2, exp, curve->p);                    // buf2 = (x - theta)^2
    mpz_mul(buf2, buf1, buf2);                              // buf2 = (2 * x + theta) * (x - theta)^2
    mpz_mod(buf2, buf2, curve->p);
    mpz_powm(curve->Y_base, curve->y, exp, curve->p);       // Y_base = y^2
    mpz_sub(curve->Y_base, buf2, curve->Y_base);            // Y_base = (2 * x + theta) * (x - theta)^2 - y^2
    mpz_mod(curve->Y_base, curve->Y_base, curve->p);



    // Z_base = y
    mpz_set(curve->Z_base, curve->y);                       // Z_base = y
    mpz_mod(curve->Z_base, curve->Z_base, curve->p);


    mpz_clear(buf1);
    mpz_clear(buf2);
    mpz_clear(buf3);

}


// сложение двух точек
void pointsAddition (struct Point *res, const struct Point *P1, const struct Point *P2, const struct JacobiCurve *curve){
    mpz_t T1, T2, T3, T4, T5, T6, T7, T8, exp;
    mpz_init(T1); mpz_init(T2); mpz_init(T3); mpz_init(T4); mpz_init(T5); mpz_init(T6); mpz_init(T7);  mpz_init(T8); mpz_init(exp);

    mpz_set(T1, P1->X);                                     // T1 = X1; T2 = Y1; T3 = Z1
    mpz_set(T2, P1->Y);
    mpz_set(T3, P1->Z);
    mpz_set(T4, P2->X);                                      // T4 = X2; T5 = Y2; T6 = Z2
    mpz_set(T4, P2->Y);
    mpz_set(T4, P2->Z);
    mpz_set_str(exp, "2", 10);


    mpz_mul(T7, T1, T3);                            // T7 = X1 * Z1
    mpz_mod(T7, T7, curve->p);
    mpz_add(T7, T2, T7);                            // T7 = X1 * Z1 + Y1
    mpz_mod(T7, T7, curve->p);
    mpz_mul(T8, T4, T6);                            // T8 = X2 * Z2
    mpz_mod(T8, T8, curve->p);
    mpz_add(T8, T5, T8);                            // T8 = X2 * Z2 + Y2
    mpz_mod(T8, T8, curve->p);
    mpz_mul(T2, T2, T5);                            // T2 = Y1 * Y2
    mpz_mod(T2, T2, curve->p);
    mpz_mul(T7, T7, T8);                            // T7 = X3 + Y1 * Y2 + X1 * X2 * Z1 * Z2
    mpz_mod(T7, T7, curve->p);
    mpz_sub(T7, T7, T2);                            // T7 = X3 + X1 * X2 * Z1 * Z2
    mpz_mod(T7, T7, curve->p);
    mpz_mul(T5, T1, T4);                            // T5 = X1 * X2
    mpz_mod(T5, T5, curve->p);
    mpz_add(T1, T1, T3);                            // T1 = X1 + Z1
    mpz_mod(T1, T1, curve->p);
    mpz_mul(T8, T3, T6);                            // T8 = Z1 * Z2
    mpz_mod(T8, T8, curve->p);
    mpz_add(T4, T4, T6);                            // T4 = X2 + Z2
    mpz_mod(T4, T4, curve->p);
    mpz_mul(T6, T5, T8);                            // T6 = X1 * X2 * Z1 * Z2
    mpz_mod(T6, T6, curve->p);
    mpz_sub(T7, T7, T6);                            // T7 = X3
    mpz_mod(T7, T7, curve->p);
    mpz_mul(T1, T1, T4);                            // T1 = X1 * Z2 + X2 * Z1 + X1 * X2 + Z1 * Z2
    mpz_mod(T1, T1, curve->p);
    mpz_sub(T1, T1, T5);                            // T1 = X1 * Z2 + X2 * Z1 + Z1 * Z2
    mpz_mod(T1, T1, curve->p);
    mpz_sub(T1, T1, T8);                            // T1 = X1 * Z2 + X2 * Z1
    mpz_mod(T1, T1, curve->p);
    mpz_powm(T3, T1, exp,curve->p);                 // T3 = X1^2 * Z2^2+ X2^2 * Z1^2 + 2 * X1 * X2 * Z1 * Z2
    mpz_add(T6, T6, T6);                            // T6 = 2 * X1 * X2 * Z1 * Z2
    mpz_mod(T6, T6, curve->p);
    mpz_sub(T3, T3, T6);                            // T3 = X1^2 * Z2^2+ X2^2 * Z1^2
    mpz_mod(T3, T3, curve->p);
    mpz_mul(T4, curve->e, T6);                      // T4 = 2 * e * X1 * X2 * Z1 * Z2
    mpz_mod(T4, T4, curve->p);
    mpz_mul(T3, T3, T4);                            // T3 = 2 * e * X1 * X2 * Z1 * Z2 * (X1^2 * Z2^2+ X2^2 * Z1^2)
    mpz_mod(T3, T3, curve->p);
    mpz_mul(T4, curve->d, T6);                      // T4 = 2 * d * X1 * X2 * Z1 * Z2
    mpz_mod(T4, T4, curve->p);
    mpz_sub(T2, T2, T4);                            // T2 = Y1 * Y2 - 2 * d * X1 * X2 * Z1 * Z2
    mpz_sub(T2, T2, curve->p);
    mpz_powm(T4, T8, exp, curve->p);                // T4 = Z1^2 * Z2^2
    mpz_powm(T8, T5, exp, curve->p);                // T8 = X1^2 * X2^2
    mpz_mul(T8, curve->e, T8);                      // T8 = e * X1^2 * X2^2
    mpz_mod(T8, T8, curve->p);
    mpz_add(T5, T4, T8);                            // T5 = Z1^2 * Z2^2 + e * X1^2 * X2^2
    mpz_mod(T5, T5, curve->p);
    mpz_mul(T2, T2, T5);                            // T2 = (Z1^2 * Z2^2 + e * X1^2 * X2^2) * (Y1 * Y2 - 2 * d * X1 * X2 * Z1 * Z2)
    mpz_mod(T2, T2, curve->p);
    mpz_add(T2, T2, T3);                            // T2 = Y3
    mpz_mod(T2, T2, curve->p);
    mpz_sub(T5, T4, T8);                            // T5 = Z3
    mpz_mod(T5, T5, curve->p);


    mpz_set(res->X, T7);                            // X3 = T7
    mpz_set(res->Y, T2);                            // Y3 = T2
    mpz_set(res->Z, T5);                            // Z3 = T5



    mpz_clear(T1); mpz_clear(T2);  mpz_clear(T3); mpz_clear(T4); mpz_clear(T5); mpz_clear(T6); mpz_clear(T7); mpz_clear(T8);
}


// сравнение двух  точек на равенство
int pointsEquality (const struct Point *P1, const struct Point *P2, const struct JacobiCurve *curve){
   struct Point res1, res2;
   mpz_init(res1.X); mpz_init(res1.Y); mpz_init(res1.Z); mpz_init(res2.X); mpz_init(res2.Y); mpz_init(res2.Z);

   int eq = -2;

   neutralPointInit(&res1);
   neutralPointInit(&res2);

   affineCoordinatesConversion(&res1, P1, curve);
   affineCoordinatesConversion(&res2, P2, curve);

   eq = (mpz_cmp(res1.X, res2.X) && mpz_cmp(res1.Y, res1.Y));

   pointFree(&res1);
   pointFree(&res2);

   return eq;

}


/*
 * Запись противоположной точки:
 * P1 = (X1 : Y1 : Z1), P2 = (X2 : Y2 : Z2)
 * P2 = -P1, когда P2 = (X2 : Y2 : Z2) = (-X1 : Y1 : Z1)
 */
void negativePoint (struct Point *res, const struct Point *point){
    mpz_set(res->X, point->X);
    mpz_set(res->Y, point->Y);
    mpz_set(res->Z, point->Z);
    mpz_neg(res->X, res->X);
}

// алгоритм "Лесенка Монтгомери" для вычисления кратной точки
void montgomeryLadder (struct Point *res, const struct Point *point, const struct JacobiCurve *curve, const mpz_t power){
    mpz_t tmp;
    mpz_init(tmp);

    int bits = mpz_popcount(power);

    struct Point R, Q;
    mpz_init(R.X); mpz_init (R.Y); mpz_init(R.Z);
    mpz_init(Q.X); mpz_init (Q.Y); mpz_init(Q.Z);

    neutralPointInit (&Q);

    mpz_set (R.X, point->X);
    mpz_set (R.Y, point->Y);
    mpz_set (R.Z, point->Z);

    for (int i = bits - 1; i >= 0; i--)
    {
        if (mpz_tstbit (power, i))
        {
            pointsAddition (&Q, &Q, &R, curve);     // Q = Q + R
            pointsAddition (&R, &R, &R, curve);     // R = 2 * R
        }
        else
        {
            pointsAddition (&R, &R, &Q, curve);     // R = Q + R
            pointsAddition (&Q, &Q, &Q, curve);     // Q = 2 * Q
        }
    }


    mpz_set (res->X, Q.X);
    mpz_set (res->Y, Q.Y);
    mpz_set (res->Z, Q.Z);

    mpz_clear(&R);
    mpz_clear(&Q);
    mpz_clear(tmp);
}

/*
 * Проверка, лежит ли точка на кривой Y^2 = e * X^4 - 2 * d * X^2 * Z^2 + Z^4
 */
int pointOnCurve (const struct JacobiCurve *curve, const struct Point *point){
    int res = -2;

    mpz_t left, right, buf1, buf2, exp;
    mpz_init(left);mpz_init(right); mpz_init(buf1); mpz_init(buf2); mpz_init(exp);


    mpz_set_str (buf2, "4", 10);                                // buf2 = 4
    mpz_set_str (exp,  "2", 10);                                // exp = 2
    mpz_powm (left, point->Y, exp, curve->p);                   // left = Y^2
    mpz_set_str (exp,  "4", 10);                                // exp = 2
    mpz_powm (right, point->X, exp, curve->p);                  // right = X^4
    mpz_mul (right, right, curve->e);                           // right = e * X^4
    mpz_mod (right, right, curve->p);
    mpz_powm (buf2, point->Z, exp, curve->p);                   // buf2 = Z^4
    mpz_add (right, right, buf2);                               // right = e * X^4 + Z^4
    mpz_mod (right, right, curve->p);
    mpz_mul (buf2, point->X, point->Z);                         // buf2 = X * Z
    mpz_mod (buf2, buf2, curve->p);
    mpz_set_str (exp,  "2", 10);
    mpz_powm (buf2, buf2,exp,  curve->p);                       // buf2 = X^2 * Z^2
    mpz_mul (buf2, buf2, curve->d);                             // buf2 = d * X^2 * Z^2
    mpz_mod (buf2, buf2, curve->p);
    mpz_add (buf2, buf2, buf2);                                 // buf2 = 2 * d * X^2 * Z^2
    mpz_mod (buf2, buf2, curve->p);
    mpz_sub (right, right, buf2);                               // right = e * X^4 - 2 * d * X^2 * Z^2 + Z^4
    mpz_mod (right, right, curve->p);
    mpz_sub (buf1, left, right);                                // buf1 = Y^2 - (e * X^4 - 2 * d * X^2 * Z^2 + Z^4)
    mpz_mod(buf1, buf1, curve->p);


    res =  mpz_cmp_d(buf1, 0);

    mpz_clear(left); mpz_clear(right); mpz_clear(buf1); mpz_clear(buf2);

    return res;
}



/*
 * Очистка памяти
 */
void pointFree (struct Point *point)
{
    mpz_clear(point->X);
    mpz_clear(point->Y);
    mpz_clear(point->Z);
}


/*
 * Очистка памяти
 */
void curveFree (struct JacobiCurve *curve)
{
    mpz_clear(curve->theta);
    mpz_clear(curve->a);
    mpz_clear(curve->e);
    mpz_clear(curve->d);
    mpz_clear(curve->x);
    mpz_clear(curve->y);
    mpz_clear(curve->p);
    mpz_clear(curve->q);
    mpz_clear(curve-> X_base);
    mpz_clear(curve->Y_base);
    mpz_clear(curve->Z_base);
}