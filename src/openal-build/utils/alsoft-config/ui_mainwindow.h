/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionSave_As;
    QAction *actionLoad;
    QWidget *centralWidget;
    QPushButton *applyButton;
    QTabWidget *tabWidget;
    QWidget *tab_3;
    QComboBox *sampleFormatCombo;
    QLabel *label_5;
    QLabel *label_6;
    QComboBox *channelConfigCombo;
    QComboBox *sampleRateCombo;
    QLabel *label_7;
    QGroupBox *groupBox;
    QRadioButton *hrtfEnableButton;
    QRadioButton *hrtfDisableButton;
    QRadioButton *hrtfForceButton;
    QListWidget *hrtfFileList;
    QPushButton *hrtfAddButton;
    QPushButton *hrtfRemoveButton;
    QGroupBox *groupBox_3;
    QWidget *widget;
    QLabel *label_11;
    QSlider *periodCountSlider;
    QLineEdit *periodCountEdit;
    QWidget *widget_2;
    QSlider *periodSizeSlider;
    QLabel *label_10;
    QLineEdit *periodSizeEdit;
    QWidget *tab_2;
    QLineEdit *srcCountLineEdit;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *effectSlotLineEdit;
    QLabel *label_8;
    QLineEdit *srcSendLineEdit;
    QLabel *label_9;
    QComboBox *resamplerComboBox;
    QGroupBox *groupBox_2;
    QCheckBox *enableSSECheckBox;
    QCheckBox *enableSSE2CheckBox;
    QCheckBox *enableNeonCheckBox;
    QCheckBox *enableSSE41CheckBox;
    QWidget *tab;
    QCheckBox *backendCheckBox;
    QListWidget *enabledBackendList;
    QLabel *label;
    QListWidget *disabledBackendList;
    QLabel *label_2;
    QWidget *tab_4;
    QCheckBox *emulateEaxCheckBox;
    QGroupBox *groupBox_4;
    QSlider *reverbBoostSlider;
    QLineEdit *reverbBoostEdit;
    QLabel *label_12;
    QGroupBox *groupBox_5;
    QCheckBox *enableEaxReverbCheck;
    QCheckBox *enableStdReverbCheck;
    QCheckBox *enableChorusCheck;
    QCheckBox *enableDistortionCheck;
    QCheckBox *enableEchoCheck;
    QCheckBox *enableEqualizerCheck;
    QCheckBox *enableFlangerCheck;
    QCheckBox *enableModulatorCheck;
    QCheckBox *enableDedicatedCheck;
    QCheckBox *enableCompressorCheck;
    QLabel *label_13;
    QComboBox *defaultReverbComboBox;
    QMenuBar *menuBar;
    QMenu *menuFile;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(564, 454);
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("preferences-desktop-sound");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8(""), QSize(), QIcon::Normal, QIcon::Off);
        }
        MainWindow->setWindowIcon(icon);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        QIcon icon1;
        iconThemeName = QString::fromUtf8("application-exit");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QString::fromUtf8(""), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionQuit->setIcon(icon1);
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QString::fromUtf8("actionSave_As"));
        QIcon icon2;
        iconThemeName = QString::fromUtf8("document-save-as");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QString::fromUtf8(""), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionSave_As->setIcon(icon2);
        actionLoad = new QAction(MainWindow);
        actionLoad->setObjectName(QString::fromUtf8("actionLoad"));
        QIcon icon3;
        iconThemeName = QString::fromUtf8("document-open");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon3 = QIcon::fromTheme(iconThemeName);
        } else {
            icon3.addFile(QString::fromUtf8(""), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionLoad->setIcon(icon3);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        applyButton = new QPushButton(centralWidget);
        applyButton->setObjectName(QString::fromUtf8("applyButton"));
        applyButton->setGeometry(QRect(470, 405, 81, 25));
        QIcon icon4;
        iconThemeName = QString::fromUtf8("dialog-ok-apply");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon4 = QIcon::fromTheme(iconThemeName);
        } else {
            icon4.addFile(QString::fromUtf8(""), QSize(), QIcon::Normal, QIcon::Off);
        }
        applyButton->setIcon(icon4);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 0, 541, 401));
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        sampleFormatCombo = new QComboBox(tab_3);
        sampleFormatCombo->setObjectName(QString::fromUtf8("sampleFormatCombo"));
        sampleFormatCombo->setGeometry(QRect(120, 20, 188, 22));
        sampleFormatCombo->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        label_5 = new QLabel(tab_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 20, 101, 21));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_6 = new QLabel(tab_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 50, 101, 21));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        channelConfigCombo = new QComboBox(tab_3);
        channelConfigCombo->setObjectName(QString::fromUtf8("channelConfigCombo"));
        channelConfigCombo->setGeometry(QRect(120, 50, 227, 22));
        channelConfigCombo->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        sampleRateCombo = new QComboBox(tab_3);
        sampleRateCombo->setObjectName(QString::fromUtf8("sampleRateCombo"));
        sampleRateCombo->setGeometry(QRect(120, 80, 111, 22));
        sampleRateCombo->setEditable(true);
        sampleRateCombo->setInsertPolicy(QComboBox::NoInsert);
        sampleRateCombo->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        label_7 = new QLabel(tab_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 80, 101, 21));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        groupBox = new QGroupBox(tab_3);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 200, 511, 161));
        hrtfEnableButton = new QRadioButton(groupBox);
        hrtfEnableButton->setObjectName(QString::fromUtf8("hrtfEnableButton"));
        hrtfEnableButton->setGeometry(QRect(20, 30, 71, 21));
        hrtfEnableButton->setChecked(true);
        hrtfDisableButton = new QRadioButton(groupBox);
        hrtfDisableButton->setObjectName(QString::fromUtf8("hrtfDisableButton"));
        hrtfDisableButton->setGeometry(QRect(20, 50, 71, 21));
        hrtfForceButton = new QRadioButton(groupBox);
        hrtfForceButton->setObjectName(QString::fromUtf8("hrtfForceButton"));
        hrtfForceButton->setGeometry(QRect(20, 70, 71, 21));
        hrtfFileList = new QListWidget(groupBox);
        hrtfFileList->setObjectName(QString::fromUtf8("hrtfFileList"));
        hrtfFileList->setGeometry(QRect(110, 30, 301, 121));
        hrtfFileList->setDragEnabled(false);
        hrtfFileList->setDragDropMode(QAbstractItemView::InternalMove);
        hrtfFileList->setAlternatingRowColors(true);
        hrtfFileList->setSelectionMode(QAbstractItemView::ExtendedSelection);
        hrtfFileList->setTextElideMode(Qt::ElideNone);
        hrtfAddButton = new QPushButton(groupBox);
        hrtfAddButton->setObjectName(QString::fromUtf8("hrtfAddButton"));
        hrtfAddButton->setGeometry(QRect(419, 30, 81, 25));
        QIcon icon5;
        iconThemeName = QString::fromUtf8("list-add");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon5 = QIcon::fromTheme(iconThemeName);
        } else {
            icon5.addFile(QString::fromUtf8(""), QSize(), QIcon::Normal, QIcon::Off);
        }
        hrtfAddButton->setIcon(icon5);
        hrtfAddButton->setFlat(false);
        hrtfRemoveButton = new QPushButton(groupBox);
        hrtfRemoveButton->setObjectName(QString::fromUtf8("hrtfRemoveButton"));
        hrtfRemoveButton->setGeometry(QRect(419, 60, 81, 25));
        QIcon icon6;
        iconThemeName = QString::fromUtf8("list-remove");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon6 = QIcon::fromTheme(iconThemeName);
        } else {
            icon6.addFile(QString::fromUtf8(""), QSize(), QIcon::Normal, QIcon::Off);
        }
        hrtfRemoveButton->setIcon(icon6);
        groupBox_3 = new QGroupBox(tab_3);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 110, 511, 91));
        widget = new QWidget(groupBox_3);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(260, 20, 241, 51));
        label_11 = new QLabel(widget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(20, 0, 201, 21));
        label_11->setAlignment(Qt::AlignCenter);
        periodCountSlider = new QSlider(widget);
        periodCountSlider->setObjectName(QString::fromUtf8("periodCountSlider"));
        periodCountSlider->setGeometry(QRect(70, 20, 160, 23));
        periodCountSlider->setMinimum(1);
        periodCountSlider->setMaximum(16);
        periodCountSlider->setSingleStep(1);
        periodCountSlider->setPageStep(2);
        periodCountSlider->setValue(1);
        periodCountSlider->setTracking(true);
        periodCountSlider->setOrientation(Qt::Horizontal);
        periodCountSlider->setTickPosition(QSlider::TicksBelow);
        periodCountSlider->setTickInterval(1);
        periodCountEdit = new QLineEdit(widget);
        periodCountEdit->setObjectName(QString::fromUtf8("periodCountEdit"));
        periodCountEdit->setGeometry(QRect(20, 20, 51, 22));
        widget_2 = new QWidget(groupBox_3);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(10, 20, 241, 51));
        periodSizeSlider = new QSlider(widget_2);
        periodSizeSlider->setObjectName(QString::fromUtf8("periodSizeSlider"));
        periodSizeSlider->setGeometry(QRect(60, 20, 160, 23));
        periodSizeSlider->setMinimum(0);
        periodSizeSlider->setMaximum(8192);
        periodSizeSlider->setSingleStep(64);
        periodSizeSlider->setPageStep(1024);
        periodSizeSlider->setValue(0);
        periodSizeSlider->setTracking(true);
        periodSizeSlider->setOrientation(Qt::Horizontal);
        periodSizeSlider->setTickPosition(QSlider::TicksBelow);
        periodSizeSlider->setTickInterval(512);
        label_10 = new QLabel(widget_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 0, 201, 21));
        label_10->setAlignment(Qt::AlignCenter);
        periodSizeEdit = new QLineEdit(widget_2);
        periodSizeEdit->setObjectName(QString::fromUtf8("periodSizeEdit"));
        periodSizeEdit->setGeometry(QRect(10, 20, 51, 22));
        tabWidget->addTab(tab_3, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        srcCountLineEdit = new QLineEdit(tab_2);
        srcCountLineEdit->setObjectName(QString::fromUtf8("srcCountLineEdit"));
        srcCountLineEdit->setGeometry(QRect(190, 20, 51, 22));
        srcCountLineEdit->setMaxLength(3);
        srcCountLineEdit->setFrame(true);
        label_3 = new QLabel(tab_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 20, 171, 21));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 50, 171, 21));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        effectSlotLineEdit = new QLineEdit(tab_2);
        effectSlotLineEdit->setObjectName(QString::fromUtf8("effectSlotLineEdit"));
        effectSlotLineEdit->setGeometry(QRect(190, 50, 51, 22));
        effectSlotLineEdit->setMaxLength(1);
        effectSlotLineEdit->setFrame(true);
        label_8 = new QLabel(tab_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 80, 171, 21));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        srcSendLineEdit = new QLineEdit(tab_2);
        srcSendLineEdit->setObjectName(QString::fromUtf8("srcSendLineEdit"));
        srcSendLineEdit->setGeometry(QRect(190, 80, 51, 22));
        srcSendLineEdit->setMaxLength(1);
        label_9 = new QLabel(tab_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(30, 120, 71, 21));
        resamplerComboBox = new QComboBox(tab_2);
        resamplerComboBox->setObjectName(QString::fromUtf8("resamplerComboBox"));
        resamplerComboBox->setGeometry(QRect(110, 120, 185, 22));
        resamplerComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        groupBox_2 = new QGroupBox(tab_2);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 150, 511, 91));
        enableSSECheckBox = new QCheckBox(groupBox_2);
        enableSSECheckBox->setObjectName(QString::fromUtf8("enableSSECheckBox"));
        enableSSECheckBox->setGeometry(QRect(180, 20, 71, 31));
        enableSSECheckBox->setChecked(true);
        enableSSE2CheckBox = new QCheckBox(groupBox_2);
        enableSSE2CheckBox->setObjectName(QString::fromUtf8("enableSSE2CheckBox"));
        enableSSE2CheckBox->setGeometry(QRect(180, 50, 71, 31));
        enableSSE2CheckBox->setChecked(true);
        enableNeonCheckBox = new QCheckBox(groupBox_2);
        enableNeonCheckBox->setObjectName(QString::fromUtf8("enableNeonCheckBox"));
        enableNeonCheckBox->setGeometry(QRect(260, 50, 71, 31));
        enableNeonCheckBox->setChecked(true);
        enableSSE41CheckBox = new QCheckBox(groupBox_2);
        enableSSE41CheckBox->setObjectName(QString::fromUtf8("enableSSE41CheckBox"));
        enableSSE41CheckBox->setGeometry(QRect(260, 20, 71, 31));
        enableSSE41CheckBox->setChecked(true);
        tabWidget->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        backendCheckBox = new QCheckBox(tab);
        backendCheckBox->setObjectName(QString::fromUtf8("backendCheckBox"));
        backendCheckBox->setGeometry(QRect(170, 200, 161, 21));
        backendCheckBox->setChecked(true);
        enabledBackendList = new QListWidget(tab);
        enabledBackendList->setObjectName(QString::fromUtf8("enabledBackendList"));
        enabledBackendList->setGeometry(QRect(40, 40, 191, 151));
        enabledBackendList->setDragDropMode(QAbstractItemView::InternalMove);
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 20, 191, 20));
        disabledBackendList = new QListWidget(tab);
        disabledBackendList->setObjectName(QString::fromUtf8("disabledBackendList"));
        disabledBackendList->setGeometry(QRect(270, 40, 191, 151));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(270, 20, 191, 20));
        tabWidget->addTab(tab, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        emulateEaxCheckBox = new QCheckBox(tab_4);
        emulateEaxCheckBox->setObjectName(QString::fromUtf8("emulateEaxCheckBox"));
        emulateEaxCheckBox->setGeometry(QRect(10, 60, 161, 21));
        emulateEaxCheckBox->setLayoutDirection(Qt::RightToLeft);
        groupBox_4 = new QGroupBox(tab_4);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 100, 511, 61));
        reverbBoostSlider = new QSlider(groupBox_4);
        reverbBoostSlider->setObjectName(QString::fromUtf8("reverbBoostSlider"));
        reverbBoostSlider->setGeometry(QRect(10, 30, 391, 23));
        reverbBoostSlider->setMinimum(-120);
        reverbBoostSlider->setMaximum(120);
        reverbBoostSlider->setOrientation(Qt::Horizontal);
        reverbBoostSlider->setTickPosition(QSlider::TicksBelow);
        reverbBoostSlider->setTickInterval(10);
        reverbBoostEdit = new QLineEdit(groupBox_4);
        reverbBoostEdit->setObjectName(QString::fromUtf8("reverbBoostEdit"));
        reverbBoostEdit->setGeometry(QRect(410, 30, 51, 22));
        reverbBoostEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_12 = new QLabel(groupBox_4);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(460, 30, 31, 21));
        groupBox_5 = new QGroupBox(tab_4);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 170, 511, 191));
        enableEaxReverbCheck = new QCheckBox(groupBox_5);
        enableEaxReverbCheck->setObjectName(QString::fromUtf8("enableEaxReverbCheck"));
        enableEaxReverbCheck->setGeometry(QRect(70, 30, 131, 21));
        enableEaxReverbCheck->setChecked(true);
        enableStdReverbCheck = new QCheckBox(groupBox_5);
        enableStdReverbCheck->setObjectName(QString::fromUtf8("enableStdReverbCheck"));
        enableStdReverbCheck->setGeometry(QRect(70, 60, 131, 21));
        enableStdReverbCheck->setChecked(true);
        enableChorusCheck = new QCheckBox(groupBox_5);
        enableChorusCheck->setObjectName(QString::fromUtf8("enableChorusCheck"));
        enableChorusCheck->setGeometry(QRect(70, 90, 131, 21));
        enableChorusCheck->setChecked(true);
        enableDistortionCheck = new QCheckBox(groupBox_5);
        enableDistortionCheck->setObjectName(QString::fromUtf8("enableDistortionCheck"));
        enableDistortionCheck->setGeometry(QRect(70, 150, 131, 21));
        enableDistortionCheck->setChecked(true);
        enableEchoCheck = new QCheckBox(groupBox_5);
        enableEchoCheck->setObjectName(QString::fromUtf8("enableEchoCheck"));
        enableEchoCheck->setGeometry(QRect(320, 30, 131, 21));
        enableEchoCheck->setChecked(true);
        enableEqualizerCheck = new QCheckBox(groupBox_5);
        enableEqualizerCheck->setObjectName(QString::fromUtf8("enableEqualizerCheck"));
        enableEqualizerCheck->setGeometry(QRect(320, 60, 131, 21));
        enableEqualizerCheck->setChecked(true);
        enableFlangerCheck = new QCheckBox(groupBox_5);
        enableFlangerCheck->setObjectName(QString::fromUtf8("enableFlangerCheck"));
        enableFlangerCheck->setGeometry(QRect(320, 90, 131, 21));
        enableFlangerCheck->setChecked(true);
        enableModulatorCheck = new QCheckBox(groupBox_5);
        enableModulatorCheck->setObjectName(QString::fromUtf8("enableModulatorCheck"));
        enableModulatorCheck->setGeometry(QRect(320, 120, 131, 21));
        enableModulatorCheck->setChecked(true);
        enableDedicatedCheck = new QCheckBox(groupBox_5);
        enableDedicatedCheck->setObjectName(QString::fromUtf8("enableDedicatedCheck"));
        enableDedicatedCheck->setGeometry(QRect(320, 150, 131, 21));
        enableDedicatedCheck->setChecked(true);
        enableCompressorCheck = new QCheckBox(groupBox_5);
        enableCompressorCheck->setObjectName(QString::fromUtf8("enableCompressorCheck"));
        enableCompressorCheck->setGeometry(QRect(70, 120, 111, 21));
        enableCompressorCheck->setChecked(true);
        label_13 = new QLabel(tab_4);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 20, 141, 21));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        defaultReverbComboBox = new QComboBox(tab_4);
        defaultReverbComboBox->setObjectName(QString::fromUtf8("defaultReverbComboBox"));
        defaultReverbComboBox->setGeometry(QRect(160, 20, 131, 22));
        defaultReverbComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        tabWidget->addTab(tab_4, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 564, 19));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionLoad);
        menuFile->addAction(actionSave_As);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);

        retranslateUi(MainWindow);
        QObject::connect(actionQuit, SIGNAL(activated()), MainWindow, SLOT(close()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "OpenAL Soft Configuration", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("MainWindow", "&Quit", 0, QApplication::UnicodeUTF8));
        actionSave_As->setText(QApplication::translate("MainWindow", "Save &As...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSave_As->setToolTip(QApplication::translate("MainWindow", "Save Configuration As", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionLoad->setText(QApplication::translate("MainWindow", "&Load...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionLoad->setToolTip(QApplication::translate("MainWindow", "Load Configuration File", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        applyButton->setText(QApplication::translate("MainWindow", "Apply", 0, QApplication::UnicodeUTF8));
        sampleFormatCombo->clear();
        sampleFormatCombo->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "- Autodetect -", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "int8 - signed 8-bit int", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "uint8 - unsigned 8-bit int", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "int16 - signed 16-bit int", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "uint16 - unsigned 16-bit int", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "int32 - signed 32-bit int", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "uint32 - unsigned 32-bit int", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "float32 - 32-bit float", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        sampleFormatCombo->setToolTip(QApplication::translate("MainWindow", "The output sample type. Currently, all mixing is done with 32-bit\n"
"float and converted to the output sample type as needed.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_5->setText(QApplication::translate("MainWindow", "Sample Format:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "Channels:", 0, QApplication::UnicodeUTF8));
        channelConfigCombo->clear();
        channelConfigCombo->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "- Autodetect -", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "mono - 1-channel Mono", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "stereo - 2-channel Stereo", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "quad - 4-channel Quadraphonic", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "surround51 - 5.1 Surround Sound", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "surround61 - 6.1 Surround Sound", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "surround71 - 7.1 Surround Sound", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        channelConfigCombo->setToolTip(QApplication::translate("MainWindow", "The output channel configuration. Note that not all backends\n"
"can properly detect the channel configuration and may default\n"
"to stereo output.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        sampleRateCombo->clear();
        sampleRateCombo->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "- Autodetect -", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "96000", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "48000", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "44100", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "32000", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "22050", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "16000", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "11025", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "8000", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        sampleRateCombo->setToolTip(QApplication::translate("MainWindow", "The playback/mixing sample rate.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_7->setText(QApplication::translate("MainWindow", "Sample Rate:", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "HRTF (Stereo only)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        hrtfEnableButton->setToolTip(QApplication::translate("MainWindow", "Allows applications to request HRTF mixing.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        hrtfEnableButton->setText(QApplication::translate("MainWindow", "Enable", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        hrtfDisableButton->setToolTip(QApplication::translate("MainWindow", "Does not allow HRTF mixing, even when requested.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        hrtfDisableButton->setText(QApplication::translate("MainWindow", "Disable", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        hrtfForceButton->setToolTip(QApplication::translate("MainWindow", "Attempts to force HRTF mixing, even if applications request not\n"
"to do it. This may override the channel configuration and\n"
"sample rate.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        hrtfForceButton->setText(QApplication::translate("MainWindow", "Force", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        hrtfFileList->setToolTip(QApplication::translate("MainWindow", "A list of files containing HRTF data sets. The listed data sets\n"
"are used in place of the default sets. The filenames may\n"
"contain these markers, which will be replaced as needed:\n"
"%r - Device sampling rate\n"
"%% - Percent sign (%)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        hrtfAddButton->setText(QApplication::translate("MainWindow", "Add...", 0, QApplication::UnicodeUTF8));
        hrtfRemoveButton->setText(QApplication::translate("MainWindow", "Remove", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Buffer Metrics", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        widget->setToolTip(QApplication::translate("MainWindow", "The number of update periods. Higher values create a larger\n"
"mix ahead, which helps protect against skips when the CPU is\n"
"under load, but increases the delay between a sound getting\n"
"mixed and being heard.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_11->setText(QApplication::translate("MainWindow", "Period Count", 0, QApplication::UnicodeUTF8));
        periodCountEdit->setPlaceholderText(QApplication::translate("MainWindow", "4", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        widget_2->setToolTip(QApplication::translate("MainWindow", "The update period size, in sample frames. This is the number of\n"
"frames needed for each mixing update.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_10->setText(QApplication::translate("MainWindow", "Period Samples", 0, QApplication::UnicodeUTF8));
        periodSizeEdit->setPlaceholderText(QApplication::translate("MainWindow", "1024", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Playback", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        srcCountLineEdit->setToolTip(QApplication::translate("MainWindow", "The maximum number of allocatable sources. Lower values may\n"
"help for systems with apps that try to play more sounds than\n"
"the CPU can handle.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        srcCountLineEdit->setInputMask(QString());
        srcCountLineEdit->setPlaceholderText(QApplication::translate("MainWindow", "256", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Number of Sound Sources:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Number of Effect Slots:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        effectSlotLineEdit->setToolTip(QApplication::translate("MainWindow", "The maximum number of Auxiliary Effect Slots an app can\n"
"create. A slot can use a non-negligible amount of CPU time if\n"
"an effect is set on it even if no sources are feeding it, so this\n"
"may help when apps use more than the system can handle.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        effectSlotLineEdit->setInputMask(QString());
        effectSlotLineEdit->setPlaceholderText(QApplication::translate("MainWindow", "4", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "Number of Source Sends:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        srcSendLineEdit->setToolTip(QApplication::translate("MainWindow", "The number of auxiliary sends per source. When not specified,\n"
"it allows the app to request how many it wants. The maximum\n"
"value currently possible is 4.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        srcSendLineEdit->setPlaceholderText(QApplication::translate("MainWindow", "Auto", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "Resampler:", 0, QApplication::UnicodeUTF8));
        resamplerComboBox->clear();
        resamplerComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "- Default -", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Point (low quality, fast)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Linear (basic quality, fast)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Cubic Spline (good quality)", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        resamplerComboBox->setToolTip(QApplication::translate("MainWindow", "The resampling method used when mixing sources.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        groupBox_2->setToolTip(QApplication::translate("MainWindow", "Enables use of specific CPU extensions. Certain methods may\n"
"utilize CPU extensions when detected, and disabling these can\n"
"be useful for preventing those extensions from being used.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        groupBox_2->setTitle(QApplication::translate("MainWindow", "CPU Extensions", 0, QApplication::UnicodeUTF8));
        enableSSECheckBox->setText(QApplication::translate("MainWindow", "SSE", 0, QApplication::UnicodeUTF8));
        enableSSE2CheckBox->setText(QApplication::translate("MainWindow", "SSE2", 0, QApplication::UnicodeUTF8));
        enableNeonCheckBox->setText(QApplication::translate("MainWindow", "Neon", 0, QApplication::UnicodeUTF8));
        enableSSE41CheckBox->setText(QApplication::translate("MainWindow", "SSE4.1", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Resources", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        backendCheckBox->setToolTip(QApplication::translate("MainWindow", "When checked, allows all other available backends not listed in the priority or disabled lists.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        backendCheckBox->setText(QApplication::translate("MainWindow", "Allow Other Backends", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        enabledBackendList->setToolTip(QApplication::translate("MainWindow", "The backend driver list order. Unknown backends and\n"
"duplicated names are ignored.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label->setText(QApplication::translate("MainWindow", "Priority Backends:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        disabledBackendList->setToolTip(QApplication::translate("MainWindow", "Disabled backend driver list.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_2->setText(QApplication::translate("MainWindow", "Disabled Backends:", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Backends", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        emulateEaxCheckBox->setToolTip(QApplication::translate("MainWindow", "Uses a simpler reverb method to emulate the EAX reverb\n"
"effect. This may slightly improve performance at the cost of\n"
"some quality.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        emulateEaxCheckBox->setText(QApplication::translate("MainWindow", "Emulate EAX Reverb:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        groupBox_4->setToolTip(QApplication::translate("MainWindow", "Global amplification for reverb output, expressed in decibels.\n"
"+6 will be a scale of (approximately) 2x, +12 will be a scale of\n"
"4x, etc. Similarly, -6 will be about half, and -12 about 1/4th. A\n"
"value of 0 means no change.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Reverb Boost", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        reverbBoostSlider->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        reverbBoostEdit->setPlaceholderText(QApplication::translate("MainWindow", "0.0", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "dB", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        groupBox_5->setToolTip(QApplication::translate("MainWindow", "Specifies which effects apps can recognize. Disabling effects\n"
"can help for apps that try to use ones that are too intensive\n"
"for the system to handle.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Enabled Effects", 0, QApplication::UnicodeUTF8));
        enableEaxReverbCheck->setText(QApplication::translate("MainWindow", "EAX Reverb", 0, QApplication::UnicodeUTF8));
        enableStdReverbCheck->setText(QApplication::translate("MainWindow", "Standard Reverb", 0, QApplication::UnicodeUTF8));
        enableChorusCheck->setText(QApplication::translate("MainWindow", "Chorus", 0, QApplication::UnicodeUTF8));
        enableDistortionCheck->setText(QApplication::translate("MainWindow", "Distortion", 0, QApplication::UnicodeUTF8));
        enableEchoCheck->setText(QApplication::translate("MainWindow", "Echo", 0, QApplication::UnicodeUTF8));
        enableEqualizerCheck->setText(QApplication::translate("MainWindow", "Equalizer", 0, QApplication::UnicodeUTF8));
        enableFlangerCheck->setText(QApplication::translate("MainWindow", "Flanger", 0, QApplication::UnicodeUTF8));
        enableModulatorCheck->setText(QApplication::translate("MainWindow", "Ring Modulator", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        enableDedicatedCheck->setToolTip(QApplication::translate("MainWindow", "Enables both the Dedicated Dialog and Dedicated LFE effects\n"
"added by the ALC_EXT_DEDICATED extension.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        enableDedicatedCheck->setText(QApplication::translate("MainWindow", "Dedicated ...", 0, QApplication::UnicodeUTF8));
        enableCompressorCheck->setText(QApplication::translate("MainWindow", "Compressor", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("MainWindow", "Default Reverb Effect:", 0, QApplication::UnicodeUTF8));
        defaultReverbComboBox->clear();
        defaultReverbComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "None", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Generic", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "PaddedCell", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Room", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Bathroom", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Livingroom", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Stoneroom", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Auditorium", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "ConcertHall", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Cave", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Arena", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Hangar", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "CarpetedHallway", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Hallway", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "StoneCorridor", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Alley", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Forest", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "City", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Mountains", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Quarry", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Plain", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "ParkingLot", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "SewerPipe", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Underwater", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Drugged", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Dizzy", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Psychotic", 0, QApplication::UnicodeUTF8)
        );
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "Effects", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
