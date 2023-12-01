/**
 * Author: CP-Algorithms
 * Description: Josephus Problem
 * Time: O(N)
 * Status: stress-tested
 */
#pragma once

int josephus(int n, int k) {
    int res = 0;
    for (int i = 1; i <= n; ++i)
        res = (res + k) % i;
    return res + 1;
}
