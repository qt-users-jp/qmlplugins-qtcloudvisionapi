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

#include "qabstractcloudvisionapi.h"
#include "qcloudvisionapisettings.h"

#include <QtCore/QBuffer>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonArray>
#include <QtCore/QLoggingCategory>

#include <QtGui/QImageWriter>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

Q_LOGGING_CATEGORY(loggingCategory, "jp.qt-users.tasuku.cloudvisionapi.cpp.model")

class QAbstractCloudVisionAPI::Private
{
public:
    Private(QAbstractCloudVisionAPI *parent);

    void update();

private:
    QJsonDocument createRequest(const QByteArray &content) const;
    void parseReply(const QByteArray &content);

private:
    QAbstractCloudVisionAPI *q;

public:
    QList<QVariantHash> data;
    QString key;
    QImage image;
    int maxResults;
    Status status;
    QJsonObject error;
};

QAbstractCloudVisionAPI::Private::Private(QAbstractCloudVisionAPI *parent)
    : q(parent)
    , key(QString::fromUtf8(qgetenv("QT_CLOUD_VISION_API_KEY")))
    , maxResults(1)
    , status(Null)
{
}

void QAbstractCloudVisionAPI::Private:: update()
{
    q->setStatus(Loading);
    QBuffer buffer;
    QImageWriter jpg(&buffer, "jpg");
//    qCDebug(loggingCategory) << image;
    if (jpg.write(image)) {
        QNetworkRequest request(QUrl(QStringLiteral("https://vision.googleapis.com/v1alpha1/images:annotate?key=%1").arg(key)));
        request.setAttribute(QNetworkRequest::HttpPipeliningAllowedAttribute, true);
        request.setRawHeader("Content-Type", "application/json");
//        QSslConfiguration sslConfiguration;
//        sslConfiguration.setSslOption(QSsl::SslOptionDisableSessionPersistence, false);
//        request.setSslConfiguration(sslConfiguration);
        QNetworkReply *reply = QCloudVisionAPISettings::networkAccessManager()->post(request, createRequest(buffer.buffer().toBase64()).toJson());
        connect(reply, &QNetworkReply::finished, [this, reply]() {
            if (reply->error() == QNetworkReply::NoError) {
//                QSslConfiguration sslConfiguration = reply->sslConfiguration();
//                qDebug() << sslConfiguration.sessionTicketLifeTimeHint() << sslConfiguration.sessionTicket().toHex();
                q->clear();
                parseReply(reply->readAll());
                reply->deleteLater();
            } else {
                QJsonObject e;
                e.insert(QStringLiteral("category"), QStringLiteral("network"));
                e.insert(QStringLiteral("code"), reply->error());
                e.insert(QStringLiteral("message"), reply->errorString());
                q->setError(e);
            }
        });
    } else {
        QJsonObject e;
        e.insert(QStringLiteral("category"), QStringLiteral("image"));
        e.insert(QStringLiteral("code"), jpg.error());
        e.insert(QStringLiteral("message"), jpg.errorString());
        q->setError(e);
    }
}

QJsonDocument QAbstractCloudVisionAPI::Private::createRequest(const QByteArray &content) const
{
    QJsonObject object;
    QJsonObject image;
    image.insert(QStringLiteral("content"), QJsonValue(QLatin1String(content)));
    QJsonObject feature;
    feature.insert(QStringLiteral("type"), QJsonValue(q->type()));
    feature.insert(QStringLiteral("maxResults"), QJsonValue(maxResults));
    QJsonArray features;
    features.append(feature);
    QJsonObject request;
    request.insert(QStringLiteral("image"), image);
    request.insert(QStringLiteral("features"), features);
    QJsonArray requests;
    requests.append(request);
    object.insert(QStringLiteral("requests"), requests);

    return QJsonDocument(object);
}

void QAbstractCloudVisionAPI::Private::parseReply(const QByteArray &reply)
{
    QJsonDocument json = QJsonDocument::fromJson(reply);
//    qCDebug(loggingCategory) << QString::fromUtf8(json.toJson(QJsonDocument::Compact));

    QJsonObject object = json.object();
    if (object.contains(QStringLiteral("responses"))) {
        QJsonArray responses = object.value(QStringLiteral("responses")).toArray();
        QJsonObject response = responses.at(0).toObject();
    //    qCDebug(loggingCategory) << response.keys();
        QJsonArray annotations = response.value(q->annotationName()).toArray();
    //    qCDebug(loggingCategory) << annotations.size();
        if (!annotations.isEmpty()) {
            q->beginInsertRows(QModelIndex(), 0, annotations.size() - 1);
            foreach (const QJsonValue &value, annotations) {
                QVariantHash hash = q->parse(value.toObject());
    //            qCDebug(loggingCategory) << hash.keys();
                data.append(hash);
            }
            q->endInsertRows();
        }
        q->setStatus(Ready);
    } else if (object.contains(QStringLiteral("error"))) {
        QJsonObject e = object.value(QStringLiteral("error")).toObject();
        e.insert(QStringLiteral("category"), QStringLiteral("api"));
        q->setError(e);
    }
}

QAbstractCloudVisionAPI::QAbstractCloudVisionAPI(QObject *parent)
    : QAbstractListModel(parent)
    , d(new Private(this))
{
}

QAbstractCloudVisionAPI::~QAbstractCloudVisionAPI()
{
    delete d;
}

int QAbstractCloudVisionAPI::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return d->data.count();
}

QVariant QAbstractCloudVisionAPI::data(const QModelIndex &index, int role) const
{
    QVariant ret;
    int row = index.row();
//    qCDebug(loggingCategory) << row << role;
    if (0 <= row && row < d->data.count()) {
        if (roleNames().contains(role)) {
//            qCDebug(loggingCategory) << row << QString::fromLatin1(roleNames().value(role));
            ret = d->data.at(row).value(QString::fromLatin1(roleNames().value(role)));
        }
    }
//    qCDebug(loggingCategory) << row << role << ret;
    return ret;
}

QString QAbstractCloudVisionAPI::key() const
{
    return d->key;
}

void QAbstractCloudVisionAPI::setKey(const QString &key)
{
    if (d->key == key) return;
    d->key = key;
    emit keyChanged(key);
}

QImage QAbstractCloudVisionAPI::image() const
{
    return d->image;
}

void QAbstractCloudVisionAPI::setImage(const QImage &image)
{
    if (d->image == image) return;
    d->image = image;
    emit imageChanged(image);
}

int QAbstractCloudVisionAPI::maxResults() const
{
    return d->maxResults;
}

void QAbstractCloudVisionAPI::setMaxResults(int maxResults)
{
    if (d->maxResults == maxResults) return;
    d->maxResults = maxResults;
    emit maxResultsChanged(maxResults);
}

QAbstractCloudVisionAPI::Status QAbstractCloudVisionAPI::status() const
{
    return d->status;
}

void QAbstractCloudVisionAPI::setStatus(QAbstractCloudVisionAPI::Status status)
{
    if (d->status == status) return;
    d->status = status;
    emit statusChanged(status);
}

QJsonObject QAbstractCloudVisionAPI::error() const
{
    return d->error;
}

void QAbstractCloudVisionAPI::setError(const QJsonObject &error)
{
    if (d->error != error) {
        d->error = error;
        emit errorChanged(error);
    }
    setStatus(Error);
}

void QAbstractCloudVisionAPI::detect()
{
    d->update();
}

void QAbstractCloudVisionAPI::clear()
{
    if (!d->data.isEmpty()) {
        beginRemoveRows(QModelIndex(), 0, d->data.count() - 1);
        d->data.clear();
        endRemoveRows();
    }
}

QVariantHash QAbstractCloudVisionAPI::parse(const QJsonObject &annotation) const
{
    return annotation.toVariantHash();
}
