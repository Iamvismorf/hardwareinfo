#pragma once
#include <QFile>
#include <QObject>
#include <QTimer>
#include <qqmlintegration.h>
#include <qtmetamacros.h>
class Cpu : public QObject {
  Q_OBJECT
  QML_SINGLETON
  QML_ELEMENT
  Q_PROPERTY(qreal cpuUsage READ cpuUsage NOTIFY cpuUsageChanged)

public:
  explicit Cpu(QObject *parent = nullptr);
  ~Cpu();

  qreal cpuUsage() const;
signals:
  void cpuUsageChanged();
public slots: // make this private function
  void updateCpuUsage();

private:
  qreal mCpuUsage = 0;
  qulonglong mLastTotalTime = 0;
  qulonglong mLastIdleTime = 0;
  QFile mFile;
  QTimer *mTimer = nullptr;
};
