#include "widget.h"

#include <QVBoxLayout>

#include <cmath>

main_widget::main_widget(QWidget *parent)
    : QWidget(parent) {
    QVBoxLayout *bl = new QVBoxLayout();
    m_rw = new render_widget();
    m_pb = new QProgressBar();
    m_pb->setRange(0, 100);
    connect(m_rw->m_rt, SIGNAL(progress(double)), SLOT(show_progress(double)));
    bl->addWidget(m_rw);
    bl->addWidget(m_pb);
    setLayout(bl);
}

main_widget::~main_widget() {

}

void main_widget::resizeEvent(QResizeEvent *a) {
    m_rw->resizeEvent(a);
}

void main_widget::keyPressEvent(QKeyEvent *e) {
    m_rw->keyPressEvent(e);
}

void main_widget::show_progress(double p) {
    m_pb->setValue(p*100);
}
