#include "MainWindow.h"
#include "MainWindow.moc"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    //�����������С
    resize(1500, 800);

    //����Ĭ�ϴ򿪵��ļ�
    currentChatHistoryFile = "newChat.txt";

    // ���
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

    //���ϲ���
    newChatButton = new QPushButton("New chat");
    newChatButton->setObjectName("newChatButton");
    topButtonsLayout->addWidget(newChatButton);

    //���в���
    chatHistory = new QListWidget();
    chatHistory->setObjectName("chatHistory");
    midTextLayout->addWidget(chatHistory);

    //���²���
    settingsButton = new QPushButton("settings");
    settingsButton->setObjectName("settingsButton");
    bottomButtonLayout->addWidget(settingsButton);
    QMenu* settingsMenu = new QMenu();
    settingsMenu->setObjectName("settingsMenu");
    QAction* action1 = new QAction("Light Mode", settingsButton);
    action1->setCheckable(true); // ����Ϊ��ѡ��״̬
    action1->setChecked(true); // �����ʼ״̬����Ϊѡ��
    settingsMenu->addAction(action1);
    QAction* action2 = new QAction("Dark Mode", settingsButton);
    action2->setCheckable(true);// ����Ϊ��ѡ��״̬
    QActionGroup* modeGroup = new QActionGroup(settingsMenu);
    modeGroup->setExclusive(true); // ����Ϊ����ģʽ
    modeGroup->addAction(action1);
    modeGroup->addAction(action2);
    settingsMenu->addAction(action2);
    settingsButton->setMenu(settingsMenu);
    settingsButton->show();

    // �Ҳ�
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

    //�����ϲ���
    chatDisplayArea = new QTextEdit();
    chatDisplayArea->setObjectName("chatDisplayArea");
    chatDisplayArea->setReadOnly(true); // ����Ϊֻ�����Է��û��༭��ʷ�����¼
    highLayout->addWidget(chatDisplayArea);

    //���²���
    inputField = new QTextEdit();
    inputField->setObjectName("inputField");
    sendButton = new QPushButton("send");
    sendButton->setObjectName("sendButton");
    lowLayout->addWidget(inputField);
    lowLayout->addWidget(sendButton);

    // ������
    mainLayout = new QHBoxLayout();
    mainLayout->setObjectName("mainLayout");
    QWidget* centralWidget = new QWidget(this);
    mainLayout->addWidget(leftWidget, 1);
    mainLayout->addWidget(rightWidget, 4);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    //���ݳ־û�
    loadChatHistory();

    //��������
    updateTxtFileList();
    currentThemeFilePath = "./lightStyle.qss";
    loadStylesheet();

    //����
    executablePath = "./FinalTry.exe";


    // �����źźͲ�
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
    QDir directory; // ����QDir����
    if (!directory.exists("txt")) // ���txtĿ¼�Ƿ����
    {
        directory.mkdir("txt"); // ��������ڣ�������Ŀ¼
    }

    // ע�����ļ���ǰ��� txt/ ��ʹ�䱣�浽 txt ���ļ���
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
    QDir directory("./txt"); // txtĿ¼
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
    currentChatHistoryFile = item->text() + ".txt"; // ���µ�ǰ�����¼�ļ�
    QFile sourceFile("./txt/" + currentChatHistoryFile);
    if (!sourceFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "�޷���Դ�ļ�:";
        return;
    }
    QFile targetFile("./default.txt");
    if (!targetFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qWarning() << "�޷���Ĭ���ļ�:";
        return;
    }
    // ��ȡԴ�ļ�����
    QTextStream sourceStream(&sourceFile);
    QString content = sourceStream.readAll();

    // д��Ŀ���ļ�
    QTextStream targetStream(&targetFile);
    targetStream << content;

    sourceFile.close();
    targetFile.close();
    loadChatHistory(); // ���¼��������¼
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
            currentChatHistoryFile = fileName.mid(4); // ���µ�ǰ�����¼�ļ���ȥ��ǰ��� "txt/"
            loadChatHistory(); // ���¼��������¼
            updateTxtFileList(); // ����������ʷ��¼�б�
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

        // ����ļ��Ѿ����򿪣��ر���
        if (file.isOpen()) {
            file.close();
        }

        if (file.exists()) {
            bool removed = file.remove();
            if (!removed) {
                // �����ﴦ���ļ��޷���ɾ������������絯��һ������Ի�����ʾ�û�
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
