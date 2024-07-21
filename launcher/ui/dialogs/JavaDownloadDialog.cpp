// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Prism Launcher - Minecraft Launcher
 *  Copyright (C) 2023 TheKodeToad <TheKodeToad@proton.me>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 3.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *
 *      Copyright 2013-2021 MultiMC Contributors
 *
 *      Licensed under the Apache License, Version 2.0 (the "License");
 *      you may not use this file except in compliance with the License.
 *      You may obtain a copy of the License at
 *
 *          http://www.apache.org/licenses/LICENSE-2.0
 *
 *      Unless required by applicable law or agreed to in writing, software
 *      distributed under the License is distributed on an "AS IS" BASIS,
 *      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *      See the License for the specific language governing permissions and
 *      limitations under the License.
 */

#include "JavaDownloadDialog.h"

#include <QDebug>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

#include "ui/widgets/VersionSelectWidget.h"

#include "BaseVersion.h"
#include "BaseVersionList.h"

JavaDownloadDialog::JavaDownloadDialog(QString JavaVersionRequired, QString javaDownloadURL, QString title, QWidget* parent, bool cancelable)
    : QDialog(parent)
{

    m_windowTitle = title;
    setObjectName(QStringLiteral("JavaDownloadDialog"));
    resize(400, 347);
       
    m_horizontalLayout = new QHBoxLayout();
    m_horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));

    m_downloadButton = new QPushButton(this);
    m_downloadButton->setObjectName(QStringLiteral("downloadButton"));
    m_okButton = new QPushButton(this);
    m_okButton->setObjectName(QStringLiteral("okButton"));
    m_horizontalLayout->addWidget(m_downloadButton);
    m_horizontalLayout->addWidget(m_okButton);

    
    retranslate();

    QMetaObject::connectSlotsByName(this);
    setWindowModality(Qt::WindowModal);
    setWindowTitle(m_windowTitle);

}

void JavaDownloadDialog::retranslate()
{
    // FIXME: overrides custom title given in constructor!
    setWindowTitle(m_windowTitle);
    m_downloadButton->setToolTip(tr("Reloadsaa the version list."));
    m_downloadButton->setText(tr("&Download"));
}

void JavaDownloadDialog::setCurrentVersion(const QString& version)
{
    m_currentVersion = version;
}

int JavaDownloadDialog::exec()
{
    QDialog::open();
    return QDialog::exec();
}



void JavaDownloadDialog::on_downloadButton_clicked()
{
    m_downloadButton->setText(tr("&Download asd"));
}
void JavaDownloadDialog::on_okButton_clicked()
{
    m_downloadButton->setText(tr("&Download asd"));
}

