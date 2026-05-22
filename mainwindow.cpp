#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _login_dlg = new LoginDialog(this);
    _reg_dlg = new RegisterDialog(this);

    // 解决多个弹窗的问题，清除标志位，让dialog降级为普通组件，可以正常嵌入MainWindow
    _login_dlg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    _reg_dlg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

    setCentralWidget(_login_dlg);

    // 创建和注册消息链接
    connect(_login_dlg, &LoginDialog::switchRegister, this, &MainWindow::SlotSwitchReg);

}

MainWindow::~MainWindow()
{
    delete ui;
    // if (_login_dlg) {
    //     delete _login_dlg;
    //     _login_dlg = nullptr;
    // }
    // if (_reg_dlg) {
    //     delete _reg_dlg;
    //     _reg_dlg = nullptr;
    // }

}

void MainWindow::SlotSwitchReg()
{
    // 取下登录界面，再隐藏，防止直接替换导致旧组件被delete
    QWidget *oldWidget = takeCentralWidget();
    if (oldWidget == _login_dlg) {
        _login_dlg->hide();
    }
    setCentralWidget(_reg_dlg);
    _reg_dlg->show();
}
