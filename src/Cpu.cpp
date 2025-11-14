#include "../include/Cpu.hpp"
#include <QDebug>
#include <QFile>
#include <QTimer>

Cpu::Cpu(QObject *parent) : QObject(parent), mFile("/proc/stat") {}
double Cpu::cpuUsage() const { return mCpuUsage; }
void Cpu::updateCpuUsage() {
  if (!mFile.open(QIODevice::ReadOnly)) {
    qDebug() << "something went wrong!";
    return;
  }
  qulonglong totalTime = 0;
  qulonglong idleTime = 0;
  double currentCpuUsage;
  QList<QByteArray> fLine = mFile.readLine().mid(3).simplified().split(' ');
  for (const auto &time : fLine) {
    totalTime += time.toULongLong();
  }
  idleTime = fLine.at(3).toULongLong();

  qulonglong deltaTotalTime = totalTime - mLastTotalTime;
  qulonglong deltaIdleTime = idleTime - mLastIdleTime;

  mCpuUsage = 100 * static_cast<double>(deltaTotalTime - deltaIdleTime) /
              deltaTotalTime;
  mLastTotalTime = totalTime;
  mLastIdleTime = idleTime;
  mFile.close();
  emit cpuUsageChanged();
}
