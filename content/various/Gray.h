/**
 * Author: CP-Algorithms
 * Description: Generate gray code representation and reverses it.
 * Time: O(\log N)
 * Status: stress-tested
 */
#pragma once

int g (int n) {
    return n ^ (n >> 1);
}

int rev_g (int g) {
    int n = 0;
    for (; g; g >>= 1)
        n ^= g;
    return n;
}
