#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "AudioData.h"

#include<QDebug>
#include <QTime>
#include <QDateTime>

tagAudioContext *g_pContext=NULL;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    g_pContext=new tagAudioContext;
    g_pContext->pUserContext=this;
    g_pContext->pAudioDataContext=NULL;
    connect(&m_tTime,SIGNAL(timeout()),this,SLOT(on_get_buff()));
    m_pTalkbackContext=new tagTalkbackContext;
    m_pTalkbackContext->pUserContext=this;
    sprintf(m_pTalkbackContext->ip,"192.168.1.106");
    sprintf(m_pTalkbackContext->passWord,"admin");
    sprintf(m_pTalkbackContext->userName,"admin");
    sprintf(m_pTalkbackContext->url,"rtsp://192.168.1.106:8554/test264");
    m_pTalkbackContext->nPort=8554;

}

MainWindow::~MainWindow()
{
    delete ui;
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

}

void MainWindow::on_addDeviceToTalkback_clicked()
{

}

void MainWindow::on_removeDeviceFromTalkback_clicked()
{

}
