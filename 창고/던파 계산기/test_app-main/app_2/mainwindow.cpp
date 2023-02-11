#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_clicked()
{     double state_div =0.057;  //스탯값 기본값 1500
      double state_gong =0.0763;  //공력 850
      double su_chi = 0.1;//%수치
      double dok_basic = 1.0; //독공 고정 수치


      int int_c = ui->lineEdit->text().toInt(); //힘지
      int ma_gong = ui->lineEdit_2->text().toInt(); //물마
      int dok_gong = ui->lineEdit_3->text().toInt(); //독공


      double stats_c=  ((int_c * (1.0+state_div ))/ 250+1);
      double mu_gong =(su_chi *(ma_gong*(1.0+state_gong)));
       double dok_gong_2 = mu_gong + ((dok_basic* dok_gong)/100);




    ui->label_4->setText( QString::number(mu_gong));
    ui->label_2->setText( QString::number(stats_c));
    ui->label_7->setText( QString::number(dok_gong_2));

}



