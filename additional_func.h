#ifndef ADDITIONAL_FUNC_H
#define ADDITIONAL_FUNC_H


#include <QApplication>
#include <QTranslator>
#include "pin.h"
#include "mainwindow.h"
#include "circuitview.h"
#include "circuitwidget.h"
#include "circuitview.h"
#include "plotterwidget.h"
#include "terminalwidget.h"
#include <QtWidgets>
#include "circuitwidget.h"
#include "mainwindow.h"
#include "circuit.h"
#include "filebrowser.h"
#include <QSvgGenerator>

#include "circuitwidget.h"
#include "circuitview.h"
#include "circuit.h"
#include "mainwindow.h"
#include "component.h"
#include "mcucomponent.h"
#include "subcircuit.h"
#include "utils.h"
#include <QtWidgets>
#include <QGraphicsView>
#include <iostream>

struct myPin {
    Circuit *circ;
    myPin(Circuit *circuit):circ(circuit) {}

    Pin *getPin(QString pinName) {
        return circ->m_pinMap[pinName];
    }

    bool connectPin(Pin *from, Pin *to) {
        circ->newconnector(from);
        circ->closeconnector(to);
        return 0;
    }
    bool connectPinString(QString from, QString to){
        connectPin(getPin(from), getPin(to));
    }
    ~myPin(){
        delete circ;
    }
};

#endif // ADDITIONAL_FUNC_H
