#pragma once
#include <QObject>
#include <QRegularExpression>
#include <QtQmlIntegration>
#include <qqmlintegration.h>
#include <qtmetamacros.h>
class Ram : public QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON
  Q_PROPERTY(qulonglong totalRam READ totalRam NOTIFY totalRamChanged)
  Q_PROPERTY(qulonglong usedRam READ usedRam NOTIFY usedRamChanged)
  Q_PROPERTY(qreal utilization READ utilization NOTIFY utilizationChanged)

public:
  explicit Ram(QObject *parent = nullptr);
  ~Ram();
  qulonglong totalRam() const;
  qulonglong usedRam() const;
  qreal utilization() const;
signals:
  void totalRamChanged();
  void usedRamChanged();
  void utilizationChanged();

private:
  qulonglong mTotalRam = 0;
  qulonglong mUsedRam = 0;
  qreal mUtilization = 0;
  QFile mFile;
  QTimer *mTimer = nullptr;
  void updateUsedRam();
  void updateUtilization();
  qulonglong extractNumberFromLine(const QByteArray &line);
};
