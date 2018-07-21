#!/bin/bash

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

LYOKOCOIND=${LYOKOCOIND:-$SRCDIR/lyokocoind}
LYOKOCOINCLI=${LYOKOCOINCLI:-$SRCDIR/lyokocoin-cli}
LYOKOCOINTX=${LYOKOCOINTX:-$SRCDIR/lyokocoin-tx}
LYOKOCOINQT=${LYOKOCOINQT:-$SRCDIR/qt/lyokocoin-qt}

[ ! -x $LYOKOCOIND ] && echo "$LYOKOCOIND not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
BTCVER=($($LYOKOCOINCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for lyokocoind if --version-string is not set,
# but has different outcomes for lyokocoin-qt and lyokocoin-cli.
echo "[COPYRIGHT]" > footer.h2m
$LYOKOCOIND --version | sed -n '1!p' >> footer.h2m

for cmd in $LYOKOCOIND $LYOKOCOINCLI $LYOKOCOINTX $LYOKOCOINQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${BTCVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${BTCVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
