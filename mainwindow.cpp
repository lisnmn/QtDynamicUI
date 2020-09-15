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

    dynamicUI.loadInterface("dialog_demo.ini", ui->verticalLayout);
    dynamicUI.buildInterface("parameters");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_submit_clicked() {
    // Submit
    if(!dynamicUI.saveIniFile()) {
        QMessageBox::information(this, "Success", "Saving iniFile successfully.");
    } else {
        QMessageBox::critical(this, "Error", "Saving iniFile failed!");
    }
}
