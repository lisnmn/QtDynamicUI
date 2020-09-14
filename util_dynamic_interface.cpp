#include "util_dynamic_interface.h"

#include <float.h>

#include <QDebug>
#include <QFile>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QFileDialog>

#include "inifile.h"

UtilDynamicInterface::UtilDynamicInterface(const std::string& filepath, QBoxLayout *layout) {
    if(mIniFile.Load(filepath)) {
        qDebug() << "Loading " << filepath.c_str() << " failed!";
    }
    mMainLayout = layout;
}

UtilDynamicInterface::~UtilDynamicInterface() {
    // mIniFile.Save();
    mMainLayout = nullptr;
}

void UtilDynamicInterface::buildInterface() {
    const char* section_name = "parameters";
    inifile::IniSection* section = mIniFile.getSection(section_name);
    for(auto it = section->begin(); it != section->end(); it++) {
        // [key] = [value]
        // [key] => [type]_[name]
        QString key = QString::fromStdString(it->key);
        QString value = QString::fromStdString(it->value);
        QString type = key.split('_')[0];
        QString name = key.split('_')[1];
        
        QHBoxLayout* horizontalLayout = new QHBoxLayout();

        QLabel* label = new QLabel(name);
        horizontalLayout->addWidget(label);
        
        if(type == "int") {
            QSpinBox* spinBox = new QSpinBox();
            spinBox->setRange(INT_MIN,INT_MAX);
            spinBox->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
            spinBox->setValue(value.toInt());
            // A wise way provided by "Qt Help"(Press F1 at valueChanged).
            connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), [this, key, section_name](int i) {
                this->mIniFile.SetIntValue(section_name, key.toStdString(), i);
            });
            horizontalLayout->addWidget(spinBox);
        } else if(type == "double") {
            QDoubleSpinBox* doubleSpinBox = new QDoubleSpinBox();
            doubleSpinBox->setRange(DBL_MIN,DBL_MAX);
            doubleSpinBox->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
            doubleSpinBox->setValue(value.toDouble());
            // A wise way provided by "Qt Help"(Press F1 at valueChanged).
            connect(doubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [this, key, section_name](double d) {
                this->mIniFile.SetDoubleValue(section_name, key.toStdString(), d);
            });
            horizontalLayout->addWidget(doubleSpinBox);
        } else if(type == "string") {
            QLineEdit* lineEdit = new QLineEdit(value);
            lineEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
            // A wise way provided by "Qt Help"(Press F1 at textChanged).
            connect(lineEdit, QOverload<const QString&>::of(&QLineEdit::textChanged), [this, key, section_name](const QString& text) {
                this->mIniFile.SetStringValue(section_name, key.toStdString(), text.toStdString());
            });
            horizontalLayout->addWidget(lineEdit);
        } else if(type == "bool") {
            QCheckBox* checkBox = new QCheckBox();
            if(value == "true") {
                checkBox->setChecked(true);
            } else {
                checkBox->setChecked(false);
            }
            // A wise way provided by "Qt Help"(Press F1 at stateChanged).
            connect(checkBox, QOverload<int>::of(&QCheckBox::stateChanged), [this, key, section_name](int i) {
                this->mIniFile.SetBoolValue(section_name, key.toStdString(), i);
            });
            horizontalLayout->addWidget(checkBox);
        } else if(type == "file") {
            QLineEdit* lineEdit = new QLineEdit(value);
            lineEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
            // A wise way provided by "Qt Help"(Press F1 at textChanged).
            connect(lineEdit, QOverload<const QString&>::of(&QLineEdit::textChanged), [this, key, section_name](const QString& text) {
                this->mIniFile.SetStringValue(section_name, key.toStdString(), text.toStdString());
            });
            
            QPushButton* pushButton = new QPushButton("Browser");
            pushButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            connect(pushButton, QOverload<const bool>::of(&QPushButton::clicked), [lineEdit, key](const bool) {
                QString filePath = QFileDialog::getOpenFileName(nullptr, "Please select a file: ", key);
                if(!filePath.isEmpty()) {
                    lineEdit->setText(filePath);
                }
                
            });
            
            horizontalLayout->addWidget(lineEdit);
            horizontalLayout->addWidget(pushButton);
        } else if(type == "folder") {
            QLineEdit* lineEdit = new QLineEdit(value);
            lineEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
            // A wise way provided by "Qt Help"(Press F1 at textChanged).
            connect(lineEdit, QOverload<const QString&>::of(&QLineEdit::textChanged), [this, key, section_name](const QString& text) {
                this->mIniFile.SetStringValue(section_name, key.toStdString(), text.toStdString());
            });
            
            QPushButton* pushButton = new QPushButton("Browser");
            pushButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            connect(pushButton, QOverload<const bool>::of(&QPushButton::clicked), [lineEdit, key](const bool) {
                QString filePath = QFileDialog::getExistingDirectory(nullptr, "Please select a folder: ", key, QFileDialog::ShowDirsOnly);
                if(!filePath.isEmpty()) {
                    lineEdit->setText(filePath);
                }
                
            });
            
            horizontalLayout->addWidget(lineEdit);
            horizontalLayout->addWidget(pushButton);
            
        }
        mMainLayout->addLayout(horizontalLayout);
    }
}

int UtilDynamicInterface::saveIniFile() {
    return mIniFile.Save();
}
