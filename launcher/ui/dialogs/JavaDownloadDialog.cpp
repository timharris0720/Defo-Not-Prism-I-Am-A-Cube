#include "JavaDownloadDialog.h"
#include "Application.h"

#include <QDebug>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QFile>
#include <QDir>
#include <QEventLoop>
#include <QFileInfo>

#include <quazip.h>
#include <quazipfile.h>


#include "ui/widgets/VersionSelectWidget.h"

#include "BaseVersion.h"
#include "BaseVersionList.h"

namespace Ui {
class JavaDownloadDialog;
}


JavaDownloadDialog::JavaDownloadDialog(QString mcVersion, QString JavaVersionRequired, QString javaDownloadURL, QString title, QWidget* parent, bool cancelable)
    : QDialog(parent)
{
    m_DownloadURL = javaDownloadURL;
    m_windowTitle = title;
    setObjectName(QStringLiteral("JavaDownloadDialog"));
    resize(275, 100);
    
    m_TextLabel = new QLabel(this);
    m_TextLabel->setObjectName(QStringLiteral("textLabel"));
    m_TextLabel->setText(tr("The required Java version for minecraft version: ") + mcVersion + tr(" is ") + JavaVersionRequired + tr(" \nWould You like to download it?"));
    m_StatusLabel = new QLabel(this);
    m_StatusLabel->setObjectName(QStringLiteral("textLabel"));
    m_StatusLabel->setText(tr("Status: Not Yet Confirmed"));
    m_verticalLayout = new QVBoxLayout(this);
    m_verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

    m_horizontalLayout = new QHBoxLayout();
    m_horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));

    m_downloadButton = new QPushButton(this);
    m_downloadButton->setObjectName(QStringLiteral("downloadButton"));

    m_horizontalLayout->addWidget(m_downloadButton, Qt::AlignLeft);
    m_buttonBox = new QDialogButtonBox(this);
    m_buttonBox->setObjectName(QStringLiteral("buttonBox"));
    m_buttonBox->setOrientation(Qt::Horizontal);
    m_buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
    m_horizontalLayout->addWidget(m_buttonBox, Qt::AlignRight);

    m_verticalLayout->addWidget(m_TextLabel, Qt::AlignHCenter);
    m_verticalLayout->addWidget(m_StatusLabel, Qt::AlignHCenter);
    m_verticalLayout->addLayout(m_horizontalLayout);

    m_javaVersionRequired = JavaVersionRequired;
    m_downloadLocation = APPLICATION->applicationDirPath() + "/JavaVersions/ZIPTemp_" + JavaVersionRequired.replace(" ", "") + ".zip";
    m_unzipLocation = APPLICATION->applicationDirPath() + "/JavaVersions/" + JavaVersionRequired.replace(" ", "");
    retranslate();
    
    QMetaObject::connectSlotsByName(this);
    setWindowModality(Qt::WindowModal);
    setWindowTitle(m_windowTitle);
    connect(m_buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
}

void JavaDownloadDialog::retranslate()
{
    // FIXME: overrides custom title given in constructor!
    setWindowTitle(m_windowTitle);
    m_downloadButton->setToolTip(tr("Downloads the specified Minecraft Version."));
    m_downloadButton->setText(tr("&Download"));
    
}

void JavaDownloadDialog::setCurrentVersion(const QString& version)
{
    m_currentVersion = version;
}
void JavaDownloadDialog::download() {
    
    QDir dir2(m_unzipLocation);
    
    if (dir2.exists()) {
        qDebug() << "Java Already Exists: " << m_unzipLocation;
        m_javaLocationReturned = m_unzipLocation + "/" + dir2.entryList()[2] + "/bin/javaw.exe";
        m_StatusLabel->setText(tr("Status: Java Vesion Already Exists\n") + m_javaLocationReturned);
    } else {
        m_StatusLabel->setText(tr("Status: Downloading Java Zip\nThis can take some time depending on internet connection"));

        QNetworkAccessManager manager;
        QNetworkRequest request(m_DownloadURL);
        QNetworkReply* reply = manager.get(request);

        QEventLoop loop;
        QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        loop.exec();

        if (reply->error() != QNetworkReply::NoError) {
            qWarning() << "[Downloading Java Version: " << m_javaVersionRequired << " ] - Error downloading file:" << reply->errorString();
            return;
        }
        QFile file(m_downloadLocation);
        QDir dir = QFileInfo(file).absoluteDir();
        // Ensure the directory exists
        if (!dir.exists()) {
            if (!dir.mkpath(".")) {
                qWarning() << "[Downloading Java Version:" << m_javaVersionRequired
                           << " ] - Error creating directory for download:" << dir.absolutePath();
                return;
            }
        }

        if (!file.open(QIODevice::WriteOnly)) {
            qDebug() << "[Downloading Java Version: " << m_javaVersionRequired
                     << " ] - Error opening file for writing:" << file.errorString();
            return;
        }

        file.write(reply->readAll());
        file.close();
        reply->deleteLater();
        qDebug() << "[Downloading Java Version: " << m_javaVersionRequired << " ] Finished Downloading the file";
        m_StatusLabel->setText(tr("Status: Finished Downloading Java Zip"));
        unzip();
    }
    
}
void JavaDownloadDialog::unzip() {
    m_StatusLabel->setText(tr("Status: Unzipping"));
    QuaZip zip(m_downloadLocation);
    if (!zip.open(QuaZip::mdUnzip)) {
        qWarning() << "Error opening ZIP file";
        m_StatusLabel->setText(tr("Error Has Occured: Opening The ZIP File"));
        return;
    }

    QuaZipFile file(&zip);
    bool firstRun = true;
    for (bool more = zip.goToFirstFile(); more; more = zip.goToNextFile()) {
        QString name = zip.getCurrentFileName();
        QFileInfo fileInfo(m_unzipLocation + QDir::separator() + name);
        //qWarning() << "ZIP CONTENTS: " << fileInfo.absoluteFilePath();
        QDir dir = fileInfo.absoluteDir();
        if (!dir.exists()) {
            dir.mkpath(".");
        }    
        else {
            if (!file.open(QIODevice::ReadOnly)) {
                qWarning() << "Error opening file inside ZIP:" << name;
                m_StatusLabel->setText(tr("Error Has Occured: Opening File Inside ZIP"));
                return;
            }

            QFile outFile(fileInfo.absoluteFilePath());
            if (!outFile.open(QIODevice::WriteOnly)) {
                qWarning() << "Error opening output file: " << fileInfo.absolutePath() << " REASON: " << outFile.errorString();
                m_StatusLabel->setText(tr("Error Has Occured: Opening Output file when unzipping"));
                file.close(); 
                return;
            }
            
            outFile.write(file.readAll());
            file.close();
            outFile.close();
        }
    }
    zip.close();
    qDebug() << "[UNZIPPING Java Version: " << m_javaVersionRequired << " ] Finished Unzipping From Path " << m_downloadLocation;
    
}
int JavaDownloadDialog::exec()
{
    QDialog::open();
    return QDialog::exec();
}
void JavaDownloadDialog::on_downloadButton_clicked()
{
    m_downloadButton->setText(tr("&Download"));
    qDebug() << "Downloading Java Using: " << m_DownloadURL;
    qDebug() << "Downloading Java To   : " << m_downloadLocation;
    download();
    m_StatusLabel->setText(tr("Completed You Can now Close This Dialog"));
    QDir DownloadDir(APPLICATION->applicationDirPath() + "/JavaVersions/");
    DownloadDir.remove("ZIPTemp_" + m_javaVersionRequired.replace(" ", "") + ".zip");
    //this->close();
}
QString JavaDownloadDialog::getJavaInstallLocation() {
    return m_javaLocationReturned;
}

