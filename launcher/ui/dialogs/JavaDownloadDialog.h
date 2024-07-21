/* Copyright 2013-2021 MultiMC Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <QDialog>
#include <QSortFilterProxyModel>

#include "BaseVersionList.h"

class QVBoxLayout;
class QHBoxLayout;
class QDialogButtonBox;
class VersionSelectWidget;
class QPushButton;

namespace Ui {
class JavaDownloadDialog;
}

class JavaDownloadDialog : public QDialog {
    Q_OBJECT

   public:
    explicit JavaDownloadDialog(QString JavaVersionRequired, QString javaDownloadURL, QString title, QWidget* parent = 0, bool cancelable = true);
    virtual ~JavaDownloadDialog(){};

    int exec() override;

    BaseVersion::Ptr selectedVersion() const;

    void setCurrentVersion(const QString& version);
    void setFuzzyFilter(BaseVersionList::ModelRoles role, QString filter);
    void setExactFilter(BaseVersionList::ModelRoles role, QString filter);
    void setExactIfPresentFilter(BaseVersionList::ModelRoles role, QString filter);
    void setEmptyString(QString emptyString);
    void setEmptyErrorString(QString emptyErrorString);
    void setResizeOn(int column);

   private slots:
    void on_downloadButton_clicked();
    void on_okButton_clicked();

   private:
    void retranslate();
    void selectRecommended();

   private:
    QString m_currentVersion;
    QString m_windowTitle;
    QHBoxLayout* m_horizontalLayout = nullptr;
    QPushButton* m_downloadButton = nullptr;
    QPushButton* m_okButton = nullptr;

    int resizeOnColumn = -1;

    Task* loadTask = nullptr;
};
