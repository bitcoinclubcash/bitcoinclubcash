// Copyright (c) 2017 The Lyokocoin Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef LYOKOCOIN_QT_TEST_LYOKOCOINADDRESSVALIDATORTESTS_H
#define LYOKOCOIN_QT_TEST_LYOKOCOINADDRESSVALIDATORTESTS_H

#include <QObject>
#include <QTest>

class LyokocoinAddressValidatorTests : public QObject {
    Q_OBJECT

private Q_SLOTS:
    void inputTests();
};

#endif
