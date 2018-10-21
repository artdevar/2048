#include "finish.h"
#include "ui_finish.h"

Finish::Finish(uint64_t score, QWidget *parent) : QDialog(parent), ui(new Ui::Finish)
{
    ui->setupUi(this);
    ui->label_score->setAlignment(Qt::AlignCenter);
    ui->label_score->setText("YOUR SCORE: " + QString::number(score));
}

Finish::~Finish()
{
    delete ui;
}

void Finish::on_but_quit_clicked()
{
    QCoreApplication::quit();
}

void Finish::on_but_continue_clicked()
{
    close();
}

void Finish::on_but_newgame_clicked()
{
    emit new_game();
    close();
}
