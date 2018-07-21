// Copyright (c) 2009-2015 The Lyokocoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef LYOKOCOIN_QT_TEST_URITESTS_H
#define LYOKOCOIN_QT_TEST_URITESTS_H

#include <QObject>
#include <QTest>

class URITests : public QObject {
    Q_OBJECT

private Q_SLOTS:
    void uriTestsBase58();
    void uriTestsCashAddr();
    void uriTestFormatURI();
    void uriTestScheme();
};

#endif // LYOKOCOIN_QT_TEST_URITESTS_H
