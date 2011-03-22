#ifndef MARTLETSETTINGS_H
#define MARTLETSETTINGS_H

#include <QObject>
#include <QSettings>

class MartletSettings : public QObject
{
    Q_OBJECT
    explicit MartletSettings(QObject *parent = 0);
public:
    static MartletSettings& instance();

    static QSettings& settings();

signals:

public slots:

private:
    QSettings m_settings;
    static MartletSettings* m_instance;
};

#endif // MARTLETSETTINGS_H
