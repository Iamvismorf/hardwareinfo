#pragma once
#include <QFile>
#include <QObject>
#include <qqmlintegration.h>
#include <qtmetamacros.h>
class Cpu : public QObject {
  Q_OBJECT
  QML_SINGLETON
  QML_ELEMENT
  Q_PROPERTY(double cpuUsage READ cpuUsage NOTIFY cpuUsageChanged)

public:
  explicit Cpu(QObject *parent = nullptr);

  double cpuUsage() const;
signals:
  void cpuUsageChanged();
public slots:
  void updateCpuUsage();

private:
  double mCpuUsage = 0;
  qulonglong mLastTotalTime = 0;
  qulonglong mLastIdleTime = 0;
  QFile mFile;
};
