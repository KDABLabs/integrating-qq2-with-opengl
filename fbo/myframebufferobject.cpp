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

#include "myframebufferobject.h"

#include <meshrenderer.h>

#include <QQuickWindow>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFramebufferObjectFormat>

class MyFrameBufferObjectRenderer : public QQuickFramebufferObject::Renderer
{
public:
    MyFrameBufferObjectRenderer()
    {

        m_render.initialize();
    }

    void synchronize(QQuickFramebufferObject *item) Q_DECL_OVERRIDE
    {
        m_window = item->window();

        MyFrameBufferObject *i = static_cast<MyFrameBufferObject *>(item);
        m_render.setAzimuth(i->azimuth());
        m_render.setElevation(i->elevation());
        m_render.setDistance(i->distance());
    }

    void render() Q_DECL_OVERRIDE
    {
        m_render.render();
        m_window->resetOpenGLState();
    }

    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) Q_DECL_OVERRIDE
    {
        QOpenGLFramebufferObjectFormat format;
        format.setSamples(4);
        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        return new QOpenGLFramebufferObject(size, format);
    }

private:
    MeshRenderer m_render;
    QQuickWindow *m_window;
};



// MyFrameBufferObject implementation

MyFrameBufferObject::MyFrameBufferObject(QQuickItem *parent)
    : QQuickFramebufferObject(parent)
    , m_azimuth(0.0)
    , m_elevation(15.0)
    , m_distance(5.0)
{
    setMirrorVertically(true);
}

QQuickFramebufferObject::Renderer *MyFrameBufferObject::createRenderer() const
{
    return new MyFrameBufferObjectRenderer;
}

float MyFrameBufferObject::azimuth() const
{
    return m_azimuth;
}

float MyFrameBufferObject::distance() const
{
    return m_distance;
}

float MyFrameBufferObject::elevation() const
{
    return m_elevation;
}

void MyFrameBufferObject::setAzimuth(float azimuth)
{
    if (m_azimuth == azimuth)
        return;

    m_azimuth = azimuth;
    emit azimuthChanged(azimuth);
    update();
}

void MyFrameBufferObject::setDistance(float distance)
{
    if (m_distance == distance)
        return;

    m_distance = distance;
    emit distanceChanged(distance);
    update();
}

void MyFrameBufferObject::setElevation(float elevation)
{
    if (m_elevation == elevation)
        return;

    m_elevation = elevation;
    emit elevationChanged(elevation);
    update();
}
