#include <QMessageBox>
#include <QFile>

#include "subtitle.h"

#define QTIME_PATTERN "hh:mm:ss,zzz"

Subtitle::Subtitle(int number, const QTime &startTime, const QTime &endTime, const QStringList &lines) :
  _number(number),
  _startTime(startTime),
  _endTime(endTime),
  _lines(lines)
{
}

void Subtitle::move(int milliseconds)
{
  move(_startTime, milliseconds);
  move(_endTime, milliseconds);
}

void Subtitle::move(QTime &time, int milliseconds)
{
  if (milliseconds < 0 && time.msecsTo(QTime(0, 0)) > milliseconds)
    time.setHMS(0, 0, 0, 0);
  else
    time = time.addMSecs(milliseconds);
}

//////////////////////////
//////////////////////////
//////////////////////////

Subtitles::Subtitles()
{
#define TIME_PATTERN "(\\d\\d:\\d\\d:\\d\\d,\\d\\d\\d)"
  _timesRegExp.setPattern("^"TIME_PATTERN" --> "TIME_PATTERN"$");
}

void Subtitles::load(const QString &fileName)
{
  QFile file(fileName);
  if (!file.exists())
    return;

  // Open it...
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    QMessageBox::critical(0, QObject::tr("Error"), QObject::tr("Error while opening subtitles file"));
    return;
  }

  QTextStream stream(&file);

  // And parse it
  _subtitles.clear();
  _parseCurrentLine = 1;
  while (!stream.atEnd())
    if (!parseNextSubtitle(stream))
      break;
}

void Subtitles::save(const QString &fileName)
{
  QFile file(fileName);

  // Open it...
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
  {
    QMessageBox::critical(0, QObject::tr("Error"), QObject::tr("Error while opening subtitles file in write mode"));
    return;
  }

  QTextStream stream(&file);

  // Write all subtitles
  foreach (const Subtitle &subtitle, _subtitles)
  {
    // Number
    stream << QString::number(subtitle.number()) << endl;

    // Times
    stream << subtitle.startTime().toString(QTIME_PATTERN) << " --> " <<
              subtitle.endTime().toString(QTIME_PATTERN) << endl;

    // Subtitles
    foreach (const QString &str, subtitle.lines())
      stream << str << endl;

    // Empty line
    stream << endl;
  }
}

bool Subtitles::parseNextSubtitle(QTextStream &stream)
{
  // Number
  bool ok;
  int number = stream.readLine().toInt(&ok);
  if (!ok)
  {
    QMessageBox::critical(0, QObject::tr("Error"), QObject::tr("Error in SRT file (%1)").arg(_parseCurrentLine));
    return false;
  }

  _parseCurrentLine++;

  // Start --> End
  if (!_timesRegExp.exactMatch(stream.readLine()))
  {
    QMessageBox::critical(0, QObject::tr("Error"), QObject::tr("Error in SRT file (%1)").arg(_parseCurrentLine));
    return false;
  }

  _parseCurrentLine++;

  QTime startTime = QTime::fromString(_timesRegExp.cap(1), QTIME_PATTERN);
  QTime endTime = QTime::fromString(_timesRegExp.cap(2), QTIME_PATTERN);

  // Subtitle
  QStringList subtitle;
  QString str;
  while (!(str = stream.readLine()).isEmpty())
  {
    subtitle << str;
    _parseCurrentLine++;
  }
  _parseCurrentLine++;

  _subtitles << Subtitle(number, startTime, endTime, subtitle);

  return true;
}

void Subtitles::move(int milliseconds)
{
  for (int i = 0; i < _subtitles.count(); ++i)
    _subtitles[i].move(milliseconds);
}
