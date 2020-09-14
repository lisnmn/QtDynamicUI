#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDialog>
#include <QMessageBox>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDir>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    utilDynamicInterface = new UtilDynamicInterface("dialog_demo.ini", ui->verticalLayout);
    utilDynamicInterface->buildInterface();
}

MainWindow::~MainWindow() {
    delete ui;
    delete utilDynamicInterface;
}

void MainWindow::on_pushButton_submit_clicked() {
    // Submit
    if(!utilDynamicInterface->saveIniFile()) {
        QMessageBox::information(this, "Success", "Saving iniFile successfully.");
    } else {
        QMessageBox::critical(this, "Error", "Saving iniFile failed!");
    }
}
