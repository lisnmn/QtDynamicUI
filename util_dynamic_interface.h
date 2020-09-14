#ifndef UTILDYNAMICINTERFACEADV_H
#define UTILDYNAMICINTERFACEADV_H

#include <string>

#include <QBoxLayout>

#include "inifile.h"

class UtilDynamicInterface : public QObject {
    Q_OBJECT
public:
    UtilDynamicInterface(const std::string& filepath, QBoxLayout* layout);
    ~UtilDynamicInterface();
    void buildInterface();
    int saveIniFile();
    
private:
    QBoxLayout* mMainLayout;
    inifile::IniFile mIniFile;
};

#endif // UTILDYNAMICINTERFACEADV_H
