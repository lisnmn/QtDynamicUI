#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "util_dynamic_interface.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private slots:
    void on_pushButton_submit_clicked();
    
private:
    Ui::MainWindow *ui;
    UtilDynamicInterface* utilDynamicInterface;

};
#endif // MAINWINDOW_H
