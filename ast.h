#ifndef AST_H
#define AST_H

#include <map>
#include <cmath>
#include <cstdlib>

#include "token_reader.h"

struct ast_node {
    virtual long double execute(long double /*x*/, long double /*y*/) = 0;
};

struct number_node : public ast_node {
    long double number;
    virtual void parse(token_reader &a) {
        if (a.get_last_token_type() == a.tt_number) {
            number = std::atof(a.get_last_token().c_str());
            a.next_token();
        }
    }
    virtual long double execute(long double /*x*/, long double /*y*/) {
        return number;
    }
};

struct variable_node : public ast_node {
    char name;

    virtual long double execute(long double x, long double y) {
        if (name == 'x') {
            return x;
        } else if (name == 'y') {
            return y;
        }
    }
};

struct unary_operator : public ast_node {
    ast_node *left;
    char op;

    virtual long double execute(long double x, long double y) {
        switch (op) {
            case '-': return -left->execute(x, y); break;
            case '|': return fabsl(left->execute(x, y)); break;
        }
        return 0;
    }
};

struct binary_operator : public ast_node {
    ast_node *left, *right;
    char op;

    virtual long double execute(long double x, long double y) {
        switch (op) {
            case '^': return pow(left->execute(x, y), right->execute(x, y)); break;
            case '+': return left->execute(x, y) + right->execute(x, y); break;
            case '-': return left->execute(x, y) - right->execute(x, y); break;
            case '*': return left->execute(x, y) * right->execute(x, y); break;
            case '/': return left->execute(x, y) / right->execute(x, y); break;
            default:  return left->execute(x, y) * right->execute(x, y); break;
        }
        return 0;
    }
};

//////////////////////////////////////////////
static std::map<char, int> bin_op_precedence;

static int get_token_precedence(char token)
{
    std::map<char, int>::iterator tok_prec =
        bin_op_precedence.find(token);

    if (tok_prec == bin_op_precedence.end())
        return -1;

    return tok_prec->second;
}

static void install_precedence()
{
    // Install standard binary operators.
    // 1 is lowest precedence.
    bin_op_precedence['+'] = 4000;
    bin_op_precedence['-'] = 4000;
    bin_op_precedence['*'] = 5000;
    bin_op_precedence['/'] = 5000;
    bin_op_precedence['^'] = 6000; // highest
}
//////////////////////////////////////////////////

static number_node *parse_number(token_reader &a);
static variable_node *parse_variable(token_reader &a);
static ast_node *parse_paren_expr(token_reader &a);
static ast_node *parse_primary(token_reader &a);
static ast_node *parse_bin_op_rhs(token_reader &a, int expr_prec, ast_node *lhs);
static ast_node *parse_expression(token_reader &a);

static number_node *parse_number(token_reader &a) {
    number_node *r = new number_node();
    if (a.get_last_token_type() == a.tt_number) {
        r->number = std::atof(a.get_last_token().c_str());
        a.next_token();
    }
    return r;
}
static variable_node *parse_variable(token_reader &a) {
    variable_node *r = new variable_node();
    if (a.get_last_token_type() == a.tt_variable) {
        r->name = a.get_last_token()[0];
        a.next_token();
    }
    return r;
}

static ast_node *parse_paren_expr(token_reader &a) {
    if (a.get_last_token()[0] == '|') {
        a.next_token(); // eat '|'
        unary_operator *res = new unary_operator();
        res->left = parse_expression(a);
        res->op = '|';
        a.next_token(); // eat '|'
        return res;

    } else if (a.get_last_token()[0] == '(') {
        a.next_token(); // eat '('
        ast_node *res = parse_expression(a);
        a.next_token(); // eat ')'
        return res;
    }
    return NULL;
}

static ast_node *parse_primary(token_reader &a) {
    if (a.get_last_token_type() == a.tt_number) {
        return parse_number(a);
    } else if (a.get_last_token_type() == a.tt_variable) {
        return parse_variable(a);
    }
    switch(a.get_last_token()[0]) {
        case '(': return parse_paren_expr(a);
        case '|': return parse_paren_expr(a);
        case '-':
            a.next_token(); // eat '-'
            unary_operator *result = new unary_operator();
            result->left = parse_primary(a);
            result->op = '-';
            return result;
    }
    return NULL;
}

static ast_node *parse_bin_op_rhs(token_reader &a, int expr_prec, ast_node *lhs) {
    while(1) {
        int tok_prec = get_token_precedence(a.get_last_token()[0]);

        if (tok_prec < expr_prec) {
            return lhs;
        }

        int bin_op = a.get_last_token()[0];
        a.next_token(); // eat binop

        ast_node *rhs =  parse_primary(a);
        int next_prec = get_token_precedence(a.get_last_token()[0]);
        if (tok_prec < next_prec) {
            rhs = parse_bin_op_rhs(a, tok_prec + 1, rhs);
        }


        ast_node *old_lhs = lhs;
        lhs = new binary_operator();
        static_cast<binary_operator*>(lhs)->op = bin_op;
        static_cast<binary_operator*>(lhs)->left = old_lhs;
        static_cast<binary_operator*>(lhs)->right = rhs;
    }
}

static ast_node *parse_expression(token_reader &a) {
    ast_node *lhs = parse_primary(a);
    return parse_bin_op_rhs(a, 0, lhs);
}

#endif // AST_H
