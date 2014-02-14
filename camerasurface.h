#ifndef CAMERASURFACE_H
#define CAMERASURFACE_H

#include <QAbstractVideoSurface>

class CameraSurface : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    explicit CameraSurface(QObject *parent = 0);

signals:

public slots:

};

#endif // CAMERASURFACE_H
