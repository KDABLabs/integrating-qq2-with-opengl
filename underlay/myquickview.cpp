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

#include "myquickview.h"

#include <camera.h>
#include <meshrenderer.h>

#include <QSurfaceFormat>
#include <QQmlContext>

MyQuickView::MyQuickView(QWindow *parent)
    : QQuickView(parent)
    , m_camera(new Camera(this))
    , m_renderer(new MeshRenderer(this))
{
    QSurfaceFormat format;
    format.setMajorVersion(3);
    format.setMinorVersion(3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setSamples(4);
    setFormat(format);

    connect(this, &QQuickWindow::sceneGraphInitialized,
            this, &MyQuickView::initializeUnderlay,
            Qt::DirectConnection);

    connect(this, &QQuickWindow::beforeSynchronizing,
            this, &MyQuickView::synchronizeUnderlay,
            Qt::DirectConnection);

    connect(this, &QQuickWindow::beforeRendering,
            this, &MyQuickView::renderUnderlay,
            Qt::DirectConnection);

    connect(this, &QQuickWindow::sceneGraphInvalidated,
            this, &MyQuickView::invalidateUnderlay,
            Qt::DirectConnection);

    connect(m_camera, &Camera::azimuthChanged,
            this, &QQuickWindow::update);

    connect(m_camera, &Camera::elevationChanged,
            this, &QQuickWindow::update);

    connect(m_camera, &Camera::distanceChanged,
            this, &QQuickWindow::update);

    setClearBeforeRendering(false);
    setPersistentOpenGLContext(true);

    setResizeMode(SizeRootObjectToView);
    rootContext()->setContextProperty("_camera", m_camera);
    setSource(QUrl("qrc:///qml/main.qml"));
}

void MyQuickView::initializeUnderlay()
{
    m_renderer->initialize();
    resetOpenGLState();
}

void MyQuickView::synchronizeUnderlay()
{
    m_renderer->setAzimuth(m_camera->azimuth());
    m_renderer->setElevation(m_camera->elevation());
    m_renderer->setDistance(m_camera->distance());
}

void MyQuickView::renderUnderlay()
{
    m_renderer->render();
    resetOpenGLState();
}

void MyQuickView::invalidateUnderlay()
{
    m_renderer->invalidate();
    resetOpenGLState();
}
