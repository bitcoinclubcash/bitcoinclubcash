// Copyright (c) 2017 The Lyokocoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef LYOKOCOIN_QT_TEST_GUIUTILTESTS_H
#define LYOKOCOIN_QT_TEST_GUIUTILTESTS_H

#include <QObject>
#include <QTest>

class GUIUtilTests : public QObject {
    Q_OBJECT

private Q_SLOTS:
    void dummyAddressTest();
    void toCurrentEncodingTest();
};

#endif // LYOKOCOIN_QT_TEST_GUIUTILTESTS_H
