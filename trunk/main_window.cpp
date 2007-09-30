#include <QFileDialog>

#include "main_window.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
  setupUi(this);
}

void MainWindow::on_actionQuit_triggered()
{
  qApp->quit();
}

void MainWindow::on_actionOpenSubtitles_triggered()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Select a subtitles file"),
                                                  QString(), tr("Subtitles file (*.srt)"));

  if (fileName.isNull())
    return;

  _subtitles.load(fileName);
}

void MainWindow::refreshSubtitles()
{
  int milliseconds = sliderMinutes->value() * 60 * 1000 + sliderSeconds->value() * 1000 + sliderMilliseconds->value() * 100;

  spinBoxShift->setValue(milliseconds);

  labelResult->setText(QTime(0,0).addMSecs(milliseconds).toString("hh:mm:ss,zzz"));
}

void MainWindow::on_sliderMilliseconds_valueChanged(int value)
{
  refreshSubtitles();
}

void MainWindow::on_sliderSeconds_valueChanged(int value)
{
  refreshSubtitles();
}

void MainWindow::on_sliderMinutes_valueChanged(int value)
{
  refreshSubtitles();
}
