#include "ECDSA.h"
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void exgcd(mpz_t *v, mpz_t *u, mpz_t *r){
    int inverr;
    mpz_t q, t;
    mpz_t   s;
    mpz_set_str((mpz_ptr)r, "0", 10);
    mpz_set_str(s, "1", 10);


    mpz_t temp;
    if(v < 0){mpz_add((mpz_ptr) v, (mpz_ptr)v, (mpz_ptr)u);}

    while (v) {
        mpz_cdiv_q(q, (mpz_ptr)u, (mpz_ptr)v);
        mpz_mul(temp, q, (mpz_ptr)v);    //! t = u - q * v;
        mpz_sub(t, (mpz_ptr)u, temp);
        mpz_set(u, (mpz_ptr)v);
        mpz_set((mpz_ptr)v, t);


        mpz_mul(temp, q, s);    //! t = r - q * s;
        mpz_sub(t, r, temp);
        mpz_set(r, s);
        mpz_set(s, t);
    }

    mpz_set_str(temp, "1", 10);

    if (mpz_cmp((mpz_ptr)u , temp)) {
        gmp_printf(" impossible inverse mod N, gcd = %d\n", (mpz_ptr)u);
        inverr = 1;
    }
}

void modn(mpz_t *a, Curve *e){
    mpz_cdiv_r((mpz_ptr)a, (mpz_ptr)a, e->N);
    if (a < 0) {mpz_add((mpz_ptr)a, (mpz_ptr)a, e->N);}
}

void modr (mpz_t *a, Curve *e){
    mpz_cdiv_r((mpz_ptr)a, (mpz_ptr)a, e->r);
    if (a < 0) {mpz_add((mpz_ptr)a, (mpz_ptr)a, e->r);}
}

void disc(Curve *e){
    mpz_t c, a, b, temp, temp1;
    mpz_set(a, e->a);
    mpz_set(b, e->b);


    mpz_mul(temp, a, a);    //! c = 4 * modn(a * modn(a * a));
    modn((mpz_t *) temp, e);
    mpz_mul( temp, a, temp);
    modn((mpz_t *) temp, e);
    mpz_set_str(temp1, "4", 0);
    mpz_mul(c, temp1, temp);


    //! modn(-16 * (c + 27 * modn(b * b)))
    mpz_set_str(temp1, "27", 0);
    mpz_mul(temp, b, b);
    modn((mpz_t *) temp, e);
    mpz_mul(temp, temp1, temp);
    mpz_add(c, c, temp);
    mpz_set_str(temp1, "-16", 0);
    mpz_mul(c, temp1,  c);

}

//! Возвращает 1, есди р == 0
int isO (Point *p)
{
    return(mpz_cmp(p->x, inf) && mpz_cmp(p->y, 0));

}


//! Возвращает 1, если точка Р лежит на кривой
int ison(Point *p, Curve *e)
{
    mpz_t r, s, tmp;
    if (! isO (p)) {
        mpz_mul(r, p->x, p->x); //! e.a + p.x * p.x
        mpz_sub(r, e->a, r);
        modn((mpz_t *) r, e);

        mpz_mul(r, p->x, tmp); //!  r = modn(e.b + p.x * modn(e.a + p.x * p.x));
        mpz_sub(r, e->b, tmp);
        modn((mpz_t *) r, e);

        mpz_mul(s, p->y, p->y);
        modn((mpz_t *) s, e);

    }

    return mpz_cmp(r, s);
}

//! Сложение точки Е
void padd (Point *r, Point *p, Point *q, Curve *e, int inverr, Point *zer0)
{
    mpz_t la, t, tmp, tmp2, tmp3;
    mpz_set_str(tmp2, "0", 10);

    if (isO(p)) {
        mpz_set((mpz_ptr) r, q);
        return;
    }
    if (isO(q)) {
        mpz_set((mpz_ptr) r, p);
        return;
    }

    //! la = modn(t * exgcd(p.x - q.x, e.N));
    if (! mpz_cmp(p->x, q->x)){  //! R:= P + Q
        mpz_sub(t, p->y, q->y);
        mpz_sub(tmp, p->x, q->x);
        exgcd((mpz_t *) tmp, (mpz_t *) e->N, (mpz_t *) la);
        mpz_mul(la, t, la);
        modn(la, e);

    }
    else                                 // P = Q, R := 2P
    if (mpz_cmp(p->y, q->y) && (p->y, tmp2)) { //! t = modn(3 * modn(p.x * p.x) + e.a);
        mpz_set_str(tmp2, "3", 10);
        mpz_mul(tmp3, p->x, p->x);
        modn(tmp3, e);
        mpz_mul(tmp2, tmp2, tmp3);
        mpz_add(t, tmp2, e->a);

        mpz_set_str(tmp2, "2", 10);
        mpz_mul(tmp2, tmp2, p->y);
        exgcd(tmp2, e->N, tmp3);
        mpz_mul(la, t, tmp3);
        modn(la, e);
    }
    else{
        mpz_cmp( r, zer0);
        return;
    }           // P = -Q, R := O

    mpz_sub(tmp, p->x, q->x);   //! t = modn(la * la - p.x - q.x);
    mpz_mul(tmp2, la, la);
    mpz_sub(t, tmp2, tmp);
    modn((mpz_t *) t, e);

    mpz_sub(tmp, p->x, t);  //!  r->y = modn(la * (p.x - t) - p.y);
    mpz_mul(tmp, la, tmp);
    mpz_sub(r->y, tmp, p->y);
    modn(r->y, e);

    mpz_set(r->x, t);
    if(inverr){mpz_set((mpz_ptr) r, zer0);}

}

//! R:= multiple kP
void pmul (Point *r, Point *p, mpz_t k, Curve  *e, int inverr, Point *zer0){
    Point *s = zer0;
    Point *q;
    mpz_set(q, p);

    for (; k; mpz_cmp(k, 1)) {
        if (mpz_cmp(k, 1)){
            padd(&s, s, q, e, inverr, zer0);
        }
        if (inverr) {mpz_set(s, zer0); break;}
        padd(&q, q, q, e, inverr, q);
    }
    mpz_set(r, s);
}

//! Напечатать точку п с префиксом ф
void pprint (char *f, Point p, Curve *e){
    mpz_t y, tmp;
    mpz_set(y, p.y);

    if (isO (&p))
        printf ("%s (0)\n", f);

    else {

    }
        mpz_sub(tmp, e->N, y);
        if (mpz_cmp(y, tmp)){
            mpz_sub(y, y, e->N);

        printf ("%s (%lld, %lld)\n", f, p.x, y);
    }
}

//! Инициализация элептической кривой
int ellinit (long i[], Curve *e, int inverr)
{
    long a = i[0], b = i[1];
    mpz_set(e->N, i[2]);
    inverr = 0;

    if ((e->N < 5) || (e->N > mxN)) return 0;

    modn(e->a, e);
    modn(e->b, e);
    modn(i[3], e);
    modn(i[4], e);
    mpz_set(e->r, i[5]);

    if ((e->r < 5) || (e->r > mxr)) return 0;

    printf ("\nE: y^2 = x^3 + %dx + %d", a, b);
    printf (" (mod %lld)\n", e->N);
    pprint ("base point G", e->G, e);
    printf ("order(G, E) = %lld\n", e->r);

    return 1;
}

//! Фун-ция генерации псевдослучайног числа [0..1)
double rnd(void)
{
    return rand() / ((double)RAND_MAX + 1);
}

//! Вычисление Эл. цифровой подрись
Pair signature (mpz_t s, long f, Curve *e, int inverr, Point *zer0)
{
    long c, d, u, u1;
    Pair sg;
    mpz_t  tmp;
    Point *V;

    printf ("\nsignature computation\n");
    do {
        do {
            rnd();

            pmul (&V, c, u, e, inverr, zer0);
            modr(V->x, e);
        }
         while (c == 0);

        exgcd (u1, e->r, e);

        mpz_mul(tmp, s, c);
        mpz_sub(tmp, f, tmp);
        mpz_mul(u1, u1, tmp);
        modr(u1, e);
    }while(d ==0);

    mpz_set(sg.a, c);
    mpz_set(sg.b, d);

    return sg;
}

//! Проверка цифровой подпсии
int verify (Point *W, mpz_t f, Pair sg, Curve  *e, int inverr, Point *zer0)
{
    long c = sg.a, d = sg.b;
    long t, c1, h1, h2;
    mpz_t h;
    Point V, V2;

    t = (c > 0) && (c < e->r);
    t &= (d > 0) && (d < e->r);
    if (! t) return 0;

    printf ("\nsignature verification\n");
    exgcd (d, e->r);
    mpz_mul(f, f, h);
    modr(f , e, inverr, zer0);
    modr(c * h);
    printf ("h1,h2 = %d, %d\n", h1,h2);
    pmul (&V, e.G, h1);
    pmul (&V2, W, h2);
    pprint ("h1G", V, e);
    pprint ("h2W", V2, e);
    padd (&V, V, V2, e);
    pprint ("+ =", V, e);
    if (isO (&V)) return 0;
    modr(V.x, e);
    printf ("c' = %d\n", c1);

    return (c1 == c);
}

//! Проверка работоспособности подписи
void ec_dsa (long f, long d)
{
    printf ("\nkey generation\n");
    s = 1 + (long)(rnd() * (e.r - 1));
    pmul (&W, e.G, s);
    printf ("private key s = %d\n", s);
    pprint ("public key W = sG", W);

    // next highest power of 2 - 1
    t = e.r;
    for (i = 1; i < 32; i <<= 1)
      t |= t >> i;
    while (f > t) f >>= 1;
    printf ("\naligned hash %x\n", f);

    sg = signature (s, f);
    if (inverr) goto errmsg;
    printf ("signature c,d = %d, %d\n", sg.a, sg.b);

    if (d > 0) {
      while (d > t) d >>= 1;
      f ^= d;
      printf ("\ncorrupted hash %x\n", f);
    }

    t = verify (W, f, sg);
    if (inverr) goto errmsg;
    if (t)
      printf ("Valid\n_____\n");
    else
      printf ("invalid\n_______\n");

    return;

    errmsg:
    printf ("invalid parameter set\n");
    printf ("_____________________\n");
}
