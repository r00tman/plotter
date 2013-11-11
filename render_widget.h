#ifndef RENDER_WIDGET_H
#define RENDER_WIDGET_H

#include <QWidget>
#include <QMutex>
#include <QMutexLocker>
#include <QImage>
#include <QKeyEvent>

#include "coordinate_system.h"
#include "render_thread.h"

class render_widget : public QWidget {
    Q_OBJECT

private:
    coordinate_system m_cs;
    QImage m_image;
    bool m_painting;
    QMutex m_image_mutex;

public:
    render_thread *m_rt;

public:
    explicit render_widget(QWidget *parent = 0);
    ~render_widget();

    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *e);
    void keyPressEvent(QKeyEvent *e);

    void init_coordinate_system();
    void redraw();

public slots:
    void copy_image();
};

#endif // RENDER_WIDGET_H
