#include "render_thread.h"
#include <cmath>
#include <QApplication>
#include "f.h"

void render_thread::redraw()
{
    QMutexLocker lock(&m_pixmap_mutex);
    m_pixmap = QImage(MULTISAMPLING*m_size.width(),
                      MULTISAMPLING*m_size.height(), QImage::Format_RGB32);
    m_pixmap.fill(Qt::white);

    for (int y = 0; y < m_pixmap.height(); y++) {
//#pragma omp parallel for
        for (int x = 0; x < m_pixmap.width(); x++) {
            long double xx, yy;
            m_cs.backward(x/(long double)MULTISAMPLING,
                          y/(long double)MULTISAMPLING, xx, yy);

            bool is_black = false;
            if (f(xx, yy)) {
                is_black = true;
            } else if (fabsl(fabsl(xx)-(long long)(fabsl(xx))) < 0.75/m_cs.xscale) {
                is_black = true;
            } else if (fabsl(fabsl(yy)-(long long)(fabsl(yy))) < 0.75/m_cs.yscale) {
                is_black = true;
            } else if (fabsl(xx) < 1.5/m_cs.xscale) {
                is_black = true;
            } else if (fabsl(yy) < 1.5/m_cs.yscale) {
                is_black = true;

            }
            if (is_black) {
                m_pixmap.setPixel(x, m_pixmap.height()-y-1, Qt::black);
            }
        }
        if ((y)*10/m_pixmap.height()!=(y-1)*10/m_pixmap.height()) {
            emit progress(y / (double) m_pixmap.height());
            qApp->processEvents();
        }
    }

    emit progress(1.0);
}


render_thread::render_thread(QObject *parent)
    : QThread(parent), m_need_redraw(false), m_busy(false), m_active(true) {

}

void render_thread::run() {
    while (m_active) {
        while (m_need_redraw) {
            m_need_redraw = false;
            m_busy = true;
            redraw();
            emit redrawed();
            m_busy = false;
        }
        msleep(100);
    }
}

bool render_thread::request(coordinate_system cs, QSize size) {
    if (!m_busy) {
        m_size = size;
        m_cs = cs;
        m_need_redraw = true;
        return true;
    }
    return false;
}
