QT += quick widgets svg sql network

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/database.cpp \
        src/main.cpp \
        src/network.cpp \
        src/quick/stats.cpp \
        src/quick/updater.cpp \
        src/quick/userinfo.cpp \
        src/types/stat.cpp \
        src/types/userdata.cpp \
        src/types/word.cpp

RESOURCES += res/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
android: include(D:/Unity/2020.3.14f1/Editor/Data/PlaybackEngines/AndroidPlayer/SDK/android_openssl/openssl.pri)

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

HEADERS += \
    src/database.h \
    src/network.h \
    src/quick/stats.h \
    src/quick/updater.h \
    src/quick/userinfo.h \
    src/types/stat.h \
    src/types/userdata.h \
    src/types/word.h
