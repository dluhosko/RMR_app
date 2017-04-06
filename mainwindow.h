#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "navigation.h"
#include "irobotcreate.h"
#include "definitions.h"
#include "rplidar.h"
#include "definitions.h"
#include "grid_map.h"
#include "global_planner.h"
#include "mapping.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void showMB();
public:


    void forMsgBox(){emit showMB();}

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static int demoCallback(CreateSensors inputData,void *ioPointer);
        
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void on_pointButton_clicked();
    void on_turnButton_clicked();

    void showMessageBox()
            {
                QMessageBox Msgbox;
                Msgbox.setText("Save work and change Battery!");
                Msgbox.setIcon(QMessageBox::Critical);
                Msgbox.exec();
                exit(-1);
            }

private:
    Ui::MainWindow *ui;

    pthread_t threadHandleLidar; // handle na vlakno
    int threadLidarMapping;

};

#endif // MAINWINDOW_H
