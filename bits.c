/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(x & y) & ~(~x & ~y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if (!x && !y) return 1;
    if (!x) return 0;
    if (!y) return 0;
    return !((x >> 31) ^ (y >> 31));
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int b16 = ((v >> 16) > 0) << 4;
    v = v >> b16;
    int b8 = ((v >> 8) > 0) << 3;
    v = v >> b8;
    int b4 = ((v >> 4) > 0) << 2;
    v = v >> b4;
    int b2 = ((v >> 2) > 0) << 1;
    v = v >> b2;
    int b1 = ((v >> 1) > 0);
    v = v >> b1;
    return b16 | b8 | b4 | b2 | b1 ;

}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int l1 = n << 3;
    int l2 = m << 3;
    int p1 = (x >> l1) & 0xFF;
    int p2 = (x >> l2) & 0xFF;
    int mask = (0xFF << l1) | (0xFF << l2);
    return (x & ~mask) | (p1 << l2) | (p2 << l1);
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned r = 0;
    int i = 32;

    while (i) {
        r = (r << 1) | (v & 1);
        v = v >> 1;
        i = i - 1;
    }

    return r;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    return (x >> n) & ~(((1 << 31) >> n) << 1);
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int v = ~x;
    int count = 0;
    int shift;

    shift = (!(v >> 16)) << 4;
    count = count + shift;
    v = v << shift;

    shift = (!(v >> 24)) << 3;
    count = count + shift;
    v = v << shift;

    shift = (!(v >> 28)) << 2;
    count = count + shift;
    v = v << shift;

    shift = (!(v >> 30)) << 1;
    count = count + shift;
    v = v << shift;

    shift = !(v >> 31);
    count = count + shift;

    return count + !v;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    if (x == 0) return 0;
    unsigned int sign = x & 0x80000000u;
    unsigned abs_x = x;
    if (sign) abs_x = -abs_x;

    int E = 0;
    unsigned temp = abs_x;

    while (temp >> 1) {
        temp >>= 1;
        E++;
    }
    unsigned e = E + 127;
    unsigned mant;
    if (E <= 23) mant = abs_x << (23 - E);
    else 
    {
        int shift = E - 23;
        mant = abs_x >> shift;
        unsigned lost = abs_x & ((1u << shift) - 1);
        unsigned half = 1u << (shift - 1);
        if (lost > half) mant ++;
        else if (lost == half) if (mant & 1) mant ++;
        if (mant >> 24) {
            mant >>= 1;
            e++;
        }
    }
    unsigned frac = mant & 0x7FFFFFu;

    return sign | (e << 23) | frac;

}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf & 0x80000000u;
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x007FFFFF;

    if (exp == 0xFF)
        return uf;

    if (!exp)
        return sign | (uf << 1);

    exp = exp + 1;

    if (exp == 0xFF)
        frac = 0;

    return sign | (exp << 23) | frac;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    int sign = uf2 >> 31;
    int E = ((uf2 >> 20) & 0x7FF) - 1023;
    if (E > 30) return 0x80000000;
    else if(E < 0) return 0;
    int frac = (uf2 & 0xFFFFF) << 10 | (uf1 >> 22);
    int val = (1 << E) | (frac >> (30-E));
    if (sign) return -val;
    else return val;    

}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x > 127) return 0x7F800000;
    else if (x > -127) return (x + 127) << 23;
    else if (x < -149) return 0;
    else return (1 << (x + 149));
}
