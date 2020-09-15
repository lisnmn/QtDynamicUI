#ifndef UTILDYNAMICINTERFACEADV_H
#define UTILDYNAMICINTERFACEADV_H

#include <QBoxLayout>

#include "inifile.h"

class DynamicUI : public QObject {
    Q_OBJECT
public:
    DynamicUI();
    ~DynamicUI();
    void loadInterface(const char* filepath, QBoxLayout* layout);
    void buildInterface(const char* sectionName);
    int saveIniFile();
    
private:
    QBoxLayout* mMainLayout;
    inifile::IniFile mIniFile;
};

#endif // UTILDYNAMICINTERFACEADV_H
