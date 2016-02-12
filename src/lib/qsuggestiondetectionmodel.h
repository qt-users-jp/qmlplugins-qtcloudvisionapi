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

#ifndef QSUGGESTIONDETECTIONMODEL_H
#define QSUGGESTIONDETECTIONMODEL_H

#include "qabstractcloudvisionapi.h"

class QCLOUDVISIONAPI_EXPORT QSuggestionDetectionModel : public QAbstractCloudVisionAPI
{
    Q_OBJECT
public:
    QSuggestionDetectionModel(QObject *parent = nullptr);
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE {
        return {
            { Qt::DisplayRole, "description" },
            { Qt::ToolTipRole, "score" },
        };
    }

protected:
    QLatin1String type() const Q_DECL_OVERRIDE { return QLatin1String("SUGGESTION_DETECTION"); }
    QLatin1String annotationName() const Q_DECL_OVERRIDE { return QLatin1String("suggestionAnnotations"); }

    Q_DISABLE_COPY(QSuggestionDetectionModel)
};

#endif // QSUGGESTIONDETECTIONMODEL_H
