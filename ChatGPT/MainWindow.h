#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include "QtWidgets/qmainwindow.h"
#include "QtWidgets/qpushbutton.h"
#include "QtWidgets/qtextedit.h"
#include "QtWidgets/qlistwidget.h"
#include "QtWidgets/qlayout.h"
#include "QtWidgets/qlistview.h"
#include "QtWidgets/qlineedit.h"
#include "QtWidgets/qstatusbar.h"
#include "QtWidgets/qmenu.h"
#include "QtWidgets/qmenubar.h"
#include "QtWidgets/qlabel.h"
#include "QtWidgets/qcombobox.h"
#include "QtWidgets/qformlayout.h"
#include "QtWidgets/qscrollarea.h"
#include "QtWidgets/qscrollbar.h"
#include "QtCore/qfile.h"
#include "QtCore/qtextstream.h"
#include "QtCore/qdir.h"
#include "QtCore/qfileinfo.h"
#include "QtCore/qtimer.h"
#include "QtCore/qcoreapplication.h"
#include "QtCore/qprocess.h"
#include "QtGui/qevent.h"
#include "QtGui/qtextformat.h"
#include "QtWidgets/qaction.h"
#include "QtWidgets/qmessagebox.h"
#include "QtWidgets/qstyle.h"
#include "QtWidgets/qstylepainter.h"
#include "QtGui/qtouchdevice.h"
#include "QtCore/qdebug.h"

class MainWindow : public QMainWindow 
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void saveMessageToFile(const QString& message);
    void saveMessage(const QString& message);
    void sendChat();
    void loadChatHistory();
    void updateTxtFileList();
    void changeChatHistoryFile(QListWidgetItem* item);
    void addAnswer();
    void createNewChat();
    void deleteChatHistory();
    void loadStylesheet();
    void changeTheme();

protected:
    void contextMenuEvent(QContextMenuEvent* event) override;

private:
    //左侧
    QWidget* leftWidget;
    QVBoxLayout* leftLayout;
    QHBoxLayout* topButtonsLayout;//上
    QHBoxLayout* midTextLayout;//中
    QHBoxLayout* bottomButtonLayout;//下

    // 左上部分
    QPushButton* newChatButton;
    
    //左中部分
    QListWidget* chatHistory;

    //左下部分
    QPushButton* settingsButton;
    QMenu* settingsMenu;
    QActionGroup* modeGroup;
    
    // 右侧
    QWidget* rightWidget;
    QVBoxLayout* rightLayout;
    QHBoxLayout* highLayout;
    QHBoxLayout* lowLayout;
    
    //右中上部分
    QTextEdit* chatDisplayArea;

    
    //右下部分
    QTextEdit* inputField;
    QPushButton* sendButton;
    
    // 主布局
    QHBoxLayout* mainLayout;

    //记录当前打开的文件
    QString currentChatHistoryFile;

    //运行子程序
    QProcess process;
    QString executablePath;
    QStringList arguments;

    QListWidgetItem* currentItem;
    QString currentThemeFilePath;
    
};



#endif // MAINWINDOW_H