TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += \
#        $$PWD/jsonpb \
#        $$PWD/qhttp/qhttp.pro \
        $$PWD/Files/files.pro \
        $$PWD/Models/models.pro \
        $$PWD/Sql/sql.pro \
        $$PWD/Theme/Theme.pro \
        $$PWD/Utils/utils.pro \
        $$PWD/Audio/audio.pro \
        $$PWD/Material/QtMaterial.pro \
#        $$PWD/libBotan \
#        $$PWD/libQSsh \
#        $$PWD/libQmlSsh \
        $$PWD/Protoblock/protoblock.pro \
        $$PWD/PeerTwoPeerChat \
        $$PWD/Backend

#Backend.depends = jsonpb
