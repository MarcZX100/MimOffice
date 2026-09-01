# MimOffice

MimOffice is an office suite — Words, Sheets, Stage, and Karbon — built by
XI14 as the office-suite sibling of [MimOS](https://mimoslinux.org).

MimOffice is a rebranded, actively-synced fork of the [KDE Calligra
Suite](https://invent.kde.org/office/calligra). We track Calligra's
stable release branches and periodically merge upstream fixes and
features; MimOffice's own changes are limited to branding, packaging,
and distribution — the application code itself comes from Calligra. See
[NOTICE](NOTICE) for the full attribution and license details, and
[TRADEMARKS.md](TRADEMARKS.md) for how the MimOffice name and MIMI mascot
relate to the source code license.

## Contents

Office productivity:

- **Words:** Word processor
- **Sheets:** Spreadsheet calculator
- **Stage:** Presentation program

Graphics:

- **Karbon:** Vector graphics

MimOffice ships a scoped subset of upstream Calligra (Words, Sheets,
Stage, Karbon) rather than the full upstream application set; see
`CMakePresets.json` and `CalligraProducts.cmake`.

## Installing

The easiest way to install MimOffice is via the prebuilt Flatpak from the
[latest GitHub release](https://github.com/MarcZX100/MimOffice/releases/latest),
which is rebuilt automatically from every `main` commit:

```sh
# Download mimoffice.flatpak from the release page above, then:
flatpak install --user mimoffice.flatpak
flatpak run org.mimoslinux.MimOffice
```

You can also just double-click the downloaded `mimoffice.flatpak` file in a
file manager to install it through GNOME Software or KDE Discover.

## Building and running

MimOffice is built on the [KDE Frameworks](https://develop.kde.org/products/frameworks),
same as upstream Calligra — you don't need to be running Plasma Desktop
to use it, it works on any desktop or platform.

```sh
cmake --preset mimoffice
cmake --build --preset mimoffice
```

This configures a build scoped to `PRODUCTSET="WORDS;SHEETS;STAGE;KARBON"`.
For general Calligra build background (dependencies, platform notes), see
upstream's own build documentation: https://community.kde.org/Calligra/Building

A Flatpak manifest (`org.mimoslinux.MimOffice.json`) is also provided for
building and distributing MimOffice as a Flatpak.

## License

MimOffice is free software, primarily under LGPL-2.0-or-later and
GPL-2.0-or-later, inherited from upstream Calligra. See
[COPYING](COPYING), [COPYING.LIB](COPYING.LIB), and the
[LICENSES/](LICENSES/) directory for details, and [NOTICE](NOTICE) for
how MimOffice's own additions are licensed.

## Contact / issues

Report MimOffice-specific issues (branding, packaging, updates) at:
https://github.com/MarcZX100/MimOffice/issues

For issues in the underlying application logic that also affect upstream
Calligra, consider reporting to KDE's Calligra project as well:
https://community.kde.org/Calligra
