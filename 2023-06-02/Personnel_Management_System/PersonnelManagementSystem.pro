QT       += core gui sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    baoxiu_1.cpp \
    changemima.cpp \
    insertdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    qtlogin.cpp \
    searchapart.cpp \
    searchbaoxiu.cpp \
    searchbaoxiu_2.cpp \
    searchbaoxiu_3.cpp \
    searchstu.cpp \
    searchtiwen.cpp \
    stu_apartinfo.cpp \
    stu_baoxiu1.cpp \
    stu_baoxiu2.cpp \
    stu_mainwindow.cpp \
    stu_stuinfo.cpp \
    stu_tiwen.cpp \
    stu_yichang.cpp \
    stuguanli.cpp \
    tiwenchange_dialog.cpp \
    updatedialog.cpp

HEADERS += \
    baoxiu_1.h \
    changemima.h \
    insertdialog.h \
    mainwindow.h \
    qtlogin.h \
    searchapart.h \
    searchbaoxiu.h \
    searchbaoxiu_2.h \
    searchbaoxiu_3.h \
    searchstu.h \
    searchtiwen.h \
    stu_apartinfo.h \
    stu_baoxiu1.h \
    stu_baoxiu2.h \
    stu_mainwindow.h \
    stu_stuinfo.h \
    stu_tiwen.h \
    stu_yichang.h \
    stuguanli.h \
    tiwenchange_dialog.h \
    updatedialog.h

FORMS += \
    baoxiu_1.ui \
    changemima.ui \
    insertdialog.ui \
    mainwindow.ui \
    qtlogin.ui \
    searchapart.ui \
    searchbaoxiu.ui \
    searchbaoxiu_2.ui \
    searchbaoxiu_3.ui \
    searchstu.ui \
    searchtiwen.ui \
    stu_apartinfo.ui \
    stu_baoxiu1.ui \
    stu_baoxiu2.ui \
    stu_mainwindow.ui \
    stu_stuinfo.ui \
    stu_tiwen.ui \
    stu_yichang.ui \
    stuguanli.ui \
    tiwenchange_dialog.ui \
    updatedialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    ../QtLogin/QtLogin.pro

RESOURCES += \
    myResources.qrc

DISTFILES += \
    images/tubiao3.png
