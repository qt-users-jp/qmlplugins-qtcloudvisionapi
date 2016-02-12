/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   QtCloudVisionAPI                                                        *
 *   Copyright (C) 2016 by Tasuku Suzuki <stasuku@gmail.com>                 *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Lesser Public License as          *
 *   published by the Free Software Foundation; either version 2 of the      *
 *   License, or (at your option) any later version.                         *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU Lesser General Public License for more details.                     *
 *                                                                           *
 *   You should have received a copy of the GNU Lesser General Public        *
 *   License along with this program; if not, write to the                   *
 *   Free Software Foundation, Inc.,                                         *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.               *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <QtQml/QQmlExtensionPlugin>
#include <QtQml/qqml.h>

#include <QtCloudVisionAPI/QFaceDetectionModel>
#include <QtCloudVisionAPI/QLandmarkDetectionModel>
#include <QtCloudVisionAPI/QLogoDetectionModel>
#include <QtCloudVisionAPI/QLabelDetectionModel>
#include <QtCloudVisionAPI/QTextDetectionModel>
#include <QtCloudVisionAPI/QSafeSearchDetectionModel>
#include <QtCloudVisionAPI/QSuggestionDetectionModel>

class CloudVisionAPIDeclarativeModule : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri)
    {
        Q_ASSERT(uri == QStringLiteral("jp.qtusers.tasuku.cloudvisionapi"));
        // @uri jp.qtusers.tasuku.cloudvisionapi
        qmlRegisterType<QFaceDetectionModel>(uri, 0, 1, "FaceDetectionModel");
        qmlRegisterType<QLandmarkDetectionModel>(uri, 0, 1, "LandmarkDetectionModel");
        qmlRegisterType<QLogoDetectionModel>(uri, 0, 1, "LogoDetectionModel");
        qmlRegisterType<QLabelDetectionModel>(uri, 0, 1, "LabelDetectionModel");
        qmlRegisterType<QTextDetectionModel>(uri, 0, 1, "TextDetectionModel");
        qmlRegisterType<QSafeSearchDetectionModel>(uri, 0, 1, "SafeSearchDetectionModel");
        qmlRegisterType<QSuggestionDetectionModel>(uri, 0, 1, "SuggestionDetectionModel");
    }
};

#include "main.moc"
