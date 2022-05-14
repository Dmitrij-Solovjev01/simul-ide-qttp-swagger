#ifndef MAIN2WINDOW_H
#define MAIN2WINDOW_H

#include <QtWidgets>

class PropertiesWidget;
class ComponentSelector;
class CircuitWidget;
class EditorWindow;
class FileWidget;

class MAINMODULE_EXPORT Main2Window : public QMainWindow
{
    Q_OBJECT

  public:
    Main2Window();
    ~Main2Window();

    static Main2Window *self()
    {
        return m_pSelf;
    }

    QSettings *settings();

    void loadPlugins();
    void unLoadPugin(QString pluginName);

    void readSettings();

    void setTitle(QString title);

    double fontScale()
    {
        return m_fontScale;
    }
    void setFontScale(double scale)
    {
        m_fontScale = scale;
    }

    int autoBck();
    void setAutoBck(int secs);

    QString loc();
    void setLoc(QString loc);

    QString *circHelp();
    void loadCircHelp();

    QTabWidget *m_sidepanel;
    QWidget *m_ramTabWidget;
    QGridLayout *m_ramTabWidgetLayout;

  protected:
    void closeEvent(QCloseEvent *event);

  private:
    static Main2Window *m_pSelf;

    void loadPluginsAt(QDir pluginsDir);

    bool m_blocked;

    void createWidgets();
    void createMenus();
    void createToolBars();
    void writeSettings();
    void applyStyle();

    float m_fontScale;
    int m_autoBck;

    QSettings m_settings;

    QString m_version;
    QString m_styleSheet;
    QString m_circHelp;

    QHash<QString, QPluginLoader *> m_plugins;

    CircuitWidget *m_circuit;
    ComponentSelector *m_components;
    PropertiesWidget *m_itemprop;
    EditorWindow *m_editor;

    QSplitter *m_Centralsplitter;
    FileWidget *m_fileSystemTree;
};

#endif // MAIN2WINDOW_H
