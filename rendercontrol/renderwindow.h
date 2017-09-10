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

#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <QWindow>

class MeshRenderer;
class Camera;
class QOpenGLContext;
class QQuickWindow;
class QQuickRenderControl;
class QQmlComponent;
class QQuickItem;

class RenderWindow : public QWindow
{
public:
    RenderWindow(QWindow *parent = 0);
    ~RenderWindow();

protected:
    void resizeEvent(QResizeEvent *e) Q_DECL_OVERRIDE;

    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;

private:
    void syncScene();
    void draw();

    void onQmlComponentLoadingComplete();
    void updateRootItemSize();

    QOpenGLContext *m_context;

    MeshRenderer *m_renderer;
    Camera *m_camera;

    QQuickRenderControl *m_renderControl;
    QQuickWindow *m_quickWindow;
    QQmlComponent *m_qmlComponent;
    QQuickItem *m_rootItem;
};

#endif // RENDERWINDOW_H

