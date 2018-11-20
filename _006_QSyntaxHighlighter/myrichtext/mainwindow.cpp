#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mysyntaxhighlighter.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /* 编辑器文档指针做参数，每当编辑器中的文本改变时都会调用highlightBlock函数设置语法高亮*/
    highlighter = new MySyntaxHighlighter(ui->textEdit->document());

}

MainWindow::~MainWindow()
{
    delete ui;
}
