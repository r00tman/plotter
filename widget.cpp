#include "widget.h"

#include <cmath>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_expression = QInputDialog::getText(this, "Formula", "Input formula:").toStdString();
    text_stream ts;
    ts.set_text(m_expression);
    //ts.next_char();
    token_reader r(ts);
    r.next_token();
    install_precedence();
    m_ast = parse_expression(r);
    m_ast = optimize(m_ast);
    //eps = QInputDialog::getDouble(this, "Epsilon", "Input epsilon (try values from 0.0001 for simple formulaes to 1000000 for very complex expressions:", 0, -2147483647, 214783647, 10);
}

Widget::~Widget()
{

}

const long long multisampling = 4;
const long double xscale = 15;
const long double yscale = 15;
const long double xpitch = -25;
const long double ypitch = -15;

long double Widget::f(long double x, long double y) {
    //long double f1 = sqrt(pow(x-5, 2)+pow(y-8, 2))+sqrt(pow(x-3, 2)+pow(y, 2))-sqrt(68);
    //long double f2 = sqrt(pow(x+5, 2)+pow(y-8, 2))+sqrt(pow(x+3, 2)+pow(y, 2))-sqrt(68);
    //long double f3 = pow(y, 2)+pow(x, 2)-9+fabsl(pow(x, 2)-9);
    //long double f4 = pow(y-8, 2) + pow(x, 2) - 25 + fabsl(pow(x, 2) - 25);
    //return f1*f2*f3*f4;
    return m_ast->execute(x, y);
}

bool Widget::condition(long double x, long double y) {
    return fabsl(f(x, y)) < eps;
}


void Widget::paintEvent(QPaintEvent */*e*/)
{
    QPixmap a(multisampling*this->width(), multisampling*this->height());
    a.fill();
    QPainter b;
    b.begin(&a);
    for (int y = 0; y < a.height(); y++) {
        for (int x = 0; x < a.width(); x++) {
            if (condition((x/xscale+xpitch)/multisampling, (y/yscale+ypitch)/multisampling))
                b.drawPoint(x, a.height()-y-1);
        }
    }
    b.end();

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::SmoothPixmapTransform, true);
    p.drawPixmap(0, 0, this->width(), this->height(), a);
}
