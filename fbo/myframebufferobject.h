/****************************************************************************
**
** Copyright (C) 2017 Klarälvdalens Datakonsult AB, a KDAB Group company.
** Author: Giuseppe D'Angelo
** Contact: info@kdab.com
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/

#ifndef MYFRAMEBUFFEROBJECT_H
#define MYFRAMEBUFFEROBJECT_H

#include <QQuickFramebufferObject>

class MyFrameBufferObject : public QQuickFramebufferObject
{
    Q_OBJECT

    Q_PROPERTY(float azimuth READ azimuth WRITE setAzimuth NOTIFY azimuthChanged)
    Q_PROPERTY(float elevation READ elevation WRITE setElevation NOTIFY elevationChanged)
    Q_PROPERTY(float distance READ distance WRITE setDistance NOTIFY distanceChanged)

public:
    explicit MyFrameBufferObject(QQuickItem *parent = 0);
    Renderer *createRenderer() const Q_DECL_OVERRIDE;

    float azimuth() const;
    float distance() const;
    float elevation() const;

signals:
    void azimuthChanged(float azimuth);
    void distanceChanged(float distance);
    void elevationChanged(float elevation);

public slots:
    void setAzimuth(float azimuth);
    void setDistance(float distance);
    void setElevation(float elevation);

private:
    float m_azimuth;
    float m_elevation;
    float m_distance;
};

#endif // MYFRAMEBUFFEROBJECT_H
