/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef TRACKERCLIENT_H
#define TRACKERCLIENT_H

#include <QByteArray>
#include <QList>
#include <QObject>
#include <QHostAddress>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QAuthenticator>
#include <QUdpSocket>
#include <QTimer>

#include "metainfo.h"
#include "torrentclient.h"

class TorrentClient;

class TrackerClient : public QObject
{
    Q_OBJECT

public:
    explicit TrackerClient(TorrentClient *downloader, QObject *parent = 0);
    virtual ~TrackerClient();

    void start(const MetaInfo &info);
    void stop();
    void startSeeding();

signals:
    void failure(const QString &reason);
    void warning(const QString &message);
    void peerListUpdated(const QList<TorrentPeer> &peerList);

    void uploadCountUpdated(qint64 newUploadCount);
    void downloadCountUpdated(qint64 newDownloadCount);

    void stopped();

protected:
    void timerEvent(QTimerEvent *event) override;

private slots:
    void fetchPeerList();
    void fetchTimeoutHandler();

private slots:

//// Requests :
    void connectRequest();
    void announceRequest();
    void scrapeRequest();

    void sendLastActionRequest();

//// Handlers :
    void responseHandler();
    void connectResponseHandler();
    void announceResponseHandler();
    void scrapeResponseHandler();

private:
    TorrentClient      *m_torrentDownloader;

    int                 m_requestIntervalSec;
    int                 m_requestIntervalTimer;
    QUdpSocket          m_udpSocket;
    MetaInfo            m_metaInfo;
    QStringList::ConstIterator m_currentAnnounceIt;
    QList<TorrentPeer>  m_peerList;
    qint64              m_uploadedBytes;
    qint64              m_downloadedBytes;
    qint64              m_length;

    enum ActionTypes{
        ActionConnectToHost   = -1,
        ActionConnect   = 0,
        ActionAnnounce  = 1,
        ActionScrape    = 2,
        ActionError     = 3
    };
    ActionTypes         m_lastAction;
    qint32              m_transactionId;
    qint64              m_connectionId;
    QByteArray          m_response;

    uint                m_maxTryNum;
    uint                m_requestTryNum;
    bool                m_isLastRequestSuccessful;
    int                 m_fetchTimeout;
    QTimer              m_fetchTimer;

    bool                m_firstTrackerRequest;
    bool                m_lastTrackerRequest;
    bool                m_firstSeeding;
};

#endif
