# define some default paths for installation process
mac:INSTALL_BASENAME_PATH          = mac
else:linux*:INSTALL_BASENAME_PATH  = linux
else:win32:INSTALL_BASENAME_PATH   = win
else:freebsd*:INSTALL_BASENAME_PATH   = freebsd

# binary wrapper (bw) installer --> leave empty == no bw installation, otherwise specify the filename
# the bw should be located in SOURCES_RESOURCES_TEXTFILES
INSTALL_BINARY_WRAPPER_NAME =

# Qt libs and plugs
INSTALL_QT_LIBS_PATH      = $${INSTALL_BINARY_PATH}/libs
INSTALL_QT_PLUGINS_PATH   = $${INSTALL_PLUGINS_PATH}/qt

# some help for file copying
LIB_EXTENSION             = so*

# install Qt libs and plugins inside the bundle ; leave it empty if you don't want to install QT libs and plugs inside the bundle
INSTALL_QT_INSIDE_BUNDLE = true

# These inclusions modify the default path for the installation process
macx:include(install_mac.pri)
else:linux*:include(install_linux.pri)
else:win32:include(install_win.pri)
else:freebsd*:include(install_freebsd.pri)

# by default package is constructed inside the svn trunk under
# packages/yourOs/Application
isEmpty(INSTALL_ROOT_PATH):     INSTALL_ROOT_PATH      = $${RELEASE_BINARY_PATH}/$${INSTALL_BASENAME_PATH}/$${BINARY_TARGET}
isEmpty(INSTALL_BINARY_PATH):   INSTALL_BINARY_PATH    = $${INSTALL_ROOT_PATH}
isEmpty(INSTALL_LIBS_PATH):     INSTALL_LIBS_PATH      = $${INSTALL_BINARY_PATH}
isEmpty(INSTALL_PLUGINS_PATH):  INSTALL_PLUGINS_PATH   = $${INSTALL_LIBS_PATH}
isEmpty(INSTALL_RESOURCES_PATH):INSTALL_RESOURCES_PATH = $${INSTALL_BINARY_PATH}/Resources
isEmpty(INSTALL_DESKTOP_FILES_PATH):INSTALL_DESKTOP_FILES_PATH =
isEmpty(INSTALL_DESKTOP_ICON_PATH):INSTALL_DESKTOP_ICON_PATH=

DEFINES *= "INSTALL_BINARY_PATH=\"\\\"$$INSTALL_BINARY_PATH\\\"\"" \
           "INSTALL_LIBS_PATH=\"\\\"$$INSTALL_LIBS_PATH\\\"\"" \
           "INSTALL_PLUGINS_PATH=\"\\\"$$INSTALL_PLUGINS_PATH\\\"\"" \
           "INSTALL_RESOURCES_PATH=\"\\\"$$INSTALL_RESOURCES_PATH\\\"\"" \
	   "INSTALL_DESKTOP_FILES_PATH=\"\\\"$$INSTALL_DESKTOP_FILES_PATH\\\"\"" \
	   "INSTALL_QT_PLUGINS_PATH=\"\\\"$$INSTALL_QT_PLUGINS_PATH\\\"\""

# resources paths
INSTALL_DATABASES_PATH    = $${INSTALL_RESOURCES_PATH}/databases
INSTALL_TRANSLATIONS_PATH = $${INSTALL_RESOURCES_PATH}/translations
INSTALL_FREEDATAPACK_PATH = $${INSTALL_RESOURCES_PATH}/datapacks/appinstalled
INSTALL_FORMS_PATH        = $${INSTALL_RESOURCES_PATH}
INSTALL_PROFILES_PATH     = $${INSTALL_RESOURCES_PATH}
INSTALL_TEXTFILES_PATH    = $${INSTALL_RESOURCES_PATH}/textfiles
INSTALL_SMALLPIX_PATH     = $${INSTALL_RESOURCES_PATH}/pixmap/16x16
INSTALL_MEDIUMPIX_PATH    = $${INSTALL_RESOURCES_PATH}/pixmap/32x32
INSTALL_BIGPIX_PATH       = $${INSTALL_RESOURCES_PATH}/pixmap/64x64
INSTALL_SVGPIX_PATH       = $${INSTALL_RESOURCES_PATH}/pixmap/svg
INSTALL_SPLASHPIX_PATH    = $${INSTALL_RESOURCES_PATH}/pixmap/splashscreens
INSTALL_DOCS_PATH         = $${INSTALL_RESOURCES_PATH}/doc/$${BINARY_TARGET}

# message the configuration
message( ******************************************************************************** )
message( ***************************    Qt configuration   ****************************** )
message( ******************************************************************************** )
message( Qt version: $$[QT_VERSION])
message( Qt is installed in $$[QT_INSTALL_PREFIX])
message( Header files: $$[QT_INSTALL_HEADERS])
message( Libraries: $$[QT_INSTALL_LIBS])
message( Binary files (executables): $$[QT_INSTALL_BINS])
message( Plugins: $$[QT_INSTALL_PLUGINS])
message( Spec file in use: env spec: $$QMAKESPEC)
message( Spec file in use: qmake spec: $$QMAKE_MKSPECS)
message( ******************************************************************************** )
message( **************************    FreeMedForms Config   **************************** )
message( ******************************************************************************** )
CONFIG(LINUX_INTEGRATED):message( Building Linux Integrated version )
message( Binary : )
message(    * From : $${BUILD_BINARY_PATH} )
message(    * To : $${INSTALL_BINARY_PATH} )
message( Application libraries : )
message(    * From : $${BUILD_LIB_PATH})
message(    * To : $${INSTALL_LIBS_PATH})
message(    * Extension : $${LIB_EXTENSION})
message(    * RPath : $${RPATH_LIBS_BIN} )
message( Plugins : )
message(    * From : $${BUILD_PLUGIN_PATH})
message(    * To : $${INSTALL_PLUGINS_PATH} )
message(    * Extension : $${LIB_EXTENSION})
!isEmpty(INSTALL_QT_LIBS_PATH):message( Qt Libs : $${INSTALL_QT_LIBS_PATH} )
!isEmpty(INSTALL_QT_PLUGINS_PATH):message( Qt Plugins : $${INSTALL_QT_PLUGINS_PATH} )
message( ******************************************************************************** )
message( *************************    FreeMedForms Resources   ************************** )
message( ******************************************************************************** )
message( Resources : $${INSTALL_RESOURCES_PATH} )
message( Translations : $${INSTALL_TRANSLATIONS_PATH} )
!isEmpty(INSTALL_FREEDATAPACK_PATH):message( Free datapack path : $${INSTALL_FREEDATAPACK_PATH} )
!isEmpty(INSTALL_FORMS_PATH):message( Forms : $${INSTALL_FORMS_PATH} )
message( Pixmaps - small : $${INSTALL_SMALLPIX_PATH} )
message( Pixmaps - medium : $${INSTALL_MEDIUMPIX_PATH} )
message( Pixmaps - big : $${INSTALL_BIGPIX_PATH} )
message( Pixmaps - svg : $${INSTALL_SVGPIX_PATH} )
message( Pixmaps - splashscreens : $${INSTALL_SPLASHPIX_PATH} )
!isEmpty(INSTALL_DOCS_PATH):message( Documentation : $${INSTALL_DOCS_PATH} )
!isEmpty(INSTALL_DESKTOP_FILES_PATH):message( DesktopFile : $${INSTALL_DESKTOP_FILES_PATH} )
!isEmpty(INSTALL_DESKTOP_ICON_PATH):message( DesktopIcon : $${INSTALL_DESKTOP_ICON_PATH} )
message( ******************************************************************************** )
message( *************************    FreeMedForms Databases   ************************** )
message( ******************************************************************************** )
contains(INSTALL_DRUGS,1):message( Installing drugs database )
contains(INSTALL_PROFILES_FILES,1):message( Installing user default Profiles files)
contains(INSTALL_ICD_DATABASE,1):message( Installing ICD10 database )
contains(INSTALL_ACCOUNT_FILES,1):message( Installing Account files )
contains(INSTALL_ZIPCODES,1):message( Installing ZipCodes database )


# Install target
!isEmpty(INSTALL_BINARY_PATH):!isEmpty(BUILD_BINARY_PATH){
target.path = $${INSTALL_BINARY_PATH}
#installtarget.files = $${BUILD_BINARY_PATH}/$${BINARY_TARGET}
INSTALLS += target
}

macx {
 # Qt 4.7 / MacOS 10.6 patch when not using the Qt macdeploy app
 #$$[QT_INSTALL_LIBS]/QtGui.framework/Resources/qt_menu.nib
 # /Library/Frameworks/QtGui.framework/Resources/qt_menu.nib
 mac10_6.path=$${INSTALL_RESOURCES_PATH}
 mac10_6.files=$$[QT_INSTALL_LIBS]/QtGui.framework/Resources/qt_menu.nib
 INSTALLS+=mac10_6
}

# manage binary wrapper
!isEmpty(INSTALL_BINARY_WRAPPER_NAME){
bw.path = $${INSTALL_BINARY_PATH}
bw.files = $${SOURCES_RESOURCES_TEXTFILES}/$${INSTALL_BINARY_WRAPPER_NAME}
INSTALLS += bw
}

# Install libs (on Win32 copy from BUILD_LIB_PATH/../ (remove plugins path) )
!isEmpty(INSTALL_LIBS_PATH):!isEmpty(BUILD_LIB_PATH){
applibs.path = $${INSTALL_LIBS_PATH}
mac:applibs.files = $${BUILD_LIB_PATH}/*.1.$${LIB_EXTENSION}
else:unix:applibs.files = $${BUILD_LIB_PATH}/*$${LIB_EXTENSION}*
else:win32:applibs.files = $${BUILD_LIB_PATH}/../*$${LIB_EXTENSION}
applibs.CONFIG += no_check_exist
INSTALLS += applibs
}
# Install plugins
!isEmpty(INSTALL_PLUGINS_PATH):!isEmpty(BUILD_PLUGIN_PATH){
plugs.path = $${INSTALL_PLUGINS_PATH}
plugs.files = $${BUILD_PLUGIN_PATH}/*.$${LIB_EXTENSION}
plugs.CONFIG += no_check_exist
INSTALLS += plugs
}
# Install plugins specs
!isEmpty(INSTALL_PLUGINS_PATH):!isEmpty(BUILD_PLUGIN_PATH){
plugs_specs.path = $${INSTALL_PLUGINS_PATH}
plugs_specs.files = $${BUILD_PLUGIN_PATH}/*.pluginspec
plugs_specs.CONFIG += no_check_exist
INSTALLS += plugs_specs
}

# Install translations
!isEmpty(INSTALL_TRANSLATIONS_PATH):!isEmpty(SOURCES_TRANSLATIONS){
i18n.path = $${INSTALL_TRANSLATIONS_PATH}
i18n.files = $${SOURCES_TRANSLATIONS_PATH}/*.qm
qti18n.path = $${INSTALL_TRANSLATIONS_PATH}
qti18n.files = $$[QT_INSTALL_TRANSLATIONS]/translations/*fr.qm \
               $$[QT_INSTALL_TRANSLATIONS]/translations/*de.qm \
               $$[QT_INSTALL_TRANSLATIONS]/translations/*es.qm
INSTALLS +=  qti18n i18n
}

# Install forms && FreeMedForms Profiles
!isEmpty(INSTALL_FORMS_PATH):!isEmpty(SOURCES_FORMS){
forms.path = $${INSTALL_FORMS_PATH}
forms.files = $${SOURCES_FORMS}
INSTALLS += forms
}

# Install drugs databases
contains(INSTALL_DRUGS,1):!isEmpty(INSTALL_FREEDATAPACK_PATH):!isEmpty(SOURCES_FREEDATAPACK_PATH){
drugsdb.path = $${INSTALL_FREEDATAPACK_PATH}/drugs
drugsdb.files = $${SOURCES_FREEDATAPACK_PATH}/drugs/*
INSTALLS += drugsdb
}

#!isEmpty(INSTALL_DATABASES_PATH):!isEmpty(SOURCES_DATABASES){
#usersdb.path = $${INSTALL_DATABASES_PATH}/users
#usersdb.files = $${SOURCES_GLOBAL_RESOURCES}/databases/users/*txt
#INSTALLS += usersdb
#}

# Install profiles
contains(INSTALL_PROFILES_FILES,1):!isEmpty(INSTALL_PROFILES_PATH){
profiles_resources.path = $${INSTALL_PROFILES_PATH}
profiles_resources.files = $${SOURCES_PROFILES}
INSTALLS += profiles_resources
}

# Install theme
screens.path = $${INSTALL_SPLASHPIX_PATH}
screens.files = $${SOURCES_GLOBAL_RESOURCES}/pixmap/splashscreens/*.png
pix16.path = $${INSTALL_SMALLPIX_PATH}
pix16.files = $${SOURCES_GLOBAL_RESOURCES}/pixmap/16x16/*.png
pix16flags.path = $${INSTALL_SMALLPIX_PATH}/flags
pix16flags.files = $${SOURCES_GLOBAL_RESOURCES}/pixmap/16x16/flags/*.png
pix32.path = $${INSTALL_MEDIUMPIX_PATH}
pix32.files = $${SOURCES_GLOBAL_RESOURCES}/pixmap/32x32/*.png
pix64.path = $${INSTALL_BIGPIX_PATH}
pix64.files = $${SOURCES_GLOBAL_RESOURCES}/pixmap/64x64/*.png
pix64jpg.path = $${INSTALL_BIGPIX_PATH}
pix64jpg.files = $${SOURCES_GLOBAL_RESOURCES}/pixmap/64x64/*.jpg
pixsvg.path = $${INSTALL_SVGPIX_PATH}
pixsvg.files = $${SOURCES_GLOBAL_RESOURCES}/pixmap/svg/*.svg
INSTALLS+=screens pix16 pix16flags pix32 pix64 pix64jpg pixsvg

# Install desktop file
!isEmpty(INSTALL_DESKTOP_FILES_PATH){
desk.path=$${INSTALL_DESKTOP_FILES_PATH}
desk.files=$${SOURCES_GLOBAL_RESOURCES}/package_helpers/$${LOWERED_APPNAME}.desktop
desk_icon.path=$${INSTALL_DESKTOP_ICON_PATH}
desk_icon.files=$${SOURCES_GLOBAL_RESOURCES}/pixmap/svg/$${LOWERED_APPNAME}.svg
INSTALLS+= desk desk_icon
}

# Install textfiles (mostly used in debug mode)
!isEmpty(INSTALL_TEXTFILES_PATH){
textfiles.path=$${INSTALL_TEXTFILES_PATH}
textfiles.files=$${SOURCES_GLOBAL_RESOURCES}/textfiles/*
INSTALLS+= textfiles
}

# Documentation
!isEmpty(INSTALL_DOCS_PATH){
docs.path=$${INSTALL_DOCS_PATH}
docs.files=$${SOURCES_GLOBAL_RESOURCES}/doc/$${LOWERED_APPNAME}/*
docs.CONFIG += no_check_exist
INSTALLS+=docs
}

# Package Helpers
!isEmpty(INSTALL_RESOURCES_PATH){
packageHelpers.path=$${INSTALL_RESOURCES_PATH}/package_helpers
packageHelpers.files=$${SOURCES_GLOBAL_RESOURCES}/package_helpers/*
INSTALLS+=packageHelpers
}

# Install some specific files
contains(INSTALL_ICD_DATABASE,1){
freeicd_sqlfile.path=$${INSTALL_RESOURCES_PATH}/sql/icd10
freeicd_sqlfile.files=$${SOURCES_GLOBAL_RESOURCES}/sql/icd10/icd10.sql
#freeicd_db.path=$${INSTALL_FREEDATAPACK_PATH}/icd10
#freeicd_db.files=$${SOURCES_FREEDATAPACK_PATH}/icd10/icd10.db
#INSTALLS+=freeicd_sqlfile freeicd_db
INSTALLS+=freeicd_sqlfile
}

# Install FreeAccount SQL files
contains(INSTALL_ACCOUNT_FILES,1){
account_sqlfile.path=$${INSTALL_RESOURCES_PATH}/sql/account
account_sqlfile.files=$${SOURCES_GLOBAL_RESOURCES}/sql/account/*
INSTALLS+=account_sqlfile
}

# Install Zipcodes db  TODO MOVE THIS IN DATAPACKS
contains(INSTALL_ZIPCODES,1){
zipcodes_db.path=$${INSTALL_DATABASES_PATH}/zipcodes
zipcodes_db.files=$${SOURCES_DATABASES}/zipcodes/zipcodes.db
INSTALLS+=zipcodes_db
}

# configuration for non-integrated solutions (everything is included inside the bundle)
!isEmpty(INSTALL_QT_INSIDE_BUNDLE){
   macx:message( Error detected: Trying to install Qt libs inside bundle: $${INSTALL_QT_INSIDE_BUNDLE} )
   macx:error(For MacOS use scripts instead of the installer for the Qt libs)
   QTPLUGINS_PATH = $$[QT_INSTALL_PLUGINS]
   qt_libs.path  = $${INSTALL_QT_LIBS_PATH}
   linux {
   qt_libs.files = $$[QT_INSTALL_LIBS]/*QtCore.so.4 \
                  $$[QT_INSTALL_LIBS]/*QtGui.so.4 \
                  $$[QT_INSTALL_LIBS]/*QtSql.so.4 \
                  $$[QT_INSTALL_LIBS]/*QtScript.so.4 \
                  $$[QT_INSTALL_LIBS]/*Qt3Support.so.4 \
                  $$[QT_INSTALL_LIBS]/*QtXml.so.4 \
                  $$[QT_INSTALL_LIBS]/*QtSvg.so.4 \
                  $$[QT_INSTALL_LIBS]/*QtNetwork.so.4
   }
   win32 {
   qt_libs.files = $$[QT_INSTALL_BINS]/QtCore4.$${LIB_EXTENSION} \
                  $$[QT_INSTALL_BINS]/QtGui4.$${LIB_EXTENSION} \
                  $$[QT_INSTALL_BINS]/QtSql4.$${LIB_EXTENSION} \
                  $$[QT_INSTALL_BINS]/QtScript4.$${LIB_EXTENSION} \
                  $$[QT_INSTALL_BINS]/QtXml4.$${LIB_EXTENSION} \
                  $$[QT_INSTALL_BINS]/QtSvg4.$${LIB_EXTENSION} \
                  $$[QT_INSTALL_BINS]/QtNetwork4.$${LIB_EXTENSION} \
                  $$[QT_INSTALL_BINS]/mingw*.$${LIB_EXTENSION} \
                  $$[QT_INSTALL_BINS]/libgcc_s_dw2-1.$${LIB_EXTENSION} \
                 # $$[QT_INSTALL_LIBS]/Qt3Support.$${LIB_EXTENSION} \
   }

   INSTALLS+=qt_libs

   linux:message(Bundle : Qt Libs will be installed from $$[QT_INSTALL_LIBS] to $${INSTALL_QT_LIBS_PATH})
   else:win32:message(Bundle : Qt Libs will be installed from $$[QT_INSTALL_BIN] to $${INSTALL_QT_LIBS_PATH})

   # Install Qt plugins (SQL plugins)
   qt_sqlplugins.path = $${INSTALL_QT_PLUGINS_PATH}
   qt_sqlplugins.files = $${QTPLUGINS_PATH}/sqldrivers
   qt_imagesplugins.path = $${INSTALL_QT_PLUGINS_PATH}
   qt_imagesplugins.files = $${QTPLUGINS_PATH}/imageformats
   qt_accessibleplugins.path = $${INSTALL_QT_PLUGINS_PATH}
   qt_accessibleplugins.files = $${QTPLUGINS_PATH}/accessible
   INSTALLS+=qt_sqlplugins qt_imagesplugins qt_accessibleplugins
   message(Bundle : Qt Plugins will be installed from $${QTPLUGINS_PATH} to $${INSTALL_QT_PLUGINS_PATH} )
 }

