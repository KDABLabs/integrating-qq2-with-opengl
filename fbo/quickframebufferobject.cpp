/****************************************************************************
**
** Copyright (C) 2015 Klarälvdalens Datakonsult AB, a KDAB Group company.
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

#include "quickframebufferobject.h"

#include <meshrenderer.h>

#include <QQuickWindow>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFramebufferObjectFormat>

class FrameBufferObjectRenderer : public QQuickFramebufferObject::Renderer
{
public:
    FrameBufferObjectRenderer()
    {
#if QT_VERSION < QT_VERSION_CHECK(5, 6, 0)
        // Unfortunately QQuickFramebufferObject mirrors the Y coordinate in 5.5,
        // 5.6 has APIs for this
        m_render.initialize(MeshRenderer::MirrorYCoordinate);
#else
        m_render.initialize();
#endif
    }

    void synchronize(QQuickFramebufferObject *item) Q_DECL_OVERRIDE
    {
        m_window = item->window();

        QuickFrameBufferObject *i = static_cast<QuickFrameBufferObject *>(item);
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

QuickFrameBufferObject::QuickFrameBufferObject(QQuickItem *parent)
    : QQuickFramebufferObject(parent)
    , m_azimuth(0.0)
    , m_elevation(15.0)
    , m_distance(5.0)
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 6, 0)
    setMirrorVertically(true);
#endif
}

QQuickFramebufferObject::Renderer *QuickFrameBufferObject::createRenderer() const
{
    return new FrameBufferObjectRenderer;
}




float QuickFrameBufferObject::azimuth() const
{
    return m_azimuth;
}

float QuickFrameBufferObject::distance() const
{
    return m_distance;
}

float QuickFrameBufferObject::elevation() const
{
    return m_elevation;
}

void QuickFrameBufferObject::setAzimuth(float azimuth)
{
    if (m_azimuth == azimuth)
        return;

    m_azimuth = azimuth;
    emit azimuthChanged(azimuth);
    update();
}

void QuickFrameBufferObject::setDistance(float distance)
{
    if (m_distance == distance)
        return;

    m_distance = distance;
    emit distanceChanged(distance);
    update();
}

void QuickFrameBufferObject::setElevation(float elevation)
{
    if (m_elevation == elevation)
        return;

    m_elevation = elevation;
    emit elevationChanged(elevation);
    update();
}


