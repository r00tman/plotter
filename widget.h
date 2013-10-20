#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui>
#include <QtWidgets>
#include <string>
#include "aggregate_node.h"
#include "ast.h"
#include "token_reader.h"
#include "text_stream.h"

class Widget : public QWidget
{
    Q_OBJECT

private:
    std::string m_expression;
    ast_node *m_ast;
    long double f(long double x, long double y);
    bool condition(long double x, long double y);

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    void paintEvent(QPaintEvent *e);
};

#endif // WIDGET_H
