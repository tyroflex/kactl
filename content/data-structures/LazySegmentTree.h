/**
 * Author: Simon Lindholm
 * Date: 2016-10-08
 * License: CC0
 * Source: me
 * Description: Segment tree with ability to add or set values of large intervals, and compute max of intervals.
 * Can be changed to other things.
 * Use with a bump allocator for better performance, and SmallPtr or implicit indices to save memory.
 * Time: O(\log N).
 * Usage: Node* tr = new Node(v, 0, sz(v));
 * Status: stress-tested a bit
 */
#pragma once

#include "../various/BumpAllocator.h"

const ll inf = LLONG_MAX;

struct Node {
    Node *l = 0, *r = 0;
    ll lo, hi, mset = inf, madd = 0;
    ll minval = inf, sumval = 0, maxval = -inf;

    Node(ll lo, ll hi) : lo(lo), hi(hi) {}

    Node(vector<ll> &v, ll lo, ll hi) : lo(lo), hi(hi) {
        if (lo + 1 < hi) {
            ll mid = lo + (hi - lo) / 2;
            l = new Node(v, lo, mid);
            r = new Node(v, mid, hi);
            sumval = l->sumval + r->sumval;
            maxval = max(l->maxval, r->maxval);
            minval = min(l->minval, r->minval);
        } else {
            sumval = maxval = minval = v[lo];
        }
    }

    ll sumquery(ll L, ll R) {
        if (R <= lo || hi <= L) return 0;
        if (L <= lo && hi <= R) return sumval;
        push();
        return l->sumquery(L, R) + r->sumquery(L, R);
    }

    ll maxquery(ll L, ll R) {
        if (R <= lo || hi <= L) return -inf;
        if (L <= lo && hi <= R) return maxval;
        push();
        return max(l->maxquery(L, R), r->maxquery(L, R));
    }

    ll minquery(ll L, ll R) {
        if (R <= lo || hi <= L) return inf;
        if (L <= lo && hi <= R) return minval;
        push();
        return min(l->minquery(L, R), r->minquery(L, R));
    }

    void set(ll L, ll R, ll x) {
        if (R <= lo || hi <= L) return;
        if (L <= lo && hi <= R) {
            mset = x;
            sumval = (hi - lo) * x;
            minval = x;
            maxval = x;
            madd = 0;
        } else {
            push(), l->set(L, R, x), r->set(L, R, x);
            sumval = l->sumval + r->sumval;
            maxval = max(l->maxval, r->maxval);
            minval = min(l->minval, r->minval);
        }
    }

    void add(ll L, ll R, ll x) {
        if (R <= lo || hi <= L) return;
        if (L <= lo && hi <= R) {
            if (mset != inf) mset += x;
            else madd += x;
            sumval += (hi - lo) * x;
            minval += x;
            maxval += x;
        } else {
            push(), l->add(L, R, x), r->add(L, R, x);
            sumval = l->sumval + r->sumval;
            maxval = max(l->maxval, r->maxval);
            minval = min(l->minval, r->minval);
        }
    }

    void push() {
        if (!l) {
            ll mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid);
            r = new Node(mid, hi);
        }
        if (mset != inf)
            l->set(lo, hi, mset), r->set(lo, hi, mset), mset = inf;
        else if (madd)
            l->add(lo, hi, madd), r->add(lo, hi, madd), madd = 0;
    }
};
