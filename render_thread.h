#ifndef RENDER_THREAD_H
#define RENDER_THREAD_H

#include <QThread>
#include <QImage>
#include <QMutex>
#include <QSize>

#include "coordinate_system.h"

class render_thread : public QThread {
    Q_OBJECT
public:
    QImage m_pixmap;
    const static long double MULTISAMPLING = 1.5;
    bool m_need_redraw, m_busy;
    coordinate_system m_cs;
    QSize m_size;
    QMutex m_pixmap_mutex;
    bool m_active;

private:
    void redraw();

public:
    explicit render_thread(QObject *parent = 0);
    void run();

public slots:
    bool request(coordinate_system cs, QSize size);

signals:
    void redrawed();
    void progress(double);
};

#endif // RENDER_THREAD_H
