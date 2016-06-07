INCLUDEPATH += ../lib/

win32 {
    CONFIG(debug,debug|release) {
        LIBS += $$OUT_PWD/../lib/debug/librenderlib.a
        PRE_TARGETDEPS = $$OUT_PWD/../lib/debug/librenderlib.a
    }
    CONFIG(release,debug|release) {
        LIBS += $$OUT_PWD/../lib/release/librenderlib.a
        PRE_TARGETDEPS = $$OUT_PWD/../lib/release/librenderlib.a
    }
} else {
    LIBS += $$OUT_PWD/../lib/librenderlib.a
    PRE_TARGETDEPS = $$OUT_PWD/../lib/librenderlib.a
}
