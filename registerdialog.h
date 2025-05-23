#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QJsonObject>
#include <QMap>
#include <QSet>
#include <QTimer>
#include "global.h"
#include <functional>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

private slots:
    void on_get_code_clicked();
    void on_sure_btn_clicked();
    void on_return_btn_clicked();
    void on_cancel_btn_clicked();

public slots:
    void slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err);

private:
    bool checkUserValid();
    bool checkEmailValid();
    bool checkPassValid();
    bool checkVerifyValid();
    bool checkConfirmValid();
    void initHttpHandlers();
    void AddTipErr(TipErr te, QString tips);
    void DelTipErr(TipErr te);
    void ChangeTipPage();
    void showTip(QString str, bool b_ok);

    Ui::RegisterDialog *ui;
    QMap<ReqId, std::function<void(const QJsonObject &)>> _handlers;
    QMap<TipErr, QString> _tip_errs;
    QTimer *_countdown_timer;
    int _countdown;

signals:
    void sigSwitchLogin();
};

#endif // REGISTERDIALOG_H
