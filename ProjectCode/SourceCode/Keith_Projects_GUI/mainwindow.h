#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_buttonTakePictures_clicked();

    void on_takeTestPics_clicked();

    void on_calibrateCams_clicked();

    void on_checkImgRectification_clicked();

    void on_clearAllPicsTaken_clicked();

    void on_clearCalibrationFiles_clicked();

    void on_RecordVid_clicked();

    void on_cearAllVideos_clicked();

    void on_checkVidDistance_clicked();

    void on_testDistanceInVids_clicked();

    void on_MainWindow_iconSizeChanged(const QSize &iconSize);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
