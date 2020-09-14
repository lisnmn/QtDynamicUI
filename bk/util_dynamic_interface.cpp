#include "util_dynamic_interface.h"

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QBoxLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QByteArray>

using namespace inifile;

UtilDynamicInterface::UtilDynamicInterface(QString filepath, QBoxLayout *layout)
{
    QFile json_file(filepath);
    if(!json_file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "打开json文件失败!" << endl;
    }
    QTextStream in(&json_file);
    QString text = in.readAll();
    json_file.close();
    document.Parse<rapidjson::kParseDefaultFlags>(text.toLatin1().data());
    if(document.HasParseError() || !document.IsObject())
    {
        qDebug() << "解析json文件失败!" << endl;
    }
    main_layout = layout;
    BuildInterface(document, layout);
}

void UtilDynamicInterface::BuildInterface(rapidjson::Value& object, QBoxLayout *current_layout)
{
    QString section("demo");
    
    QString type(object["type"].GetString());
    if(type == "VerticalLayout")
    {
        QVBoxLayout *vertical_layout = new QVBoxLayout();
        current_layout->addLayout(vertical_layout);
        for(unsigned int i=0;i < object["item"].Size();i++)
        {
            BuildInterface(object["item"][i],vertical_layout);
        }
    }
    else if(type == "HorizontalLayout")
    {
        QHBoxLayout *horizontal_layout = new QHBoxLayout();
        current_layout->addLayout(horizontal_layout);
        for(unsigned int i=0;i < object["item"].Size();i++)
        {
            BuildInterface(object["item"][i],horizontal_layout);
        }
    }
    else if(type == "Label")
    {
        QLabel *label = new QLabel();
        label->setText(object["text"].GetString());
        current_layout->addWidget(label);
    }
    else if(type == "LineEdit")
    {
        QLineEdit *line_edit = new QLineEdit();
        line_edit->setObjectName(object["name"].GetString());
        line_edit->setText(object["text"].GetString());
        line_edit->setPlaceholderText(object["placeHolderText"].GetString());
        current_layout->addWidget(line_edit);
        iniFile.SetStringValue(section.toStdString(), object["name"].GetString(), object["text"].GetString());
    }
    else if(type == "PushButton")
    {
        QPushButton *push_button = new QPushButton();
        push_button->setObjectName(object["name"].GetString());
        push_button->setText(object["text"].GetString());
        current_layout->addWidget(push_button);
    }
    else if(type == "RadioButton")
    {
        QRadioButton *radio_button = new QRadioButton();
        radio_button->setObjectName(object["name"].GetString());
        radio_button->setText(object["text"].GetString());
        current_layout->addWidget(radio_button);
    }
    else if(type == "ComboBox")
    {
        QComboBox *combo_box = new QComboBox();
        combo_box->setObjectName(object["name"].GetString());
        for(unsigned int i = 0;i < object["item"].Size();i++)
        {
            combo_box->addItem(object["item"][i].GetString());
        }
        current_layout->addWidget(combo_box);
        
        iniFile.SetStringValue(section.toStdString(), object["name"].GetString(), object["item"][0].GetString());
    }
    else if(type == "SpinBox")
    {
        QSpinBox *spin_box = new QSpinBox();
        spin_box->setObjectName(object["name"].GetString());
        spin_box->setSuffix(object["suffix"].GetString());
        spin_box->setMinimum(object["minimum"].GetInt());
        spin_box->setMaximum(object["maximum"].GetInt());
        spin_box->setValue(object["value"].GetInt());
        current_layout->addWidget(spin_box);
        
        iniFile.SetIntValue(section.toStdString(), object["name"].GetString(), object["value"].GetInt());
    }
    else if(type == "DoubleSpinBox")
    {
        QDoubleSpinBox *double_spin_box = new QDoubleSpinBox();
        double_spin_box->setObjectName(object["name"].GetString());
        double_spin_box->setSuffix(object["suffix"].GetString());
        double_spin_box->setDecimals(object["decimals"].GetInt());
        double_spin_box->setMinimum(object["minimum"].GetDouble());
        double_spin_box->setMaximum(object["maximum"].GetDouble());
        double_spin_box->setValue(object["value"].GetDouble());
        current_layout->addWidget(double_spin_box);
        
        iniFile.SetDoubleValue(section.toStdString(), object["name"].GetString(), object["value"].GetDouble());
    }
}

inifile::IniFile UtilDynamicInterface::getIniFile() const
{
    return iniFile;
}

