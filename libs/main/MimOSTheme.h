/* This file is part of the MimOffice project
   SPDX-FileCopyrightText: 2026 XI14 <marczxrr@gmail.com>

   SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef MIMOSTHEME_H
#define MIMOSTHEME_H

class QApplication;

/**
 *  @brief Applies the MimOS brand palette and chrome styling to a QApplication.
 *
 *  Recolors the palette and flattens/rounds toolbar, menu, and dialog button
 *  chrome to match the MimOS web identity, following the OS/Plasma light or
 *  dark color scheme and re-applying live if it changes.
 *
 *  Depends only on Qt (QApplication/QGuiApplication/QPalette/QStyleHints), so
 *  this header and its .cpp are compiled both into komain (reaching Words,
 *  Sheets, Stage, and Karbon) and directly into the launcher binary.
 */
namespace MimOSTheme
{
void apply(QApplication *app);
}

#endif // MIMOSTHEME_H
