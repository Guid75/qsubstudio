#include <QMainWindow>

#include "subtitle.h"

#include "ui_main_window.h"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
  Q_OBJECT
public:
  MainWindow(QWidget *parent = 0);

private:
  Subtitles _subtitles;

private slots:
  void on_actionQuit_triggered();
  void on_actionOpenSubtitles_triggered();
};
