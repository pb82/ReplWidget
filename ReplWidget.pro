CONFIG      += designer plugin debug_and_release
TARGET      = $$qtLibraryTarget(ReplWidgetPlugin)
TEMPLATE    = lib

HEADERS     = ReplWidgetPlugin.h
SOURCES     = ReplWidgetPlugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(ReplWidget.pri)
