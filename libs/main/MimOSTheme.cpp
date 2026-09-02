/* This file is part of the MimOffice project
   SPDX-FileCopyrightText: 2026 XI14 <marczxrr@gmail.com>

   SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "MimOSTheme.h"

#include <QApplication>
#include <QByteArray>
#include <QColor>
#include <QGuiApplication>
#include <QLatin1String>
#include <QObject>
#include <QPalette>
#include <QStyleHints>

namespace MimOSTheme
{
namespace
{

// Tokens sourced from Web-mimOS's .design-sync/src/tokens/colors.css, the
// canonical MimOS brand palette shared with the website. Keep these in sync
// with that file rather than re-deriving values here.

QPalette lightPalette()
{
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(0xF8, 0xF4, 0xFF)); // nube
    palette.setColor(QPalette::Base, QColor(0xFF, 0xFF, 0xFF));
    palette.setColor(QPalette::AlternateBase, QColor(0xFF, 0xF0, 0xF5)); // miel
    palette.setColor(QPalette::WindowText, QColor(0x15, 0x13, 0x20)); // cta-text
    palette.setColor(QPalette::Text, QColor(0x15, 0x13, 0x20));
    palette.setColor(QPalette::Button, QColor(0xF8, 0xF4, 0xFF));
    palette.setColor(QPalette::ButtonText, QColor(0x15, 0x13, 0x20));
    palette.setColor(QPalette::Highlight, QColor(0x74, 0x52, 0xF5)); // accessible abrazo fill
    palette.setColor(QPalette::HighlightedText, QColor(0x15, 0x13, 0x20));
    palette.setColor(QPalette::Link, QColor(0x5B, 0x3B, 0xE0)); // prose-purple
    palette.setColor(QPalette::ToolTipBase, QColor(0xB8, 0xA8, 0xFF)); // abrazo-light
    palette.setColor(QPalette::ToolTipText, QColor(0x15, 0x13, 0x20));
    palette.setColor(QPalette::Disabled, QPalette::Text, QColor(0x6B, 0x5E, 0x80)); // secondary-text
    palette.setColor(QPalette::Disabled, QPalette::WindowText, QColor(0x6B, 0x5E, 0x80));
    palette.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(0x6B, 0x5E, 0x80));
    return palette;
}

QPalette darkPalette()
{
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(0x1A, 0x0F, 0x1E)); // noche
    palette.setColor(QPalette::Base, QColor(0x2A, 0x19, 0x32)); // noche-soft
    palette.setColor(QPalette::AlternateBase, QColor(0x2A, 0x19, 0x32));
    palette.setColor(QPalette::WindowText, QColor(0xF8, 0xF4, 0xFF));
    palette.setColor(QPalette::Text, QColor(0xF8, 0xF4, 0xFF));
    palette.setColor(QPalette::Button, QColor(0x2A, 0x19, 0x32));
    palette.setColor(QPalette::ButtonText, QColor(0xF8, 0xF4, 0xFF));
    palette.setColor(QPalette::Highlight, QColor(0x74, 0x52, 0xF5)); // accessible abrazo fill
    palette.setColor(QPalette::HighlightedText, QColor(0x15, 0x13, 0x20));
    palette.setColor(QPalette::Link, QColor(0xB3, 0xA2, 0xFF)); // prose-purple-dark
    palette.setColor(QPalette::ToolTipBase, QColor(0x5B, 0x3F, 0xD9)); // abrazo-dark
    palette.setColor(QPalette::ToolTipText, QColor(0xF8, 0xF4, 0xFF));
    palette.setColor(QPalette::Disabled, QPalette::Text, QColor(0xA8, 0x9F, 0xB8)); // secondary-text-light
    palette.setColor(QPalette::Disabled, QPalette::WindowText, QColor(0xA8, 0x9F, 0xB8));
    palette.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(0xA8, 0x9F, 0xB8));
    return palette;
}

// Scoped strictly to toolbar/menu/dialog chrome. Deliberately no "*",
// QFrame, or QWidget selectors: Calligra relies on Breeze-specific dynamic
// properties (_breeze_force_frame and friends, see e.g. libs/main/KoView.cpp)
// that a blanket selector would clobber.
const char kMimOSQss[] = R"qss(
KToolBar {
    border: none;
    spacing: 4px;
    padding: 2px;
}
QToolButton {
    border: none;
    border-radius: 6px;
    padding: 4px;
    background: transparent;
}
QToolButton:hover {
    background: rgba(124, 92, 252, 40);
}
QToolButton:pressed, QToolButton:checked {
    background: rgba(124, 92, 252, 80);
}
QMenuBar {
    border: none;
    background: transparent;
}
QMenuBar::item {
    border-radius: 6px;
    padding: 4px 8px;
    background: transparent;
}
QMenuBar::item:selected {
    background: rgba(124, 92, 252, 40);
}
QMenu {
    border: 1px solid rgba(124, 92, 252, 60);
    border-radius: 8px;
    padding: 4px;
}
QMenu::item {
    border-radius: 6px;
    padding: 4px 24px 4px 8px;
}
QMenu::item:selected {
    background: rgba(124, 92, 252, 40);
}
QPushButton {
    border: 1px solid rgba(124, 92, 252, 60);
    border-radius: 6px;
    padding: 4px 12px;
}
QPushButton:default {
    background: #7452F5;
    color: #FFFFFF;
    border: none;
}
QPushButton:hover {
    background: rgba(124, 92, 252, 40);
}
QPushButton:default:hover {
    background: #8B72FF;
}
QPushButton:focus, QToolButton:focus {
    outline: none;
    border: 1px solid #70D6C5;
}
QDialogButtonBox QPushButton {
    min-width: 72px;
}
)qss";

void applyForScheme(QApplication *app, Qt::ColorScheme scheme)
{
    static const QPalette light = lightPalette();
    static const QPalette dark = darkPalette();

    app->setPalette(scheme == Qt::ColorScheme::Dark ? dark : light);
    app->setStyleSheet(QLatin1String(kMimOSQss));
}

} // namespace

void apply(QApplication *app)
{
    // Manual override for environments without a desktop color-scheme
    // portal to toggle live (headless testing). Not a shipped user-facing
    // setting.
    const QByteArray forced = qgetenv("MIMOFFICE_FORCE_COLOR_SCHEME");
    if (forced == "dark") {
        applyForScheme(app, Qt::ColorScheme::Dark);
        return;
    }
    if (forced == "light") {
        applyForScheme(app, Qt::ColorScheme::Light);
        return;
    }

    applyForScheme(app, QGuiApplication::styleHints()->colorScheme());

    QObject::connect(QGuiApplication::styleHints(), &QStyleHints::colorSchemeChanged, app, [app](Qt::ColorScheme scheme) {
        applyForScheme(app, scheme);
    });
}

} // namespace MimOSTheme
