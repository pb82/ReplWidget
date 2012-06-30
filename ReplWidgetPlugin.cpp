#include "ReplWidget.h"
#include "ReplWidgetPlugin.h"

#include <QtCore/QtPlugin>

ReplWidgetPlugin::ReplWidgetPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void ReplWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ReplWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ReplWidgetPlugin::createWidget(QWidget *parent)
{
    return new ReplWidget(parent);
}

QString ReplWidgetPlugin::name() const
{
    return QLatin1String("ReplWidget");
}

QString ReplWidgetPlugin::group() const
{
    return QLatin1String("Input Widgets");
}

QIcon ReplWidgetPlugin::icon() const
{
    return QIcon(QLatin1String(":/application_xp_terminal.png"));
}

QString ReplWidgetPlugin::toolTip() const
{
    return QLatin1String("A simple repl widget to process user input");
}

QString ReplWidgetPlugin::whatsThis() const
{
    return QLatin1String("A simple repl widget to process user input and display the resulting output.");
}

bool ReplWidgetPlugin::isContainer() const
{
    return false;
}

QString ReplWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ReplWidget\" name=\"replWidget\">\n<property name=\"geometry\">\n\t<rect>\n\t<x>0</x>\n\t<y>0</y>\n\t<width>100</width>\n\t<height>100</height>\n\t</rect>\n</property>\n</widget>\n");
}

QString ReplWidgetPlugin::includeFile() const
{
    return QLatin1String("ReplWidget.h");
}

Q_EXPORT_PLUGIN2(ReplWidgetPlugin, ReplWidgetPlugin)
