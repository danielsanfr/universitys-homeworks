#ifndef MAINTESTTHREAD_HPP
#define MAINTESTTHREAD_HPP

#include <QHash>
#include <QThread>
#include <QtGlobal>
#include <QStringList>
#include <QTextStream>

#include "peer.hpp"
#include "peermodel.hpp"

class MainTestThread : public QThread
{
    Q_OBJECT
public:
    explicit MainTestThread(QObject *parent = 0);
signals:
    void sendMessage(int, const QString &, const QString &);
protected:
    void run();
private slots:
    void onNewPeerFound(PeerModel *);
    void onPeerDead(QString);
private:
    qint64 m_peerCountId;
    Peer *m_peer;
    QString m_buffer;
    QStringList m_commandParts;
    QTextStream *m_textInStream;
    QHash <qint64, PeerModel *> m_peerList;
    //QTextStream m_textOutStream(stdout);
    void createHelp();
};

#endif // MAINTESTTHREAD_HPP
