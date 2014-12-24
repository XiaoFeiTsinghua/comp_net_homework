#ifndef DATABASE_H
#define DATABASE_H

#include <QtCore/QCoreApplication>
#include <QtSql>
#include <QString>
#include <QDateTime>
#include <QDir>
#include <QPixmap>

struct groupinfo
{
    int id;
    QString name;
    int friendsingroup;
};

struct friendinfo
{
    int id;
    int belongto;
    QString studentnum;
    QString name;
    QString photo;
    QString sign;
};

void newHistroy();
int getRemember();
void setRemember(int flag);
void addUser(QString username);
int getUsernum();//还没写
void getUser(int id);//还没写

void newDatabase(QString username);
void newFolder(QString username);
int getFriendsnum(QString username);
int getGroupsnum(QString username);
groupinfo getGroupinfo(QString username, int id);
friendinfo getFriendinfo(QString username, int id);
void newGroup(QString username, groupinfo newgi);
void newFriend(QString username, friendinfo newfi);
void deleteGroup(QString username, int id);
void deleteFriend(QString username, int id);
QString generateFilename();

#endif // DATABASE_H
