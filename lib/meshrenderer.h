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

#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include <QObject>

#include <QScopedPointer>

class QOpenGLBuffer;
class QOpenGLShaderProgram;
class QOpenGLVertexArrayObject;

class MeshRenderer : public QObject
{
    Q_OBJECT
public:
    explicit MeshRenderer(QObject *parent = 0);
    ~MeshRenderer();

    enum CoordinateMirroring {
        DoNotMirrorCoordinates,
        MirrorYCoordinate
    };

    // All assume that the GL context is current.
    void initialize(CoordinateMirroring cm = DoNotMirrorCoordinates);
    void render();
    void invalidate();

    void setAzimuth(float azimuth);
    void setElevation(float elevation);
    void setDistance(float distance);

private:
    QScopedPointer<QOpenGLBuffer> m_positionsBuffer;
    QScopedPointer<QOpenGLBuffer> m_normalsBuffer;
    QScopedPointer<QOpenGLBuffer> m_indicesBuffer;
    QScopedPointer<QOpenGLShaderProgram> m_shaderProgram;
    QScopedPointer<QOpenGLVertexArrayObject> m_vao;

    int m_indicesCount;

    CoordinateMirroring m_coordinateMirroring;

    float m_azimuth;
    float m_elevation;
    float m_distance;
};

#endif // MESHRENDERER_H


