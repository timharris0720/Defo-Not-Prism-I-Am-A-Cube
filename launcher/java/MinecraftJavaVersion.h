#pragma once
#include <qstring.h>

class MinecraftVersion_Java : public QObject {
   private:
    QString m_MinecraftVersion;
    int m_MinecraftInt;
    QMap<QString, QString> data_windows;
   public:
    
    MinecraftVersion_Java(QString MinecraftVersion)
    {
        m_MinecraftVersion = MinecraftVersion;
        m_MinecraftInt = m_MinecraftVersion.replace(".", "").toInt();
        QString os = "windows";
        QString arch = "x64";
        data_windows["Java 8"] = "https://github.com/adoptium/temurin8-binaries/releases/download/jdk8u422-b05/OpenJDK8U-jre_" + arch + "_" + os + "_hotspot_8u422b05.zip";
        data_windows["Java 16"] = "https://github.com/adoptium/temurin16-binaries/releases/download/jdk-16.0.2%2B7/OpenJDK16U-jdk_" + arch + "_" + os + "_hotspot_16.0.2_7.zip";
        data_windows["Java 17"] = "https://github.com/adoptium/temurin17-binaries/releases/download/jdk-17.0.12%2B7/OpenJDK17U-jdk_" + arch + "_" + os + "_hotspot_17.0.12_7.zip";
        data_windows["Java 21"] = "https://github.com/adoptium/temurin21-binaries/releases/download/jdk-21.0.4%2B7/OpenJDK21U-jdk_" + arch + "_" + os + "_hotspot_21.0.4_7.zip";
    
    }
    QString GetMinecraftVersion() { return m_MinecraftVersion;}
    QString GetJavaVersionString()
    {
        qDebug() << "Minecraft version INT: " << m_MinecraftInt;

        if (m_MinecraftInt <= 999)
            m_MinecraftInt *= 10;


        if (m_MinecraftInt > 1 && m_MinecraftInt <= 1165)
            return "Java 8";
        if (m_MinecraftInt >= 1170 && m_MinecraftInt <= 1171)
            return "Java 16";
        if (m_MinecraftInt >= 1180 && m_MinecraftInt <= 1209)
            return "Java 17";
        if (m_MinecraftInt >= 1210)
            return "Java 21";
        else
            return "Error Getting Java Vesion for Minecraft version " + m_MinecraftVersion;
    }
    QString GetJavaVersionURL(QString JavaVers)
    {
        
        return data_windows[JavaVers];
    }
};