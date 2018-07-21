
Debian
====================
This directory contains files used to package lyokocoind/lyokocoin-qt
for Debian-based Linux systems. If you compile lyokocoind/lyokocoin-qt yourself, there are some useful files here.

## lyokocoincash: URI support ##


lyokocoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install lyokocoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your lyokocoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/lyokocoin128.png` to `/usr/share/pixmaps`

lyokocoin-qt.protocol (KDE)

