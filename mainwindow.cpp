#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->m_graphicsView = new GraphicsView(this);
    ui->setupUi(this);

    QObject::connect(ui->actionExit, &QAction::triggered, this, [=] () {
        QApplication::quit();
    });
    QObject::connect(ui->actionAbout, &QAction::triggered, this, [=] () {
        QMessageBox::about(this, "About SvgView", "This is a simple SVG viewer.\nCreated by Stepan Rutz.");
    });

    auto layout = new QVBoxLayout(ui->content);
    layout->addWidget(m_graphicsView);


}

MainWindow::~MainWindow()
{
    delete ui;
}
