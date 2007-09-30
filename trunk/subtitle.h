#ifndef SUBTITLE_H
#define SUBTITLE_H

#include <QString>
#include <QTime>
#include <QList>
#include <QTextStream>
#include <QRegExp>

class Subtitle
{
public:
  Subtitle(int number, const QTime &startTime, const QTime &endTime, const QStringList &lines);

  int number() const { return _number; }         // Number of the subtitle
  QTime startTime() const { return _startTime; } // Start of the subtitle display
  QTime endTime() const { return _endTime; }     // End of the subtitle display
  QStringList lines() const { return _lines; }   // Subtitle in itself

  void shift(int milliseconds);

private:
  int _number;
  QTime _startTime;
  QTime _endTime;
  QStringList _lines;

  void shift(QTime &time, int milliseconds);
};

class Subtitles
{
public:
  Subtitles();

  // Load and parse <fileName> file
  void load(const QString &fileName);
  void save(const QString &fileName);

  const QList<Subtitle> &subtitles() const { return _subtitles; }

  // Operations
  void shift(int milliseconds); // If milliseconds is negative, backward subtitles, if positive, forward subtitles

private:
  QList<Subtitle> _subtitles;
  QRegExp _timesRegExp;
  int _parseCurrentLine;

  bool parseNextSubtitle(QTextStream &stream);
};

#endif
