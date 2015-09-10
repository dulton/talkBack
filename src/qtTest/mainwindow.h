#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "TalkbackCInterface.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();
    void on_get_buff();
    void on_startTalkback_clicked();

    void on_checkClientIsSupportTalkback_clicked();

    void on_pauseTalkback_clicked();

    void on_addDeviceToTalkback_clicked();

    void on_removeDeviceFromTalkback_clicked();

    void on_updateCode_clicked();

private:
    Ui::MainWindow *ui;
    QTimer m_tTime;
    tagTalkbackContext *m_pTalkbackContext;
};

#endif // MAINWINDOW_H
