#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "AudioData.h"

#include<QDebug>
#include <QTime>
#include <QDateTime>

tagAudioContext *g_pContext=NULL;

void mainWindowErrorCallback(void *parm,tagTalkbackCInterfaceError tError,char *pErrorInfo){
    printf("mainWindowErrorCallback:%d;pErrorInfo:%s\n",tError,pErrorInfo);
    if(parm==NULL){
        return;
    }
    MainWindow *temp=(MainWindow*)parm;
    qDebug()<<__func__<<__LINE__<<"==============="<<temp;
    temp->talkbackStateSlotEventCall(tError,pErrorInfo);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    g_pContext=new tagAudioContext;
    g_pContext->pUserContext=this;
    g_pContext->pAudioDataContext=NULL;
    connect(&m_tTime,SIGNAL(timeout()),this,SLOT(on_get_buff()));
    m_pTalkbackContext=NULL;
    m_pTalkbackContext=initTalkback();
    connect(this,SIGNAL(talkbackStateSig(int)),this,SLOT(talkbackStateSlot(int)));
    qDebug()<<__func__<<__LINE__<<"==============="<<this;

}

MainWindow::~MainWindow()
{
    if(m_pTalkbackContext!=NULL){
        removeDeviceFromTalkback(m_pTalkbackContext);
        deinitTalkback(m_pTalkbackContext);
    }
    delete ui;
}

void MainWindow::talkbackStateSlotEventCall(int flags, char *pInfo)
{
    emit talkbackStateSig(flags);
}

void MainWindow::talkbackStateSlot(int flags)
{
    qDebug()<<__func__<<__LINE__<<"===================================";
}
void errorCallback(void *parm,tagTalkbackAudioError tError,char *pErrorInfo){
    qDebug()<<__func__<<__LINE__<<pErrorInfo;

}
void MainWindow::on_pushButton_clicked()
{
    //apply
    bool bRet = applyAudio(g_pContext,AUDIO_CODE_C711_U,errorCallback);
    m_tTime.start(20);
    return ;
}

void MainWindow::on_pushButton_2_clicked()
{
    //release
    bool bRet=releaseAudio(g_pContext);
    m_tTime.stop();
    return;
}

void MainWindow::on_pushButton_3_clicked()
{
    //code
}

void MainWindow::on_pushButton_4_clicked()
{
    //audioDevice
    qDebug()<<__func__<<__LINE__<<"start checkClientIsSupportMicrophone";
    bool bRet=checkClientIsSupportMicrophone();
    qDebug()<<__func__<<__LINE__<<"checkClientIsSupportMicrophone:"<<bRet;
    return;
}
long long g_nTime=0;
void MainWindow::on_get_buff()
{
    int nSize=0;
    int nBuffSize=320;
    char pBuff[320]={0};
    bool bRet=true;
    long long nTimeStamp=0;
    while(bRet){
        if(g_pContext->pAudioDataContext!=NULL){
            bRet=getData(g_pContext,pBuff,nBuffSize,nSize,nTimeStamp);
            if(bRet){
                quint64 nQTtime= QDateTime::currentDateTimeUtc().currentMSecsSinceEpoch();
                int nDiv=nTimeStamp-g_nTime;
                g_nTime=nTimeStamp;
                qDebug()<<__func__<<__LINE__<<"bRet:"<<bRet<<"nSize:"<<nSize<<"nTimeStamp:"<<nTimeStamp<<"nQTtime"<<nQTtime<<"nDiv:"<<nDiv;
            }

        }else{
            bRet=false;
        }
    }
}

void MainWindow::on_startTalkback_clicked()
{
    bool bRet=startTalkback(m_pTalkbackContext);
    qDebug()<<__func__<<__LINE__<<"startTalkback:"<<bRet;
}

void MainWindow::on_checkClientIsSupportTalkback_clicked()
{
    bool bRet=checkClientIsSupportTalkback();
    qDebug()<<__func__<<__LINE__<<"checkClientIsSupportMicrophone:"<<bRet;
    return;
}

void MainWindow::on_pauseTalkback_clicked()
{
    pauseTalkback(m_pTalkbackContext);
    return;
}

void MainWindow::on_addDeviceToTalkback_clicked()
{
    bool bRet=addDeviceToTalkback(m_pTalkbackContext,TALKBACK_EXCLUSIVE,(void*)this,"admin","12345"\
                                  ,"rtsp://192.168.60.180:554/Streaming/Channels/1?transportmode=unicast&profile=Profile_1"\
                                  ,"192.168.60.180",554,(void*)mainWindowErrorCallback);
    qDebug()<<__func__<<__LINE__<<"on_addDeviceToTalkback_clicked:"<<bRet;
}

void MainWindow::on_removeDeviceFromTalkback_clicked()
{
    removeDeviceFromTalkback(m_pTalkbackContext);
}

void MainWindow::on_updateCode_clicked()
{
    char pcode[]=
            "<info>\n"\
            "<ip></ip>\n"\
            "<password></password>\n"\
            "<username></username>\n"\
            "<url></url>\n"\
            "<port></port>\n"\
            "</info>";
    QString sText=QString(pcode);
    ui->textEdit->setText(sText);
}
