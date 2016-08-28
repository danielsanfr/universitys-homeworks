#include "maintestthread.hpp"

#include <iostream>

#include <QList>
#include <QDebug>
#include <QCommandLineParser>

#include "message.hpp"

using namespace std;

MainTestThread::MainTestThread(QObject *parent) :
    QThread(parent), m_peerCountId(0), m_peer(new Peer()), m_textInStream(new QTextStream(stdin))
{
    bool isOk = connect(m_peer, SIGNAL(newPeerFound(PeerModel*)),
                        this, SLOT(onNewPeerFound(PeerModel*)));
    Q_ASSERT(isOk);
    isOk = connect(m_peer, SIGNAL(peerDead(QString)),
                   this, SLOT(onPeerDead(QString)));
    Q_ASSERT(isOk);
    isOk = connect(this, SIGNAL(sendMessage(int,QString,QString)),
                   m_peer, SLOT(sendMessage(int,QString,QString)));
    Q_ASSERT(isOk);
    start();
//    exec();
    cout << "For more informations use the help command." << endl;
    cout << "A command example: send -t \"Text or file path to send\" 0" << endl << endl;
}

void MainTestThread::run()
{
    QCommandLineParser commandLineParser;
    commandLineParser.setApplicationDescription("Push Anything help");
    commandLineParser.addPositionalArgument("peer", "Peer to send anything.");
    // An option with a value
    QCommandLineOption textToSend(QStringList() << "t" << "text", "text to send", "text");
    commandLineParser.addOption(textToSend);
    QCommandLineOption fileToSend(QStringList() << "f" << "file-path", "file to send", "file");
    commandLineParser.addOption(fileToSend);
    while (true) {
        cout << "> ";
        m_buffer = m_textInStream->readLine();
        m_commandParts = m_buffer.trimmed().split(" ");
        if (m_commandParts.size() == 1) {
            if (m_commandParts[0] == "list") {
                QList<qint64> keys = m_peerList.keys();
                foreach (qint64 key, keys) {
                    cout << "Peer id: " << key << endl;
                    cout << m_peerList.value(key)->toString().toStdString() << endl;
                }
            } else if ((m_commandParts[0] == "help" || m_commandParts[0] == "man") && m_commandParts.size() == 1)
//                cout << commandLineParser.helpText().toStdString() << endl;
                createHelp();
            else if ((m_commandParts[0] == "quit" || m_commandParts[0] == "exit") && m_commandParts.size() == 1) {
                m_peer->deleteLater();
                m_peer = 0;
                cout << "Bye bye..." << endl;
                QCoreApplication::quit();
            } else {
                cout << "Unknown command." << endl;
                continue;
            }
        } else if (m_commandParts[0] == "send") {
            if (m_commandParts.size() == 4) {
                commandLineParser.parse(m_commandParts);
                QString source;
                Message::Type type = Message::UNKNOWN;
                if (commandLineParser.isSet(textToSend)) {
                    type = Message::TEXT;
                    source = commandLineParser.value(textToSend);
                } else if(commandLineParser.isSet(fileToSend)) {
                    type = Message::FILE;
                    source = commandLineParser.value(fileToSend);
                } else {
                    cout << "Missing some arguments." << endl;
                    continue;
                }
                bool isOk = false;
                qint64 peerId = commandLineParser.positionalArguments()[0].toInt(&isOk);
                if (!isOk) {
                    cout << "Not a valid integer." << endl;
                    continue;
                }
                PeerModel *peer = m_peerList.value(peerId, 0);
                if (peer != 0)
                    emit sendMessage((int) type, source, peer->id());
                else {
                    cout << "Not a valid integer for a peer. Try using the list command before, to know what the valid ids." << endl;
                }
            } else {
                cout << "Missing some arguments." << endl;
                continue;
            }
        } else
            cout << "Unknown command." << endl;
    }
}

void MainTestThread::onNewPeerFound(PeerModel *peer)
{
    m_peerList.insert(m_peerCountId, peer);
    ++m_peerCountId;
}

void MainTestThread::onPeerDead(QString id)
{
    QList<qint64> keys = m_peerList.keys();
    foreach (qint64 key, keys) {
        if (m_peerList.value(key)->id() == id) {
            m_peerList.remove(key);
            return;
        }
    }
}

void MainTestThread::createHelp()
{
    cout << "                         Avaliable commands" << endl << endl;
    cout << "Name:" << endl;
    cout << "        list - List found peers." << endl;
    cout << "Synopsis:" << endl;
    cout << "        list [option]" << endl;
    cout << "Description:" << endl;
    cout << "        Not have avaliable options yet." << endl << endl;
    cout << "Name:" << endl;
    cout << "        send - Sen anything for any peer fount." << endl;
    cout << "Synopsis:" << endl;
    cout << "        send [option] [content] [peer]" << endl;
    cout << "Description:" << endl;
    cout << "        The avaliable options:" << endl;
    cout << "        -f, --file-path" << endl;
    cout << "                set send mode to file, the content is a file path" << endl;
    cout << "        -t, --text" << endl;
    cout << "                set send mode to text, the content is a simple text" << endl << endl;
    cout << "=============================================================================" << endl << endl;
}
