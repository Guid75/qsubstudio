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

  void refreshSubtitles();

private slots:
  void on_actionQuit_triggered();
  void on_actionOpenSubtitles_triggered();
  void on_sliderMilliseconds_valueChanged(int value);
  void on_sliderSeconds_valueChanged(int value);
  void on_sliderMinutes_valueChanged(int value);
};
