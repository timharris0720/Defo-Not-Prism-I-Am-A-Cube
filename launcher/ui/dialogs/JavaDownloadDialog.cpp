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
    m_buttonBox->setStandardButtons(QDialogButtonBox::Cancel);
    m_horizontalLayout->addWidget(m_buttonBox, Qt::AlignRight);

    m_verticalLayout->addWidget(m_TextLabel, Qt::AlignHCenter);
    m_verticalLayout->addLayout(m_horizontalLayout);
    
    retranslate();

    QMetaObject::connectSlotsByName(this);
    setWindowModality(Qt::WindowModal);
    setWindowTitle(m_windowTitle);
    connect(m_buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
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

int JavaDownloadDialog::exec()
{
    QDialog::open();
    return QDialog::exec();
}
void JavaDownloadDialog::on_downloadButton_clicked()
{
    m_downloadButton->setText(tr("&Download"));
    qDebug() << "Downloading Java Using: " << m_DownloadURL;
}

