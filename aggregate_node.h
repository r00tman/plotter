#ifndef AGGREGATE_NODE_H
#define AGGREGATE_NODE_H

#include "ast.h"

static long double eps = sqrt(1e-5);

struct aggregate_node : public ast_node {
    ast_node *left, *right;

    virtual long double execute(long double x, long double y) {
        if (left && fabsl(left->execute(x, y)) < eps) {
            return 0;
        } else if (right && fabsl(right->execute(x, y)) < eps) {
            return 0;
        }
        return 1;
    }
};

static ast_node *optimize(ast_node *a) {
    if (binary_operator *z = dynamic_cast<binary_operator*>(a)) {
        if (z->op == '*') {
            aggregate_node *v = new aggregate_node();
            v->left = optimize(z->left);
            v->right = optimize(z->right);
            return v;
        }
    }
    return a;
}

#endif // AGGREGATE_NODE_H
