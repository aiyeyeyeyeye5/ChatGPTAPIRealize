#include "MainWindow.h"
#include "MainWindow.moc"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    //设置主界面大小
    resize(1500, 800);

    //设置默认打开的文件
    currentChatHistoryFile = "newChat.txt";

    // 左侧
    QWidget* leftWidget = new QWidget();
    leftWidget->setObjectName("leftWidget");
    leftLayout = new QVBoxLayout(leftWidget);
    leftLayout->setObjectName("leftLayout");
    topButtonsLayout = new QHBoxLayout();
    topButtonsLayout->setObjectName("topButtonsLayout");
    midTextLayout = new QHBoxLayout();
    midTextLayout->setObjectName("midTextLayout");
    bottomButtonLayout = new QHBoxLayout();
    bottomButtonLayout->setObjectName("bottomButtonLayout");
    leftLayout->addLayout(topButtonsLayout, 2);
    leftLayout->addLayout(midTextLayout, 6);
    leftLayout->addLayout(bottomButtonLayout, 2);
    leftWidget->setLayout(leftLayout);

    //左上部分
    newChatButton = new QPushButton("New chat");
    newChatButton->setObjectName("newChatButton");
    topButtonsLayout->addWidget(newChatButton);

    //左中部分
    chatHistory = new QListWidget();
    chatHistory->setObjectName("chatHistory");
    midTextLayout->addWidget(chatHistory);

    //左下部分
    settingsButton = new QPushButton("settings");
    settingsButton->setObjectName("settingsButton");
    bottomButtonLayout->addWidget(settingsButton);
    QMenu* settingsMenu = new QMenu();
    settingsMenu->setObjectName("settingsMenu");
    QAction* action1 = new QAction("Light Mode", settingsButton);
    action1->setCheckable(true); // 设置为可选中状态
    action1->setChecked(true); // 将其初始状态设置为选中
    settingsMenu->addAction(action1);
    QAction* action2 = new QAction("Dark Mode", settingsButton);
    action2->setCheckable(true);// 设置为可选中状态
    QActionGroup* modeGroup = new QActionGroup(settingsMenu);
    modeGroup->setExclusive(true); // 设置为互斥模式
    modeGroup->addAction(action1);
    modeGroup->addAction(action2);
    settingsMenu->addAction(action2);
    settingsButton->setMenu(settingsMenu);
    settingsButton->show();

    // 右侧
    QWidget* rightWidget = new QWidget();
    rightWidget->setObjectName("rightWidget");
    rightLayout = new QVBoxLayout(rightWidget);
    rightLayout->setObjectName("rightLayout");
    highLayout = new QHBoxLayout();
    highLayout->setObjectName("highLayout");
    lowLayout = new QHBoxLayout();
    lowLayout->setObjectName("lowLayout");
    rightLayout->addLayout(highLayout, 7);
    rightLayout->addLayout(lowLayout, 3);
    rightWidget->setLayout(rightLayout);

    //右中上部分
    chatDisplayArea = new QTextEdit();
    chatDisplayArea->setObjectName("chatDisplayArea");
    chatDisplayArea->setReadOnly(true); // 设置为只读，以防用户编辑历史聊天记录
    highLayout->addWidget(chatDisplayArea);

    //右下部分
    inputField = new QTextEdit();
    inputField->setObjectName("inputField");
    sendButton = new QPushButton("send");
    sendButton->setObjectName("sendButton");
    lowLayout->addWidget(inputField);
    lowLayout->addWidget(sendButton);

    // 主布局
    mainLayout = new QHBoxLayout();
    mainLayout->setObjectName("mainLayout");
    QWidget* centralWidget = new QWidget(this);
    mainLayout->addWidget(leftWidget, 1);
    mainLayout->addWidget(rightWidget, 4);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    //数据持久化
    loadChatHistory();

    //更新主题
    updateTxtFileList();
    currentThemeFilePath = "./lightStyle.qss";
    loadStylesheet();

    //程序
    executablePath = "./FinalTry.exe";


    // 连接信号和槽
    connect(sendButton, &QPushButton::pressed, this, &MainWindow::sendChat);
    connect(chatHistory, &QListWidget::itemClicked, this, &MainWindow::changeChatHistoryFile);
    connect(newChatButton, &QPushButton::clicked, this, &MainWindow::createNewChat);
    connect(action1, &QAction::triggered, this, &MainWindow::changeTheme);
    connect(action2, &QAction::triggered, this, &MainWindow::changeTheme);
}

void MainWindow::loadStylesheet()
{
    QFile styleFile(currentThemeFilePath); // Make sure this path is correct.
    if (!styleFile.open(QFile::ReadOnly)) {
        qDebug() << "Cannot open file for reading: " << qPrintable(styleFile.errorString());
    }
    else {
        QString styleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(styleSheet);
    }
}

MainWindow::~MainWindow()
{
}

void MainWindow::saveMessageToFile(const QString& message)
{
    QDir directory; // 创建QDir对象
    if (!directory.exists("txt")) // 检查txt目录是否存在
    {
        directory.mkdir("txt"); // 如果不存在，创建该目录
    }

    // 注意在文件名前添加 txt/ ，使其保存到 txt 子文件夹
    QFile file("txt/" + currentChatHistoryFile);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file);
        out <<  message << "\n";
        file.close();
    }
} 

void MainWindow::saveMessage(const QString& message)
{
    QFile file("./default.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file);
        out << message << "\n";
        file.close();
    }
}

void MainWindow::sendChat()
{
    QString message = inputField->toPlainText();
    message.replace(" ", "");
    message.replace("\n", "");
    if (message.isEmpty())
    {
        return;
    }
    sendButton->setEnabled(false);
    sendButton->setCheckable(true);
    QString preText = "user:";
    message.prepend(preText);
    saveMessageToFile(message);
    saveMessage(message);
    loadChatHistory();
    inputField->clear();
    process.start(executablePath,arguments);
    process.waitForFinished(-1);
    addAnswer();
    loadChatHistory();
    sendButton->setEnabled(true);
    sendButton->setCheckable(false);
}

void MainWindow::loadChatHistory()
{
    chatDisplayArea->clear();

    QFile file("txt/" + currentChatHistoryFile);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            if (!line.startsWith("system:")) {
                chatDisplayArea->append(line);
            }
        }
        file.close();
    }
}

void MainWindow::updateTxtFileList()
{
    QDir directory("./txt"); // txt目录
    QFileInfoList txtFilesInfo = directory.entryInfoList(QStringList() << "*.txt", QDir::Files);
    chatHistory->clear();

    foreach(QFileInfo fileInfo, txtFilesInfo) {
        QString fileName = fileInfo.baseName();
        QListWidgetItem* item = new QListWidgetItem(fileName);
        chatHistory->addItem(item);
    }
}

void MainWindow::changeChatHistoryFile(QListWidgetItem* item)
{
    currentChatHistoryFile = item->text() + ".txt"; // 更新当前聊天记录文件
    QFile sourceFile("./txt/" + currentChatHistoryFile);
    if (!sourceFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "无法打开源文件:";
        return;
    }
    QFile targetFile("./default.txt");
    if (!targetFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qWarning() << "无法打开默认文件:";
        return;
    }
    // 读取源文件内容
    QTextStream sourceStream(&sourceFile);
    QString content = sourceStream.readAll();

    // 写入目标文件
    QTextStream targetStream(&targetFile);
    targetStream << content;

    sourceFile.close();
    targetFile.close();
    loadChatHistory(); // 重新加载聊天记录
}

void MainWindow::addAnswer()
{
    QFile file("default.txt");
    QString lastLine;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            lastLine = in.readLine();
        }
        file.close();
    }

    QFile file1("txt/" + currentChatHistoryFile);
    if (file1.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file1);
        out << lastLine << "\n";
        file1.close();
    }
}

void MainWindow::createNewChat()
{
    QDir directory;
    if (!directory.exists("txt"))
    {
        directory.mkdir("txt");
    }

    int counter = 0;
    while (true)
    {
        QString fileName = "txt/newChat";
        if (counter > 0)
        {
            fileName += QString::number(counter);
        }
        fileName += ".txt";

        if (!QFile::exists(fileName))
        {
            QFile file(fileName);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QTextStream out(&file);
                out << "system:normal" << "\n";
                file.close();
            }
            currentChatHistoryFile = fileName.mid(4); // 更新当前聊天记录文件，去掉前面的 "txt/"
            loadChatHistory(); // 重新加载聊天记录
            updateTxtFileList(); // 更新聊天历史记录列表
            break;
        }

        ++counter;
    }
}

void MainWindow::contextMenuEvent(QContextMenuEvent* event) {
    if (currentItem = chatHistory->itemAt(chatHistory->viewport()->mapFromGlobal(event->globalPos())); currentItem != nullptr) {
        QMenu contextMenu(tr("Context menu"), this);
        QAction actionDelete(tr("Delete"), this);
        connect(&actionDelete, &QAction::triggered, this, &MainWindow::deleteChatHistory);
        contextMenu.addAction(&actionDelete);
        contextMenu.exec(event->globalPos());
    }
}

void MainWindow::deleteChatHistory() {
    if (currentItem) {
        QString filename = "./txt/" + currentItem->text() + ".txt";
        QFile file(filename);

        // 如果文件已经被打开，关闭它
        if (file.isOpen()) {
            file.close();
        }

        if (file.exists()) {
            bool removed = file.remove();
            if (!removed) {
                // 在这里处理文件无法被删除的情况，比如弹出一个错误对话框提示用户
            }
            else {
                delete currentItem;
                currentItem = nullptr;
            }
        }
    }
}

void MainWindow::changeTheme()
{
    QAction* selectedAction = qobject_cast<QAction*>(sender());
    if (selectedAction) {
        if (selectedAction->text() == "Light Mode") {
            currentThemeFilePath = "./lightStyle.qss";
        }
        else if (selectedAction->text() == "Dark Mode") {
            currentThemeFilePath = "./darkStyle.qss";
        }
        loadStylesheet();
    }
}
