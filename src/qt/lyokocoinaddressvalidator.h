// Copyright (c) 2011-2014 The Lyokocoin Core developers
// Copyright (c) 2017 The Lyokocoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef LYOKOCOIN_QT_LYOKOCOINADDRESSVALIDATOR_H
#define LYOKOCOIN_QT_LYOKOCOINADDRESSVALIDATOR_H

#include <QValidator>

/**
 * Lyokocoin address entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class LyokocoinAddressEntryValidator : public QValidator {
    Q_OBJECT

public:
    explicit LyokocoinAddressEntryValidator(const std::string &cashaddrprefix,
                                          QObject *parent);

    State validate(QString &input, int &pos) const override;

private:
    std::string cashaddrprefix;
};

/** Lyokocoin address widget validator, checks for a valid lyokocoin address.
 */
class LyokocoinAddressCheckValidator : public QValidator {
    Q_OBJECT

public:
    explicit LyokocoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

#endif // LYOKOCOIN_QT_LYOKOCOINADDRESSVALIDATOR_H
