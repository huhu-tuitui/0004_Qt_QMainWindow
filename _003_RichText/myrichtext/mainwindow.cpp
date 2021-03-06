#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTextFrame>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /**
     * 【1】根框架使用样式
     */

    QTextFrameFormat format;                                //创建框架格式
    format.setBorderBrush(Qt::red);                         //边界颜色
    format.setBorder(3);                                    //边界宽度
    QTextDocument *document = ui->textEdit->document();     //获取文档对象
    QTextFrame *rootFrame = document->rootFrame();          //获取根框架
    rootFrame->setFrameFormat(format);                      //根框架使用格式

    /**
     *【2】光标使用样式
     */
    //新建框架格式
    QTextFrameFormat frameFormat;
    frameFormat.setBackground(Qt::lightGray);                           //设置背景颜色
    frameFormat.setMargin(10);                                          //设置外边距
    frameFormat.setPadding(5);                                          //设置内边距
    frameFormat.setBorder(2);
    frameFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Dotted);   //设置边框样式

    QTextCursor cursor = ui->textEdit->textCursor();                    //获取光标
    cursor.insertFrame(frameFormat);                                    //应用该框架样式

    /**
     *【3-1】增加action动作，信号触发打印根框架
     */
    QAction *action_textFrame = new QAction(tr("框架"),this);
    connect(action_textFrame,&QAction::triggered,this,&MainWindow::showTextFrame);
    ui->mainToolBar->addAction(action_textFrame);


    /**
     *【4-1】增加action动作，信号触发打印所有文本块
     */
    QAction *action_textBlock = new QAction(tr("文本块"),this);
    connect(action_textBlock,&QAction::triggered,this,&MainWindow::showTextBlock);
    ui->mainToolBar->addAction(action_textBlock);

    /**
     *【5-1】增加action动作，设置字体格式
     */
    QAction *action_font = new QAction(tr("字体"),this);
    action_font->setCheckable(true);
    connect(action_font,&QAction::toggled,this,&MainWindow::setTextFont);
    ui->mainToolBar->addAction(action_font);



}

/*【3-2】槽实现*/
void MainWindow::showTextFrame()
{
    QTextDocument *document = ui->textEdit->document();
    QTextFrame *rootFrame = document->rootFrame();
    QTextFrame::iterator it;
    for (it = rootFrame->begin();!(it.atEnd());it++){
        QTextFrame *childFrame = it.currentFrame(); //获取当前框架的指针
        QTextBlock childBlock = it.currentBlock();  //获取当期文本块
        if (childFrame){
            qDebug()<<"frame;";
        }else if (childBlock.isValid()){
            qDebug()<<"block"<<childBlock.text();
        }
    }
}

/*【4-2】槽实现*/
void MainWindow::showTextBlock()
{
    QTextDocument *document = ui->textEdit->document();
    QTextBlock block = document->firstBlock();
    int count = document->blockCount();
    for (int i=0; i<count; i++){
        qDebug()<<tr("文本块%1，文本块首行行号为：%2，长度为：%3，内容为:").arg(i).arg(block.firstLineNumber()).arg(block.length())<<block.text();
        block = block.next();

    }
}

/*【5-2】设置字体编辑格式*/
void MainWindow::setTextFont(bool checked)
{
    if (checked){
        QTextCursor cursor = ui->textEdit->textCursor();
        QTextBlockFormat blockFormat;
        blockFormat.setAlignment(Qt::AlignCenter);                  //水平居中
        cursor.insertBlock(blockFormat);                            //使用文本格式
        QTextCharFormat charFormat;                                 //字符格式
        charFormat.setBackground(Qt::lightGray);                    //背景色
        charFormat.setForeground(Qt::blue);                         //字体颜色
        charFormat.setFont(QFont(tr("宋体"),12,QFont::Bold,true));   //使用宋体，12号，加粗，倾斜
        charFormat.setFontUnderline(true);                          //使用下划线
        cursor.setCharFormat(charFormat);                           //使用字符格式
        cursor.insertText(tr("测试文字"));                            //插入文本
    }else{
        /*恢复默认的字体格式*/
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
