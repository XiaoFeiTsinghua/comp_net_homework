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

    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::on_loginButton_clicked);
    connect(exitButton, &QPushButton::clicked, this, &LoginDialog::on_exitButton_clicked);

    this->setMouseTracking(true);
    logoLabel->setMouseTracking(true);
    exitButton->setMouseTracking(true);
    beautify();
    //初始化输入框内容
    init_userCombo("localinfo.db");
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
    //装饰，无边框
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->resize(400,300);
    logoLabel->resize(400,190);
    logoLabel->move(0, -10);
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
    exitButton->setFlat(true);


    exitButton->setStyleSheet("QPushButton{background:red}");
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

}

void LoginDialog::init_userCombo(QString filename)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(filename);
    if(!db.open())
    {
        qDebug()<<"fail to open database";
    }
    QSqlQuery query;//以下执行相关QSL语句
    query.exec("create table localuser(id varchar, username varchar)");    //新建student表，id设置为主键，还有一个name项
    //query.exec(QObject::tr("insert into localuser values(1,'2012010526')"));

    query.exec("select id, username from localuser where id >= 1");
    while(query.next())//query.next()指向查找到的第一条记录，然后每次后移一条记录
    {
        int ele0=query.value(0).toInt();//query.value(0)是id的值，将其转换为int型
        QString ele1=query.value(1).toString();
        userCombo->addItem(ele1);
        qDebug()<<ele0<<ele1;//输出两个值
    }
    query.exec(QObject::tr("drop student"));
    /*
    QFile user_file(filename);
    if(!user_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Open failed." << endl;
    }
    else
    {
        QTextStream txtInput(&user_file);
        QString lineStr;
        while(!txtInput.atEnd())
        {
            lineStr = txtInput.readLine();
            userCombo->addItem(lineStr);
            qDebug() << lineStr << endl;
        }

        user_file.close();
    }
    */
}

void LoginDialog::on_exitButton_clicked()
{
    exit(0);
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
        exitButton->setFlat(false);
    else
    {
        //qDebug()<<"1";
        exitButton->setFlat(true);
    }
    if (ismousepressed)
        this->move(e->globalPos() - dPos);
}

void LoginDialog::mousePressEvent(QMouseEvent *e)
{
    QPoint windowPos = this->pos();
    QPoint mousePos = e->globalPos();
    dPos = mousePos - windowPos;
    ismousepressed = true;
}

void LoginDialog::mouseReleaseEvent(QMouseEvent *e)
{
    ismousepressed = false;
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

