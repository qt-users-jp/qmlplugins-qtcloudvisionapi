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

#ifndef QTEXTDETECTIONMODEL_H
#define QTEXTDETECTIONMODEL_H

#include "qabstractcloudvisionapi.h"

class QCLOUDVISIONAPI_EXPORT QTextDetectionModel : public QAbstractCloudVisionAPI
{
    Q_OBJECT
public:
    QTextDetectionModel(QObject *parent = nullptr);
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE {
        return {
            { Qt::DisplayRole, "description" },
            { Qt::ToolTipRole, "score" },
            { Qt::UserRole + 1, "boundingPoly" },
        };
    }

protected:
    QLatin1String type() const Q_DECL_OVERRIDE { return QLatin1String("TEXT_DETECTION"); }
    QLatin1String annotationName() const Q_DECL_OVERRIDE { return QLatin1String("textAnnotations"); }

    Q_DISABLE_COPY(QTextDetectionModel)
};

#endif // QTEXTDETECTIONMODEL_H
