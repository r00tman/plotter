#include "render_widget.h"
#include <QApplication>
#include <QPainter>

void render_widget::init_coordinate_system() {
    m_cs.xscale = 15;
    m_cs.yscale = 15;
    m_cs.xpitch = 0;
    m_cs.ypitch = 0;
    m_cs.xoffset = width()/2;
    m_cs.yoffset = height()/2;
}

void render_widget::redraw() {
    while(!m_rt->request(m_cs, size())) {
        qApp->processEvents();
    }
}

void render_widget::copy_image() {
    {
        QMutexLocker lock1(&m_rt->m_pixmap_mutex);
        QMutexLocker lock2(&m_image_mutex);
        m_image = m_rt->m_pixmap;
    }
    repaint();
}

render_widget::render_widget(QWidget *parent)
    : QWidget(parent) {
    m_painting = false;

    init_coordinate_system();

    m_rt = new render_thread();
    connect(m_rt, SIGNAL(redrawed()), SLOT(copy_image()));
    m_rt->start();

    redraw();
}

render_widget::~render_widget() {
    m_rt->m_active = false;
    m_rt->wait();
    delete m_rt;
}


void render_widget::paintEvent(QPaintEvent */*e*/) {
    QMutexLocker lock(&m_image_mutex);
    while (m_painting);
    m_painting = true;
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::SmoothPixmapTransform, true);
    p.drawImage(this->rect(), m_image);
    m_painting = false;
}

void render_widget::resizeEvent(QResizeEvent */*e*/) {
    m_cs.xoffset = width()/2;
    m_cs.yoffset = height()/2;

    redraw();
}

void render_widget::keyPressEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key_Left) {
        m_cs.xpitch += 20/m_cs.xscale;
    } else if (e->key() == Qt::Key_Right) {
        m_cs.xpitch -= 20/m_cs.xscale;
    } else if (e->key() == Qt::Key_Up) {
        m_cs.ypitch -= 20/m_cs.yscale;
    } else if (e->key() == Qt::Key_Down) {
        m_cs.ypitch += 20/m_cs.yscale;
    } else if (e->key() == '=') {
        m_cs.xscale *= 1.2;
        m_cs.yscale *= 1.2;
    } else if (e->key() == '-') {
        m_cs.xscale /= 1.2;
        m_cs.yscale /= 1.2;
    } else {
        return;
    }

    redraw();
}
