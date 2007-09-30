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
