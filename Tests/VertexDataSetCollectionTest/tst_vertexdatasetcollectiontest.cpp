#include <functional>
#include <optional>

#include <QPolygonF>
#include <QString>
#include <QtTest>

#include "VertexDataSetCollection.h"

class VertexDataSetCollectionTest : public QObject
{
    Q_OBJECT

    private:
        Aerodlyn::VertexDataSetCollection collection;

    private slots:
        void init ();

        void test_contains ();
        void test_remove ();
        void test_add ();
        void test_length ();
        void test_get ();
};

void VertexDataSetCollectionTest::init ()
    { collection = Aerodlyn::VertexDataSetCollection (); }

void VertexDataSetCollectionTest::test_contains ()
{
    collection.add (QString ("Test"));
    QVERIFY (collection.contains (QString ("Test")));
    QVERIFY (!collection.contains (QString ("Another Test")));

    collection.add (QString ("Another Test"));
    QVERIFY (collection.contains (QString ("Another Test")));
}

void VertexDataSetCollectionTest::test_remove ()
{
    collection.add (QString ("Test"));
    QVERIFY (collection.remove (QString ("Test")));
    QCOMPARE (collection.length (), 0);

    collection.add (QString ("A"));
    collection.add (QString ("B"));
    collection.add (QString ("C"));
    QVERIFY (!collection.remove (QString ("Test")));
    QVERIFY (collection.remove (QString ("B")));
    QCOMPARE (collection.length (), 2);
}

void VertexDataSetCollectionTest::test_add ()
{
    QCOMPARE (collection.add (QString ("Test")), 0);
    QCOMPARE (collection.add (QString ("Test")), -1);
    QCOMPARE (collection.length (), 1);

    QCOMPARE (collection.add (QString ("Another Test")), 0);
    QCOMPARE (collection.length (), 2);
}

void VertexDataSetCollectionTest::test_length ()
{
    for (int i = 0; i < 100; i++)
    {
        collection.add (QString::number (i));
        QCOMPARE (collection.length (), i + 1);
    }

    QCOMPARE (collection.length (), 100);
}

void VertexDataSetCollectionTest::test_get ()
{
    for (int i = 0; i < 100; i++)
        collection.add (QString::number (i));

    std::optional <std::reference_wrapper <QPolygonF>> value = collection.get (QString ("50"));
    QVERIFY (value.has_value ());

    value = collection.get (QString ("100"));
    QVERIFY (!value.has_value ());
}

QTEST_APPLESS_MAIN(VertexDataSetCollectionTest)
#include "tst_vertexdatasetcollectiontest.moc"
