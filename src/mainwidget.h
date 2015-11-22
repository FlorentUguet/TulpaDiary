#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtWidgets>

#include "Widgets/tulpawidget.h"
#include "Widgets/schedulewidget.h"
#include "Widgets/qguidelist.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    MainWidget(QWidget *parent = 0);

signals:

public slots:
    void loadUI();

private:
    ScheduleWidget *w;
    TulpaWidget *t;
    QTabWidget *tab;
    QGuideList *guideList;


};

#endif // MAINWIDGET_H
