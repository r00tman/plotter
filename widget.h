#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QProgressBar>

#include "render_thread.h"
#include "render_widget.h"

class main_widget : public QWidget {
    Q_OBJECT

private:
    render_widget *m_rw;
    QProgressBar *m_pb;

public:
    main_widget(QWidget *parent = 0);
    ~main_widget();

    void resizeEvent(QResizeEvent *);
    void keyPressEvent(QKeyEvent *e);

public slots:
    void show_progress(double p);
};

#endif // WIDGET_H
