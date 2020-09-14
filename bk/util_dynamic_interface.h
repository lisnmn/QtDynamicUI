#ifndef UTILDYNAMICINTERFACE_H
#define UTILDYNAMICINTERFACE_H

#include <QString>
#include <QBoxLayout>

#include "rapidjson/document.h"
#include "inifile.h"

class UtilDynamicInterface {
public:
    UtilDynamicInterface(QString filepath, QBoxLayout *layout);
    
    inifile::IniFile getIniFile() const;
    
private:
    void BuildInterface(rapidjson::Value& value,QBoxLayout *current_layout);
    rapidjson::Document document;
    QBoxLayout *main_layout;
    inifile::IniFile iniFile;
};

#endif // UTILDYNAMICINTERFACE_H
