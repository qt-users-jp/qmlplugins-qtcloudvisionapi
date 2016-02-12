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

#ifndef QABSTRACTCLOUDVISIONAPI_H
#define QABSTRACTCLOUDVISIONAPI_H

#include "qcloudvisionapi_global.h"

#include <QtCore/QAbstractListModel>
#include <QtCore/QJsonObject>
#include <QtGui/QImage>

class QCLOUDVISIONAPI_EXPORT QAbstractCloudVisionAPI : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString key READ key WRITE setKey NOTIFY keyChanged)
    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)
    Q_PROPERTY(int maxResults READ maxResults WRITE setMaxResults NOTIFY maxResultsChanged)
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(QJsonObject error READ error NOTIFY errorChanged)
    Q_ENUMS(Status)
public:
    enum Status {
        Null,
        Ready,
        Loading,
        Error,
    };

    explicit QAbstractCloudVisionAPI(QObject *parent = nullptr);
    ~QAbstractCloudVisionAPI() Q_DECL_OVERRIDE;

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    QString key() const;
    QImage image() const;
    int maxResults() const;
    Status status() const;
    QJsonObject error() const;

public Q_SLOTS:
    void setKey(const QString &key);
    void setImage(const QImage &image);
    void setMaxResults(int maxResults);

private:
    void setStatus(Status status);
    void setError(const QJsonObject &error);

public Q_SLOTS:
    virtual void detect();

private:
    void clear();

Q_SIGNALS:
    void keyChanged(const QString& key);
    void imageChanged(const QImage &image);
    void maxResultsChanged(int maxResults);
    void statusChanged(Status status);
    void errorChanged(const QJsonObject &error);

protected:
    virtual QLatin1String type() const = 0;
    virtual QLatin1String annotationName() const = 0;
    virtual QVariantHash parse(const QJsonObject &annotation) const;

private:
    class Private;
    Private *d;
    Q_DISABLE_COPY(QAbstractCloudVisionAPI)
};

#endif // QABSTRACTCLOUDVISIONAPI_H
