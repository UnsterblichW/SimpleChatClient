#include "global.h"

std::function<void(QWidget*)> repolish =[](QWidget *w){
    w->style()->unpolish(w);
    w->style()->polish(w);
};

std::function<QString(QString)> encodePwd = [](QString input) {
    // 使用静态方法计算哈希值
    QByteArray hash = QCryptographicHash::hash(input.toUtf8(), QCryptographicHash::Md5);
    QString strMD5 = hash.toHex(); // 将哈希值转换为十六进制字符串

    // 输出哈希值
    qDebug() << "密码md5转换 原文:" << input << " , 密文:" << strMD5;

    return strMD5;
};

QString gate_url_prefix = "";
