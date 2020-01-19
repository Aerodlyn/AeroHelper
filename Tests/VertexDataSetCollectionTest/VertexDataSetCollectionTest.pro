QT += gui testlib
CONFIG += c++17

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../VertexEditor/Utilities
SOURCES +=  tst_vertexdatasetcollectiontest.cpp ../../VertexEditor/Utilities/VertexDataSetCollection.cpp
