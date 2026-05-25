#ifndef HTTPMGR_H
#define HTTPMGR_H
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QObject>
#include <QString>
#include <QUrl>

#include "singleton.h"

// CRTP
class HttpMgr : public QObject, public Singleton<HttpMgr>, public std::enable_shared_from_this<HttpMgr> {
    Q_OBJECT
public:
    // 析构需要是公有的，因为我们使用单例的时候，析构会销毁_instance这个成员（shared_ptr类型）
    // shared_ptr内部会自动调用~HttpMgr，需要有权限访问
    ~HttpMgr();

private:
    // 声明友元，保证单例中(GetInstance)可以调用私有的构造
    friend class Singleton<HttpMgr>;
    HttpMgr();
    QNetworkAccessManager _manager;
    void PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod);
private slots:
    void slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);
signals:
    void sig_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);
    void sig_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
};

#endif // HTTPMGR_H
