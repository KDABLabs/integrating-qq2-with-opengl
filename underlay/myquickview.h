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

#ifndef MYQUICKVIEW_H
#define MYQUICKVIEW_H

#include <QQuickView>

class MeshRenderer;
class Camera;

class MyQuickView : public QQuickView
{
    Q_OBJECT
public:
    explicit MyQuickView(QWindow *parent = 0);

private:
    void initializeUnderlay();
    void synchronizeUnderlay();
    void renderUnderlay();
    void invalidateUnderlay();

    Camera *m_camera;
    MeshRenderer *m_renderer;
};

#endif // MYQUICKVIEW_H
