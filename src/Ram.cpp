#include <../include/Ram.hpp>
#include <QDebug>
#include <QFile>
#include <QRegularExpression>
Ram::Ram(QObject *parent)
    : QObject(parent), mFile("/proc/meminfo"), mTimer(new QTimer(this)) {
  if (!mFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
    return;
  }
  mTotalRam = extractNumberFromLine(mFile.readLine());
  connect(this, &Ram::usedRamChanged, this, &Ram::updateUtilization);
  connect(mTimer, &QTimer::timeout, this, &Ram::updateUsedRam);
  updateUsedRam();
  mTimer->start(1000);
}
Ram::~Ram() { mFile.close(); }
qulonglong Ram::extractNumberFromLine(const QByteArray &line) {
  QRegularExpression re("\\d+(?= kb)",
                        QRegularExpression::CaseInsensitiveOption);
  return re.match(line).captured(0).toULongLong();
}
void Ram::updateUtilization() {
  mUtilization = static_cast<qreal>(mUsedRam) / mTotalRam;
  emit utilizationChanged();
}
void Ram::updateUsedRam() {
  mFile.seek(0);
  for (size_t i = 0; i < 2; ++i) {
    mFile.readLine();
  }
  qulonglong memAvailable = extractNumberFromLine(mFile.readLine());
  mUsedRam = mTotalRam - memAvailable;
  emit usedRamChanged();
}
qulonglong Ram::totalRam() const { return mTotalRam; }
qulonglong Ram::usedRam() const { return mUsedRam; }
qreal Ram::utilization() const { return mUtilization; }
