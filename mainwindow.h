#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <tree.h>
#include "hafman.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    tree t;

    int out = 0;

    hafman H;

private slots:

    void on_goCrypt_clicked();

    void on_goDecrypt_clicked();

    void on_goCryptH_clicked();

    void on_goDecryptH_clicked();

    void on_goCrypt_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_actionOpen_File_triggered();

    void on_actionABC_triggered();

    void on_actionRandom_triggered();

    void on_actionCode_from_file_triggered();

    void on_actionDecode_from_file_triggered();

    void on_actionSave_all_to_file_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
