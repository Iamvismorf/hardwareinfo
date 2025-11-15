#include "../include/Cpu.hpp"
#include <QDebug>
#include <QFile>
#include <QTimer>

Cpu::Cpu(QObject *parent)
    : QObject(parent), mFile("/proc/stat"), mTimer(new QTimer(this)) {
  if (!mFile.open(QIODevice::ReadOnly)) {
    qDebug() << "something went wrong!";
    return;
  }
  connect(mTimer, &QTimer::timeout, this, &Cpu::updateCpuUsage);
  updateCpuUsage();
  mTimer->start(1000);
}
Cpu::~Cpu() { mFile.close(); }
qreal Cpu::cpuUsage() const { return mCpuUsage; }
void Cpu::updateCpuUsage() {
  mFile.seek(0);
  qulonglong totalTime = 0;
  qulonglong idleTime = 0;

  QList<QByteArray> fLine = mFile.readLine().mid(3).simplified().split(' ');
  for (const auto &time : fLine) {
    totalTime += time.toULongLong();
  }
  idleTime = fLine.at(3).toULongLong();

  qulonglong deltaTotalTime = totalTime - mLastTotalTime;
  qulonglong deltaIdleTime = idleTime - mLastIdleTime;

  mCpuUsage =
      100 * static_cast<qreal>(deltaTotalTime - deltaIdleTime) / deltaTotalTime;
  mLastTotalTime = totalTime;
  mLastIdleTime = idleTime;
  emit cpuUsageChanged();
}
