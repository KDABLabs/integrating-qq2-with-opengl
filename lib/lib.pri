win32: Debug: {
    PRE_TARGETDEPS = $$OUT_PWD/../lib/debug/librenderlib.a
    LIBS += $$OUT_PWD/../lib/debug/librenderlib.a
}

win32: Release: {
    PRE_TARGETDEPS = $$OUT_PWD/../lib/release/librenderlib.a
    LIBS += $$OUT_PWD/../lib/release/librenderlib.a
}

!win32: {
    PRE_TARGETDEPS = $$OUT_PWD/../lib/librenderlib.a
    LIBS += $$OUT_PWD/../lib/librenderlib.a
}

INCLUDEPATH += ../lib/
