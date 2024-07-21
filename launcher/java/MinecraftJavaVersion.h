#pragma once
#include <qstring.h>

class MinecraftVersion_Java : public QObject {
   private:
    QString m_MinecraftVersion;
    int m_MinecraftInt;
    QString m_JavaVersion;
    QMap<QString, QString> data_windows;
   public:
    
    MinecraftVersion_Java(QString MinecraftVersion)
    {
        m_MinecraftVersion = MinecraftVersion;
        m_MinecraftInt = m_MinecraftVersion.replace(".", "").toInt();
        
        data_windows["Java 8"] = "https://adoptium.net/temurin/releases/?os=windows&arch=x64&package=jre&version=8";
        data_windows["Java 16"] = "https://adoptium.net/temurin/releases/?os=windows&arch=x64&package=jre&version=16";
        data_windows["Java 17"] = "https://adoptium.net/temurin/releases/?os=windows&arch=x64&package=jre&version=17";
        data_windows["Java 21"] = "https://adoptium.net/temurin/releases/?os=windows&arch=x64&package=jre&version=21";
    }
    
    QString GetJavaVersionString()
    {
        if (m_MinecraftInt <= 1165)
            return "Java 8";
        if (m_MinecraftInt >= 1170 && m_MinecraftInt >= 1171)
            return "Java 16";
        if (m_MinecraftInt >= 1180 && m_MinecraftInt >= 1209)
            return "Java 17";
        if (m_MinecraftInt >= 1210)
            return "Java 21";
        else
            return "we dk";
    }
    QString GetJavaVersionURL(QString JavaVers)
    {
        
        return data_windows[JavaVers];
    }
    QString GetJavaVersionURL() 
    {
        return data_windows[m_JavaVersion];
    }
};