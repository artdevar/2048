#include "over.h"
#include "ui_over.h"

Over::Over(const QString & str, QWidget *parent) : QDialog(parent), ui(new Ui::Over)
{
    ui->setupUi(this);
    ui->label_score->setAlignment(Qt::AlignCenter);
    ui->label_score->setText("YOUR SCORE: " + str);
}

Over::~Over()
{
    delete ui;
}

void Over::on_but_quit_clicked()
{
    QCoreApplication::quit();
}

void Over::on_but_newgame_clicked()
{
    emit new_game();
    close();
}
