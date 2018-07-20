CONFIG += ordered
TEMPLATE = subdirs

SUBDIRS += \
#    $$PWD/GenerateProto/GenerateProto.pro \
    $$PWD/ProRotoQml/ProRotoQml.pro \
    $$PWD/Applications

OTHER_FILES += \
            $$PWD/README.md \
            $$PWD/.gitignore \
            $$PWD/TODO \
            $$PWD/pri/deps.pri \
            $$PWD/pri/macrosAndModels.pri \
            $$PWD/pri/genproto.pri \
            $$PWD/pri/protos.pri \
            $$PWD/pri/deployment.pri \
            $$PWD/pri/artwork.pri \
#            $$PWD/pri/staticJson.pri \
            $$PWD/pri/qml-pages.pri \
            $$PWD/pri/qml-utils.pri \
            $$PWD/pri/qml-components.pri

#            $$PWD/pri/qml-realChat.pri

OTHER_FILES += $$PWD/GenerateProto/Protodata/proto/*.proto

#QMAKE_MAC_SDK = macosx10.12