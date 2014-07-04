TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    dcpu.cpp

HEADERS += \
    cpuTests.h \
    common.h \
    dcpu.h \
    tests.h \
    cpuOpcodeAddTest.h \
    cpuOpcodeSubTest.h \
    cpuOpcodeDivTest.h \
    cpuOpcodeSHLTest.h \
    cpuOpcodeMulTest.h \
    cpuOpcodeModTest.h \
    cpuOpcodeSHRTest.h \
    cpuOpcodeBitwiseTest.h \
    cpuOpcodeIfTest.h \
    cpuOpcodeNonBasicTest.h \
    fullProgramTest.h


unix:!macx:!symbian: LIBS += -lgtest

unix:!macx:!symbian: LIBS += -lpthread
