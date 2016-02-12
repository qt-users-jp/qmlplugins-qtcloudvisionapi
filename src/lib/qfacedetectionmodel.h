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

#ifndef QFACEDETECTIONMODEL_H
#define QFACEDETECTIONMODEL_H

#include "qabstractcloudvisionapi.h"

class QCLOUDVISIONAPI_EXPORT QFaceDetectionModel : public QAbstractCloudVisionAPI
{
    Q_OBJECT
public:
    QFaceDetectionModel(QObject *parent = nullptr);
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE {
        return {
            { Qt::DisplayRole, "likelihood" },
            { Qt::ToolTipRole, "detectionConfidence" },
            { Qt::UserRole + 1, "angerLikelihood" },
            { Qt::UserRole + 2, "blurredLikelihood" },
            { Qt::UserRole + 3, "boundingPoly" },
            { Qt::UserRole + 4, "fdBoundingPoly" },
            { Qt::UserRole + 5, "headwearLikelihood" },
            { Qt::UserRole + 6, "joyLikelihood" },
            { Qt::UserRole + 7, "landmarkingConfidence" },
            { Qt::UserRole + 8, "landmarks" },
            { Qt::UserRole + 9, "panAngle" },
            { Qt::UserRole + 10, "rollAngle" },
            { Qt::UserRole + 11, "sorrowLikelihood" },
            { Qt::UserRole + 12, "surpriseLikelihood" },
            { Qt::UserRole + 13, "tiltAngle" },
            { Qt::UserRole + 14, "underExposedLikelihood" },
        };
    }

protected:
    QLatin1String type() const Q_DECL_OVERRIDE { return QLatin1String("FACE_DETECTION"); }
    QLatin1String annotationName() const Q_DECL_OVERRIDE { return QLatin1String("faceAnnotations"); }
    QVariantHash parse(const QJsonObject &annotation) const Q_DECL_OVERRIDE;

    Q_DISABLE_COPY(QFaceDetectionModel)
};

#endif // QFACEDETECTIONMODEL_H
