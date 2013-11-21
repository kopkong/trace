#ifndef TIMEAXISWIDGET_H
#define TIMEAXISWIDGET_H

#include "graphaxiswidget.h"

/**
 * A simple axis that draws text using getTimeString to nicely format time values
 */
class TimeAxisWidget : public GraphAxisWidget {
public:
    TimeAxisWidget(QWidget* parent = 0);

    virtual void paintEvent(QPaintEvent *e);
};

#endif
