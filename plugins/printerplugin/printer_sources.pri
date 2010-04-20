TEMPLATE = lib
TARGET = Printer

PACKAGE_VERSION = 0.0.2

DEFINES += PRINTER_LIBRARY

include(../fmf_plugins.pri)
include( $${PWD}/printerplugin_dependencies.pri )

HEADERS = $${PWD}/printerplugin.h \
    $${PWD}/printer_exporter.h \
    $${PWD}/printer.h \
    $${PWD}/printerpreviewer_p.h \
    $${PWD}/textdocumentextra.h \ # textdocumentheader.h
    $${PWD}/printerpreferences.h

SOURCES = $${PWD}/printerplugin.cpp \
    $${PWD}/printer.cpp \
    $${PWD}/printerpreviewer_p.cpp \
    $${PWD}/textdocumentextra.cpp \
    $${PWD}/printerpreferences.cpp

FORMS = $${PWD}/printerpreviewer_p.ui \
    $${PWD}/printerpreferences.ui

# Translators
TRANSLATIONS += $${SOURCES_TRANSLATIONS}/printerplugin_fr.ts \
    $${SOURCES_TRANSLATIONS}/printerplugin_de.ts \
    $${SOURCES_TRANSLATIONS}/printerplugin_es.ts

OTHER_FILES = Printer.pluginspec
