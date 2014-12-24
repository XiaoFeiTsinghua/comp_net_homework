#include "logindialog.h"

LoginDialog::LoginDialog(QDialog *parent) :
    QDialog(parent)
{
    logoLabel = new QLabel(this);
    photoLabel = new QLabel(this);
    autologCheck = new QCheckBox(this);
    rememberCheck = new QCheckBox(this);
    userCombo = new QComboBox(this);
    keyEdit = new QLineEdit(this);
    loginButton = new QPushButton(this);
    exitButton = new QPushButton(this);
    minButton = new QPushButton(this);

    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::on_loginButton_clicked);
    connect(exitButton, &QPushButton::clicked, this, &LoginDialog::close);
    connect(minButton, &QPushButton::clicked, this, &LoginDialog::showMinimized);

    this->setMouseTracking(true);
    logoLabel->setMouseTracking(true);
    exitButton->setMouseTracking(true);
    beautify();
    //判断数据库是否存在
    QDir *temp = new QDir;
    bool exist = temp->exists("history.db");

    if(exist)
        qDebug() << "exist";
    else
        newHistroy();

    //初始化输入框内容
    init_userCombo();
    init_keyEdit();
    //建立TCPSocket对象
    log = new QTcpSocket(this);
    con();
    ismousepressed = false;
}

QString LoginDialog::getUsername()
{
    return username;
}


//美化界面
void LoginDialog::beautify()
{
    //圆角
    setWindowFlags(Qt::FramelessWindowHint);
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(), 3, 3);
    setMask(bmp);//设置窗体遮罩

    //装饰，无边框
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->resize(400,300);

    logoLabel->resize(400,190);
    logoLabel->move(0, -18);
    logoLabel->setPixmap(QPixmap(":/image/logo"));

    photoLabel->resize(50,50);
    photoLabel->move(30,200);
    photoLabel->setPixmap(QPixmap(":/image/photo"));

    userCombo->resize(200, 30);
    userCombo->move(100, 180);
    userCombo->setEditable(true);

    keyEdit->resize(200, 30);
    keyEdit->move(100, 210);
    keyEdit->setEchoMode(QLineEdit::Password);

    autologCheck->resize(100,20);
    autologCheck->move(100,245);
    autologCheck->setText("自动登录");

    rememberCheck->resize(100,20);
    rememberCheck->move(200,245);
    rememberCheck->setText("记住密码");

    loginButton->resize(200, 30);
    loginButton->move(100, 270);
    loginButton->setText("登录");

    exitButton->resize(20, 20);
    exitButton->move(380, 0);
    exitButton->setIcon(QIcon(":/image/close"));
    exitButton->setStyleSheet("border:none; background-color:transparent;");

    minButton->resize(20, 20);
    minButton->move(360, 0);
    minButton->setIcon(QIcon(":/image/min"));
    minButton->setStyleSheet("border:none; background-color:transparent;");
}

void LoginDialog::on_loginButton_clicked()
{
    QString id = userCombo->currentText();
    //qDebug()<<"id"<<id<<endl;
    QString pw = keyEdit->text();
    QString st = id + '_' + pw;
    QByteArray bt;
    bt.append(st);

    if (log == NULL)
    {
        con();
        //qDebug()<<"NULL"<<endl;
    }
    log->write(bt);
    if (!log->waitForReadyRead(300))
    {

    }
    bt = log->readAll();
    if (bt == "lol")
    {
        //QMessageBox::information(this, tr("登录信息"),tr("成功！"));
        qDebug() << "lol";
        accept();
    }
    else
    {
        QMessageBox::information(this, tr("登录信息"),tr("失败！"));
        qDebug() << "false";
    }
    username = userCombo->currentText();
    int flag = rememberCheck->isChecked();
    //qDebug()<<"check"<<flag;
    setRemember(flag);
    addUser(username);
}

void LoginDialog::init_userCombo()
{

}

void LoginDialog::init_keyEdit()
{
    int flag = getRemember();
    if(flag == 1)//上次勾选了"记住密码"
    {
        rememberCheck->setChecked(true);
        keyEdit->setText("net2014");
    }
    else
    {
        rememberCheck->setChecked(false);
    }
}

void LoginDialog::con()
{
    if (log != NULL)
    {
        delete log;
        log = NULL;
    }
    log = new QTcpSocket(this);
    log->connectToHost("166.111.180.60", 8000);
}

void LoginDialog::mouseMoveEvent(QMouseEvent *e)
{
    if(inButton(exitButton, e->pos()))
        exitButton->setStyleSheet("border:none; background-color: rgb(255, 0, 0);");
    else
        exitButton->setStyleSheet("border:none; background-color:transparent;");

    if(inButton(minButton, e->pos()))
        minButton->setStyleSheet("border:none; background-color: rgba(255, 0, 0, 100);");
    else
        minButton->setStyleSheet("border:none; background-color:transparent;");


    if (e->buttons() == Qt::LeftButton)
           move(e->globalPos() - dPos);
}

void LoginDialog::mousePressEvent(QMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::LeftButton)
           dPos = mouseEvent->pos();
}


bool LoginDialog::inButton(QPushButton *push, QPoint p)
{
    int height = push->height();
    int width = push->width();
    QPoint left_up = push->pos();
    QPoint right_down;
    right_down.setX(push->pos().x() + width);
    right_down.setY(push->pos().y() + height);
    if((p.x() >= left_up.x()) && (p.x() <= right_down.x()) && (p.y() >= left_up.y()) && (p.y() <= right_down.y()))
        return true;
    else
        return false;
}


