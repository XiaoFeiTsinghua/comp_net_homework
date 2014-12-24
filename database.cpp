#include "database.h"

void newHistroy()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("history.db");  //在工程目录新建一个mytest.db的文件
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }
    QSqlQuery query;//以下执行相关QSL语句
    query.exec("create table loghistory(id varchar, studentnum varchar)");
    query.exec("create table remember(id varchar, checked varvhar)");
    query.exec("insert into remember values(1, 0)");

}

int getRemember()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("history.db");  //在工程目录新建一个mytest.db的文件
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }
    QSqlQuery query;//以下执行相关QSL语句
    query.exec("select checked from remember where id == 1");
    query.next();
    int remember = query.value(0).toInt();
    qDebug()<<remember;
    return remember;
}

void setRemember(int flag)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("history.db");  //在工程目录新建一个mytest.db的文件
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }
    QSqlQuery query;//以下执行相关QSL语句
    query.exec("update remember set checked = " + QString::number(flag, 10) + " where id = 1");
}

void addUser(QString username)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("history.db");  //在工程目录新建一个mytest.db的文件
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }
    QSqlQuery query;//以下执行相关QSL语句
    query.exec("select id from loghistory where studentnum == " + username);
    int flag = query.next();
    if(flag == false)
    {
        query.exec("select id from loghistory where id >= 1");
        query.last();
        int temp = query.value(0).toInt();
        temp++;
        query.exec("insert into loghistory values(" + QString::number(temp, 10) + ", '" + username + "')");
        //qDebug()<<"insert into loghistory values(" + QString::number(temp, 10) + ", '" + username + "')";
    }
}

void newDatabase(QString username)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("./" + username + "/" + username + ".db");  //在工程目录新建一个mytest.db的文件
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }

    QSqlQuery query;//以下执行相关QSL语句
    query.exec("create table baseinfo(id varchar, name varchar, count varchar)");
    query.exec(QObject::tr("insert into baseinfo values(1,'好友分组数',1)"));
    query.exec(QObject::tr("insert into baseinfo values(2,'好友数',0)"));
    query.exec("create table friendsgroup(id varchar, name varchar, friendsingroup varchar)");
    query.exec("insert into friendsgroup values(1, '默认分组', 0)");
    query.exec("create table friends(id varchar, belongto varchar, studentnum varchar, name varchar, photo varchar, sign varchar)");

}

int getFriendsnum(QString username)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("./" + username + "/" + username + ".db");  //在工程目录新建一个mytest.db的文件
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }
    QSqlQuery query;//以下执行相关QSL语句
    query.exec("select id, name, count from baseinfo where id == 2");
    query.next();
    int friendsnum = query.value(2).toInt();
    return friendsnum;
}

int getGroupsnum(QString username)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("./" + username + "/" + username + ".db");  //在工程目录新建一个mytest.db的文件
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }
    QSqlQuery query;//以下执行相关QSL语句
    query.exec("select id, name, count from baseinfo where id == 1");
    query.next();
    int groupsnum = query.value(2).toInt();
    return groupsnum;
}


groupinfo getGroupinfo(QString username, int id)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("./" + username + "/" + username + ".db");
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }
    QSqlQuery query;//以下执行相关QSL语句
    query.exec("select id, name, friendsingroup from friendsgroup where id == " + QString("%1").arg(id));
    query.next();
    groupinfo sth;
    sth.id = query.value(0).toInt();
    sth.name = query.value(1).toString();
    sth.friendsingroup = query.value(2).toInt();
    return sth;
}

friendinfo getFriendinfo(QString username, int id)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("./" + username + "/" + username + ".db");
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }
    QSqlQuery query;//以下执行相关QSL语句
    query.exec("select id, belongto, studentnum, name, photo, sign from friends where id == " + QString("%1").arg(id));
    query.next();
    friendinfo sb;
    sb.id = query.value(0).toInt();
    sb.belongto = query.value(1).toInt();
    sb.studentnum = query.value(2).toString();
    sb.name = query.value(3).toString();
    sb.photo = query.value(4).toString();
    sb.sign = query.value(5).toString();
    //qDebug() << sb.id;    qDebug() << sb.belongto;    qDebug() << sb.studentnum;    qDebug() << sb.name;    qDebug() << sb.photo;    qDebug() << sb.sign;
    return sb;
}

void newGroup(QString username, groupinfo newgi)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动
    qDebug()<<newgi.name;
    db.setDatabaseName("./" + username + "/" + username + ".db");
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }

    int temp = getGroupsnum(username);
    temp++;

    QSqlQuery query;//以下执行相关QSL语句
    query.exec("update baseinfo set count = " + QString::number(temp, 10) + " where id = 1");
    query.exec("insert into friendsgroup values(" + QString::number(newgi.id, 10) + ",'" + newgi.name + "'," + QString::number(newgi.friendsingroup, 10) + ")");
}

void newFriend(QString username, friendinfo newfi)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("./" + username + "/" + username + ".db");
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }

    int temp = getFriendsnum(username);
    temp++;

    QSqlQuery query;//以下执行相关QSL语句
    query.exec("update baseinfo set count = " + QString::number(temp, 10) + " where id = 2");
    query.exec("insert into friends values(" + QString::number(newfi.id, 10) + "," + QString::number(newfi.belongto, 10)
               + ",'" + newfi.studentnum + "','" + newfi.name + "','" + newfi.photo + "','" + newfi.sign + "')");
    int bt = newfi.belongto;
    query.exec("select friendsingroup from friendsgroup where id == " + QString::number(bt, 10));
    query.next();
    temp = query.value(0).toInt();
    temp++;
    query.exec("update friendsgroup set friendsingroup = " + QString::number(temp, 10) + " where id = " + QString::number(bt, 10));
}

void deleteGroup(QString username, int id)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("./" + username + "/" + username + ".db");
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }
    int temp = getGroupsnum(username);
    temp--;
    qDebug()<<temp;
    QSqlQuery query;//以下执行相关QSL语句
    //将分组中的好友移动到默认分组
    query.exec("select friendsingroup from friendsgroup where id == " + QString::number(id, 10));
    qDebug()<<"select friendsingroup from friendsgroup where id == " + QString::number(id, 10);

    query.next();
    int num = query.value(0).toInt();
    qDebug()<<num;
    query.exec("select friendsingroup from friendsgroup where id == 1");

    query.next();
    int defaultnum = query.value(0).toInt();
    qDebug()<<defaultnum;
    defaultnum += num;
    qDebug()<<defaultnum;
    query.exec("update friendsgroup set friendsingroup = " + QString::number(defaultnum, 10) + " where id = 1");
     qDebug()<<"update friendsgroup set friendsingroup = " + QString::number(defaultnum, 10) + " where id = 1";
    query.exec("update friends set belongto = 1 where belongto = " + QString::number(id, 10));
    qDebug()<<"update friends set belongto = 1 where belongto = " + QString::number(id, 10);
     //删除分组
    query.exec("delete from friendsgroup where id = " + QString::number(id, 10));
    //分组总数减1

    qDebug()<<"update baseinfo set count = " + QString::number(temp, 10) + " where id = 1";
    query.exec("update baseinfo set count = " + QString::number(temp, 10) + " where id = 1");
    qDebug()<<"update friendsgroup set id = id - 1 where id > " + QString::number(id, 10);
    query.exec("update friendsgroup set id = id - 1 where id > " + QString::number(id, 10));


}

void deleteFriend(QString username, int id)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("./" + username + "/" + username + ".db");
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }

    int temp = getFriendsnum(username);
    temp--;
    qDebug()<<"deleting friend" << temp;
    QSqlQuery query;//以下执行相关QSL语句
    //所在分组好友数减1
    int bt;
    query.exec("select belongto from friends where id == " + QString::number(id, 10));
    query.next();
    bt = query.value(0).toInt();
    query.exec("update friendsgroup set friendsingroup = friendsingroup - 1 where id = " + QString::number(bt, 10));
    //从数据库中删除
    query.exec("delete from friends where id = " + QString::number(id, 10));
    query.exec("update baseinfo set count = " + QString::number(temp, 10) + " where id = 2");
    query.exec("update friends set id = id - 1 where id > " + QString::number(id, 10));
}

QString generateFilename()
{
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyyMMddhhmmss"); //设置显示格式
    return str;
}

void newFolder(QString username)
{
    QDir *temp = new QDir;
    temp->mkdir(username);
    temp->mkdir("./" + username + "/friendsphoto");
    temp->mkdir("./" + username + "/groupsphoto");
    newDatabase(username);
    for(int i = 0; i < 3; i++)
    {
        QPixmap system(":/image/system_photo" + QString::number(i + 1, 10));
        system.save("./" + username + "/friendsphoto/system_photo" + QString::number(i + 1, 10) + ".jpg");
    }
}


