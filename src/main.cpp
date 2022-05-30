/***************************************************************************
 *   Copyright (C) 2012 by santiago González                               *
 *   santigoro@gmail.com                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>.  *
 *                                                                         *
 ***************************************************************************/

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
#include "additional_func.h"
#include "editorwindow.h"


Component* mymanualСreateComponent(CircuitWidget *circuitwidget, QString _type, QString _id) {
    return circuitwidget->DIM_create(_type, _id);
}


QString langFile( QString locale )
{
    QString langF = "../share/simulide/translations/simulide_"+locale+".qm";

    QFile file( langF );
    if( !file.exists() ) langF = "";

    return langF;
}

int main(int argc, char *argv[])
{

#ifdef _WIN32
    QStringList paths = QCoreApplication::libraryPaths();
    paths.append("plugins");
    paths.append("plugins/platforms");
    paths.append("plugins/imageformats");
    paths.append("plugins/sqldrivers");
    paths.append("plugins/bearer");
    paths.append("plugins/generic");
    paths.append("plugins/iconengines");
    paths.append("plugins/qmltooling");
    paths.append("plugins/printsupport");
    QCoreApplication::setLibraryPaths(paths);

    if (AttachConsole(ATTACH_PARENT_PROCESS))
    {
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }
#endif

    //QApplication::setGraphicsSystem( "raster" );//native, raster, opengl
    QApplication app( argc, argv );

    QSettings settings( QStandardPaths::standardLocations( QStandardPaths::DataLocation).first()+"/simulide.ini",  QSettings::IniFormat, 0l );

    QString locale = QLocale::system().name();
    if( settings.contains( "language" ) ) locale = settings.value( "language" ).toString();

    QString langF = langFile( locale );
    if( langF == "" )
    {
        locale = QLocale::system().name().split("_").first();
        langF = langFile( locale );
    }
    if( langF == "" ) langF = "../share/simulide/translations/simulide_en.qm";

    QTranslator translator;
    translator.load( langF );
    app.installTranslator( &translator );

    MainWindow window;

    Circuit *circ = window.m_circuit->m_circView.m_circuit;
    CircuitWidget *circwidget = window.m_circuit;

    mymanualСreateComponent(circwidget, "Resistor", "Resistor-1");
    mymanualСreateComponent(circwidget, "Amperimeter", "Amperimeter-1");
    mymanualСreateComponent(circwidget, "Fixed Voltage", "Fixed Voltage-1");
    mymanualСreateComponent(circwidget, "Ground", "Ground-1");

    myPin mypin(circ);

    mypin.connectPinString("Fixed Voltage-1-outnod", "Resistor-1-lPin");
    mypin.connectPinString("Resistor-1-rPin", "Amperimeter-1-lPin");
    mypin.connectPinString("Amperimeter-1-rPin", "Ground-1-Gnd");

    window.m_circuit->powerCircOn();
    window.m_circuit->powerCircOff();

    QString name ="/home/dima/_backup.simu";
    circ->saveCircuit(name);





    window.setLoc( locale );

    /*QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = ( screenGeometry.width()-window.width() ) / 2;
    int y = ( screenGeometry.height()-window.height() ) / 2;
    window.move( x, y );*/
    window.scroll( 0, 50 );

//    window.show();
    app.setApplicationVersion( APP_VERSION );

    return app.exec();
}

