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
    //���
    QWidget* leftWidget;
    QVBoxLayout* leftLayout;
    QHBoxLayout* topButtonsLayout;//��
    QHBoxLayout* midTextLayout;//��
    QHBoxLayout* bottomButtonLayout;//��

    // ���ϲ���
    QPushButton* newChatButton;
    
    //���в���
    QListWidget* chatHistory;

    //���²���
    QPushButton* settingsButton;
    QMenu* settingsMenu;
    QActionGroup* modeGroup;
    
    // �Ҳ�
    QWidget* rightWidget;
    QVBoxLayout* rightLayout;
    QHBoxLayout* highLayout;
    QHBoxLayout* lowLayout;
    
    //�����ϲ���
    QTextEdit* chatDisplayArea;

    
    //���²���
    QTextEdit* inputField;
    QPushButton* sendButton;
    
    // ������
    QHBoxLayout* mainLayout;

    //��¼��ǰ�򿪵��ļ�
    QString currentChatHistoryFile;

    //�����ӳ���
    QProcess process;
    QString executablePath;
    QStringList arguments;

    QListWidgetItem* currentItem;
    QString currentThemeFilePath;
    
};



#endif // MAINWINDOW_H